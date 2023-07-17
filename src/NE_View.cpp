#include "NE_View.h"

NE_View::NE_View(QWidget* parent, NE_Scene* scene)
        :QGraphicsView{parent}
{
//    this->setViewport(new QOpenGLWidget);
    this->getConfig();
    this->_scene = scene;
    this->setScene(this->_scene);
    this->_scene->setView(this);

    this->_cutting_line = new NE_Cutting_Line();
    this->_scene->addItem(this->_cutting_line);

    this->setMouseTracking(true);

    this->setRenderHints(QPainter::Antialiasing|
                         QPainter::TextAntialiasing|
                         QPainter::SmoothPixmapTransform|
                         QPainter::LosslessImageRendering);

    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
//    this->setCacheMode(QGraphicsView::CacheBackground);

    this->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
    this->setOptimizationFlag(QGraphicsView::DontSavePainterState, true);

    this->setDragMode(QGraphicsView::RubberBandDrag);

    //隐藏滚动条
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //初始化缩放
    this->_zoom_clamp.min = this->_config.clamp.min;
    this->_zoom_clamp.max = this->_config.clamp.max;
    this->_zoom_factor = this->_config.zoom_factor;
    this->_view_scale = 1.0;

    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setResizeAnchor(QGraphicsView::AnchorUnderMouse);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Highlight, QColor(49, 49, 49));
    setPalette(palette);

    this->setStyleSheetbyQss();
}


double NE_View::getScale()
{
    return this->_view_scale;
}

void NE_View::setScale(double scale)
{
    double factor = scale / this->_view_scale;
    this->_view_scale = scale;
    this->scale(factor, factor);
    this->update();
}

void NE_View::SwitchStyle()
{
    this->_scene->switchStyle();
}

void NE_View::getConfig()
{
    this->_obj = SearchObj(View);
    this->_config.clamp.min = this->_obj["Clamp"].toObject()["min"].toDouble();
    this->_config.clamp.max = this->_obj["Clamp"].toObject()["max"].toDouble();

    this->_config.zoom_factor = this->_obj["Zoom_factor"].toDouble();
}

void NE_View::reset_scale()
{
    this->resetTransform();
    this->_view_scale = 1.0;
    this->update();
}

void NE_View::remove_node(NE_Node_Basic *node)
{
    this->_nodes.remove(this->_nodes.indexOf(node));
}

void NE_View::delete_selected_items()
{
    QList<QGraphicsItem*> select_items = this->_scene->selectedItems();
    for(auto item : select_items)
    {
        if(NE_Node_Basic *node = dynamic_cast<NE_Node_Basic*>(item))
            node->remove_self();
        else if(NE_Line_Basic *line = dynamic_cast<NE_Line_Basic*>(item))
            line->remove_self();
    }
}

void NE_View::LeftButtonPressed(QMouseEvent *event)
{
    auto *item = this->itemAt(event->pos());
    auto *it = dynamic_cast<NE_Port_Basic*>(item);
    //    if(typeid(*item) == typeid(Port))
    if(item==nullptr)
    {
        this->setDragMode(QGraphicsView::RubberBandDrag);
        if(event->modifiers() == Qt::ControlModifier)
        {
            this->_cutting_line_mode = true;
            QApplication::setOverrideCursor(Qt::CrossCursor);
        }
    }
    if(it != nullptr)
    {
//        auto *it = dynamic_cast<NE_Port_Basic*>(item);
        if(event->modifiers() == Qt::ALT)
        {
            it->remove_all_edge();
            this->_scene->update();
        }
        else
        {
            this->_drag_edge_mode = true;
            this->create_dragging_edge(it);
        }
    }
    else
        QGraphicsView::mousePressEvent(event);
}

