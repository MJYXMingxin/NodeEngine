#include "NE_View.h"
#include "nodes/interfaces/NodeLibraryPluginInterface.h"

NE_View::NE_View(QWidget* parent, NE_Scene* scene)
        :QGraphicsView{parent},
        _config(),
        _zoom_clamp(1.1),
        _scene(scene),
        _cutting_line(new NE_Cutting_Line),
        _nodelist(),
        _pluginList(),
        _data({})
{
//    setViewport(new QOpenGLWidget);
    getConfig();
    setScene(_scene);
    _scene->setView(this);
    _scene->addItem(_cutting_line);

    setMouseTracking(true);

    setRenderHints(QPainter::Antialiasing|
                   QPainter::TextAntialiasing|
                   QPainter::SmoothPixmapTransform|
                   QPainter::LosslessImageRendering);

    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setCacheMode(QGraphicsView::CacheBackground);

//    setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
//    setOptimizationFlag(QGraphicsView::DontSavePainterState, true);

    setDragMode(QGraphicsView::RubberBandDrag);

    //隐藏滚动条
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //初始化缩放
    _zoom_clamp.min = _config.clamp.min;
    _zoom_clamp.max = _config.clamp.max;
    _zoom_factor = _config.zoom_factor;
    _view_scale = 1.0;

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Highlight, QColor(49, 49, 49));
    setPalette(palette);

    setStyleSheetbyQss();

    LoadPlugins();
    setup_node_list_widget();
}
NE_View::~NE_View()
{
    if(loader.isLoaded()){
        loader.unload();
    }
}

double NE_View::getScale() const { return _view_scale; }

void NE_View::setScale(double scale)
{
    double factor = scale / _view_scale;
    _view_scale = scale;
    this->scale(factor, factor);
    update();
}

void NE_View::SwitchStyle() { _scene->switchStyle(); }

void NE_View::getConfig()
{
    _obj = SearchObj(View);
    _config.clamp.min = _obj["Clamp"].toObject()["min"].toDouble();
    _config.clamp.max = _obj["Clamp"].toObject()["max"].toDouble();

    _config.zoom_factor = _obj["Zoom_factor"].toDouble();
}

void NE_View::reset_scale()
{
    resetTransform();
    _view_scale = 1.0;
    update();
}

void NE_View::remove_node(NE_Node_Basic *node) { _nodes.remove(_nodes.indexOf(node)); }

void NE_View::delete_selected_items()
{
    QList<QGraphicsItem*> select_items = _scene->selectedItems();
    for(auto item : select_items)
    {
        if(auto *node = dynamic_cast<NE_Node_Basic*>(item))
            node->remove_self();
        else if(auto *line = dynamic_cast<NE_Line_Basic*>(item))
            line->remove_self();
    }
}

void NE_View::LeftButtonPressed(QMouseEvent *event)
{
    auto *item = itemAt(event->pos());
    auto *it = dynamic_cast<NE_Port_Basic*>(item);
    //    if(typeid(*item) == typeid(Port))
    if(item==nullptr)
    {
        hidden_nodelist();
        setDragMode(QGraphicsView::RubberBandDrag);
        if(event->modifiers() == Qt::ControlModifier)
        {
            _cutting_line_mode = true;
            QApplication::setOverrideCursor(Qt::CrossCursor);
        }
    }

    if(it != nullptr)
    {
//        auto *it = dynamic_cast<NE_Port_Basic*>(item);
        if(event->modifiers() == Qt::ALT)
        {
            it->remove_all_edge();
            _scene->update();
        }
        else
        {
            _drag_edge_mode = true;
            create_dragging_edge(it);
        }
    }
    else
        QGraphicsView::mousePressEvent(event);
}

void NE_View::LeftButtonReleased(QMouseEvent *event)
{
    if(_drag_edge_mode)
    {
        _drag_edge_mode = false;
        auto *item = itemAt(event->pos());
        auto *it = dynamic_cast<NE_Port_Basic*>(item);
        if(it != nullptr)
        {
            _drag_edge->add_second_port(it);
            auto *edge = _drag_edge->create_node_edge();
            if(edge != nullptr)
                _edges.append(edge);
        }
        _scene->removeItem(_drag_edge);
        _drag_edge = nullptr;
    }
    else
    {
        if(_cutting_line_mode)
        {
            _cutting_line->remove_intersect_edges(_edges);

            _cutting_line_mode = false;
            _cutting_line->reset_points();
            _cutting_line->update();
            QApplication::setOverrideCursor(Qt::ArrowCursor);
        }
        setDragMode(QGraphicsView::NoDrag);
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void NE_View::RightButtonPressed(QMouseEvent *event)
{
    hidden_nodelist();
    setDragMode(QGraphicsView::NoDrag);
    _presstime_r = QTime::currentTime();
    _presspos_r = QCursor::pos();
    if(itemAt(event->pos()) != nullptr)
        return;
    else
    {
        auto release_event = new QMouseEvent(QEvent::MouseButtonRelease,
                                             event->position(),
                                             event->globalPosition(),
                                             Qt::LeftButton,
                                             Qt::NoButton,
                                             event->modifiers());
        QGraphicsView::mouseReleaseEvent(release_event);

        setDragMode(QGraphicsView::ScrollHandDrag);
        _is_drag = true;

        auto click_event = new QMouseEvent(QEvent::MouseButtonPress,
                                           event->position(),
                                           event->globalPosition(),
                                           Qt::LeftButton,
                                           Qt::NoButton,
                                           event->modifiers());
        QGraphicsView::mousePressEvent(click_event);
    }
}

void NE_View::RightButtonReleased(QMouseEvent *event)
{
    int elapsed = _presstime_r.msecsTo(QTime::currentTime());
    QPointF curpos = QCursor::pos();
    QLineF mouseOffset(_presspos_r, curpos);
    if(itemAt(event->pos()) == nullptr) {
        if (mouseOffset.length() < 3)//鼠标未偏移
        {
            show_nodelist_at_pos(mapToScene(mapFromGlobal(QCursor::pos())));
        }
        if (elapsed < 300)//单击Click
        {

        } else//长按LongPress
        {
        }
        _is_drag = false;
        auto release_event = new QMouseEvent(QEvent::MouseButtonRelease,
                                             event->position(),
                                             event->globalPosition(),
                                             Qt::LeftButton,
                                             Qt::NoButton,
                                             event->modifiers());
        QGraphicsView::mouseReleaseEvent(release_event);
        setDragMode(QGraphicsView::NoDrag);
    }
}

void NE_View::wheelEvent(QWheelEvent *event)
{
    if(!_is_drag)
    {
        double zoom_factor,temp_scale;
        event->angleDelta().y()>0?
                zoom_factor = _zoom_factor:
                zoom_factor = 1/_zoom_factor;
        temp_scale = _view_scale;
        _view_scale *= zoom_factor;
        _view_scale = clamp(_view_scale,
                                        _zoom_clamp.min,
                                        _zoom_clamp.max);
        if(_view_scale == _zoom_clamp.min ||
           _view_scale == _zoom_clamp.max)
            zoom_factor = _view_scale / temp_scale;
        scale(zoom_factor, zoom_factor);
        update();
    }
}

void NE_View::mousePressEvent(QMouseEvent *event)
{
    switch(event->button())
    {
        case Qt::LeftButton:
            LeftButtonPressed(event);
            break;
        case Qt::RightButton:
            RightButtonPressed(event);
            break;
        default:
            break;
    }
    QGraphicsView::mousePressEvent(event);
}

void NE_View::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    switch(event->button())
    {
        case Qt::LeftButton:
            LeftButtonReleased(event);
            break;
        case Qt::RightButton:
            RightButtonReleased(event);
            break;
        default:
            break;
    }
}

void NE_View::mouseMoveEvent(QMouseEvent *event)
{
    if(_drag_edge_mode)
    {
        _drag_edge->update_position(mapToScene(event->pos()));
    }
    else if(_cutting_line_mode)
    {
        _cutting_line->update_points(mapToScene(event->pos()));
    }
    else
        return QGraphicsView::mouseMoveEvent(event);
}

void NE_View::mouseDoubleClickEvent(QMouseEvent *event)
{
    switch(event->button())
    {
        case Qt::MiddleButton:
            reset_scale();
            break;
        default:
            QGraphicsView::mouseDoubleClickEvent(event);
            break;
    }
}

void NE_View::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Delete:
            delete_selected_items();
            break;
    }
    return QGraphicsView::keyPressEvent(event);
}

void NE_View::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);

    if (dragMode() == QGraphicsView::RubberBandDrag)
    {
        QPainter painter(viewport());
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(QColor(49, 49, 49), 2));
        painter.drawRect(rubberBandRect());
    }
}

void NE_View::setStyleSheetbyQss()
{
    QString style = loadStyleSheet("NE_View");
    setStyleSheet(style);
}

void NE_View::addNode(NE_Node_Basic *node, int x, int y)
{
    _scene->addItem(node);
    node->setPos(x, y);
    node->set_scene(_scene);
    _nodes.push_back(node);
}

NE_Scene *NE_View::Scene() { return _scene; }