void NE_View::LeftButtonReleased(QMouseEvent *event)
{
    if(this->_drag_edge_mode)
    {
        this->_drag_edge_mode = false;
        auto *item = this->itemAt(event->pos());
        auto *it = dynamic_cast<NE_Port_Basic*>(item);
        if(it != nullptr)
        {
            this->_drag_edge->add_second_port(it);
            auto *edge = this->_drag_edge->create_node_edge();
            if(edge != nullptr)
                this->_edges.append(edge);
        }
        this->_scene->removeItem(this->_drag_edge);
        this->_drag_edge = nullptr;
    }
    else
    {
        if(this->_cutting_line_mode)
        {
            this->_cutting_line->remove_intersect_edges(this->_edges);

            this->_cutting_line_mode = false;
            this->_cutting_line->reset_points();
            this->_cutting_line->update();
            QApplication::setOverrideCursor(Qt::ArrowCursor);
        }
        this->setDragMode(QGraphicsView::NoDrag);
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void NE_View::RightButtonPressed(QMouseEvent *event)
{
    this->setDragMode(QGraphicsView::NoDrag);
    this->_presstime_r = QTime::currentTime();
    if(this->itemAt(event->pos()) != nullptr)
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

        this->setDragMode(QGraphicsView::ScrollHandDrag);
        this->_is_drag = true;

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
    int elapsed = this->_presstime_r.msecsTo(QTime::currentTime());
    if(elapsed < 100)//单击
    {
        //Click
    }
    else//长按
    {
        //LongPress
    }
    this->_is_drag = false;
    auto release_event = new QMouseEvent(QEvent::MouseButtonRelease,
                                         event->position(),
                                         event->globalPosition(),
                                         Qt::LeftButton,
                                         Qt::NoButton,
                                         event->modifiers());
    QGraphicsView::mouseReleaseEvent(release_event);
    this->setDragMode(QGraphicsView::NoDrag);
}

void NE_View::wheelEvent(QWheelEvent *event)
{
    if(!this->_is_drag)
    {
        double zoom_factor,temp_scale;
        event->angleDelta().y()>0?
                zoom_factor = this->_zoom_factor:
                zoom_factor = 1/this->_zoom_factor;
        temp_scale = this->_view_scale;
        this->_view_scale *= zoom_factor;
        this->_view_scale = this->clamp(this->_view_scale,
                                        this->_zoom_clamp.min,
                                        this->_zoom_clamp.max);
        if(this->_view_scale == this->_zoom_clamp.min ||
           this->_view_scale == this->_zoom_clamp.max)
            zoom_factor = this->_view_scale / temp_scale;
        this->scale(zoom_factor, zoom_factor);
        this->update();
    }
}

void NE_View::mousePressEvent(QMouseEvent *event)
{
    switch(event->button())
    {
        case Qt::LeftButton:
            this->LeftButtonPressed(event);
            break;
        case Qt::RightButton:
            this->RightButtonPressed(event);
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
            this->LeftButtonReleased(event);
            break;
        case Qt::RightButton:
            this->RightButtonReleased(event);
            break;
    }
}

void NE_View::mouseMoveEvent(QMouseEvent *event)
{
    if(this->_drag_edge_mode)
    {
        this->_drag_edge->update_position(this->mapToScene(event->pos()));
    }
    else if(this->_cutting_line_mode)
    {
        this->_cutting_line->update_points(this->mapToScene(event->pos()));
    }
    else
        return QGraphicsView::mouseMoveEvent(event);
}

void NE_View::mouseDoubleClickEvent(QMouseEvent *event)
{
    switch(event->button())
    {
        case Qt::MiddleButton:
            this->reset_scale();
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
            this->delete_selected_items();
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
    this->setStyleSheet(style);
}

void NE_View::addNode(NE_Node_Basic *node, int x, int y)
{
    this->_scene->addItem(node);
    node->setPos(x, y);
    node->set_scene(this->_scene);
    this->_nodes.push_back(node);
}

NE_Scene *NE_View::Scene()
{
    return this->_scene;
}

void NE_View::add_edge(NE_Port_Basic *source, NE_Port_Basic *des)
{
    auto *edge = new NE_Line_Basic(nullptr,source,des,this->_scene);
    this->_edges.push_back(edge);
}

void NE_View::remove_edge(NE_Line_Basic *edge)
{
    for(auto i=0; i<this->_edges.size(); ++i)
    {
        if(edge == this->_edges[i])
        {
            this->_edges.remove(i);
            break;
        }
    }
}

void NE_View::create_dragging_edge(NE_Port_Basic *port)
{
    bool drag_from_source;
    auto port_pos = QPoint(port->get_port_pos().x(),port->get_port_pos().y());
    if(port->PortType()==PORT_EXEC_OUT || port->PortType()==PORT_PARAM_OUT)
        drag_from_source = true;
    else
        drag_from_source = false;
    if(this->_drag_edge == nullptr)
    {
        this->_drag_edge = new NE_Drag_Line(nullptr,drag_from_source,port_pos,port_pos,port->PortColor(),this->_scene);
        this->_drag_edge->add_first_port(port);
        this->_scene->addItem(this->_drag_edge);
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