void NE_View::add_edge(NE_Port_Basic *source, NE_Port_Basic *des)
{
    auto *edge = new NE_Line_Basic(nullptr,source,des,_scene);
    _edges.push_back(edge);
}

void NE_View::remove_edge(NE_Line_Basic *edge)
{
    for(auto i=0; i<_edges.size(); ++i)
    {
        if(edge == _edges[i])
        {
            _edges.remove(i);
            break;
        }
    }
}

void NE_View::create_dragging_edge(NE_Port_Basic *port)
{
    bool drag_from_source;
    auto port_pos = QPoint(static_cast<int>(port->get_port_pos().x()),
                           static_cast<int>(port->get_port_pos().y()));
    if(port->PortType()==PORT_EXEC_OUT || port->PortType()==PORT_PARAM_OUT)
        drag_from_source = true;
    else
        drag_from_source = false;
    if(_drag_edge == nullptr)
    {
        _drag_edge = new NE_Drag_Line(nullptr,drag_from_source,port_pos,port_pos,port->PortColor(),_scene);
        _drag_edge->add_first_port(port);
        _scene->addItem(_drag_edge);
    }
}

void NE_View::LoadPlugins() {
    QDir dir("../plugins");
    _pluginList << "*.dll";

    QStringList fileList = dir.entryList(_pluginList, QDir::Files);
    qDebug()<<"Loading Plugins at:"<<dir.absolutePath().toStdString().c_str();
    foreach (QString file, fileList) {
        qDebug() << "Try Loading:" << file.toStdString().c_str();
        loader.setFileName(dir.filePath(file));
        if(!loader.load()){
            qDebug() << file << "load failed! Reason:" << loader.errorString().toStdString().c_str();
            break;
        }

        NodeLibraryPluginInterface *pi = qobject_cast<NodeLibraryPluginInterface *>(loader.instance());
        if(pi) {
            auto libs = pi->GetLibraryMap();
            for (auto it = libs.begin(); it != libs.end(); ++it) {
                QStringList nodes = it.value().keys();
                _data.insert({{it.key(), nodes}});
                qDebug()<<"Lib :"<<it.key()<<" has been loaded";
            }
            _libs.insert(file, _data);
        }
        else
            qDebug() << file << "load failed! Reason: It's not NodeEngine's Plugin";
        loader.unload();
    }
}

void NE_View::setup_node_list_widget()
{
    _nodelist = new NE_NodeList(_data);
    QGraphicsProxyWidget *proxy = _scene->addWidget(_nodelist);
    proxy->setZValue(std::numeric_limits<qreal>::max());
    _nodelist->setGeometry(0, 0, 200, 300);
    hidden_nodelist();
    connect(_nodelist->tree, &NE_NodeListWidget::itemDoubleClicked, this, &NE_View::onItemDoubleClicked);
}

void NE_View::show_nodelist_at_pos(QPointF pos)
{
    _nodelist->setGeometry(static_cast<int>(pos.x()),
                           static_cast<int>(pos.y()),
                           200,300);
    _nodelist->searchbox->setFocus();
    _nodelist->show();
}

void NE_View::hidden_nodelist()
{
    _nodelist->clearSearchBar();
    _nodelist->setVisible(false);
}

void NE_View::onItemDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)
    if(!item->data(0, Qt::UserRole).value<QMap<QString,QString>>().empty())
    {
        createNode(item->data(0, Qt::UserRole).value<QMap<QString,QString>>().keys().first(),
                   item->data(0, Qt::UserRole).value<QMap<QString,QString>>().values().first());
    }
}

void NE_View::createNode(const QString& lib, const QString& name)
{
    for (auto i = _libs.begin(); i != _libs.end(); ++i) {
        if(!i.value().value(lib).empty()) {
            QStringList plugin(i.key());
            QDir dir("../plugins");
            QStringList fileList = dir.entryList(plugin, QDir::Files);
            foreach (QString file, fileList) {
                loader.setFileName(dir.filePath(file));
                if(!loader.load()){
                    qDebug() << file << "load failed! Reason:" << loader.errorString().toStdString().c_str();
                    break;
                }
                NodeLibraryPluginInterface *pi = qobject_cast<NodeLibraryPluginInterface *>(loader.instance());
                if (pi) {
                    NE_Node *node = pi->CreateNodeByName(lib, name);
                    addNode(node, _nodelist->pos().x(), _nodelist->pos().y());
                    hidden_nodelist();
                }
            }
        }
    }
}

template <typename T>
T NE_View::clamp(T value, T min, T max)
{
    if(value < min)
        return min;
    else if(value > max)
        return max;
    else
        return value;
}
