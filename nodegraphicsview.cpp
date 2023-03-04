#include "nodegraphicsview.h"

NodeGraphicsView::NodeGraphicsView(QWidget* parent, NodeGraphicsScene* scene)
    :QGraphicsView{parent}
{
    this->getconfig();

    this->_scene = scene;
    this->setScene(this->_scene);
    this->_scene->set_view(this);

    this->setRenderHints(QPainter::Antialiasing|
                         QPainter::TextAntialiasing|
                         QPainter::SmoothPixmapTransform);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    //隐藏滚动条
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->_zoom_clamp[0] = this->_config.clamp.min;
    this->_zoom_clamp[1] = this->_config.clamp.max;
    this->_zoom_factor = this->_config.zoom_factor;
    this->_view_scale = 1.0;

    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

}

void NodeGraphicsView::add_node(Node *node, int x, int y)
{
    this->_scene->addItem(node);
    node->setPos(x-node->width()/2,y-node->height()/2);
    node->set_scene(this->_scene);
    this->_ports.push_back(node);
}

void NodeGraphicsView::add_edge(Port *source, Port *des)
{
    auto *edge = new Edge(nullptr,source,des,this->_scene);
    this->_edges.push_back(edge);
}

void NodeGraphicsView::wheelEvent(QWheelEvent *event)
{
    if(!this->_is_drag)
    {
        double zoom_factor;
        event->angleDelta().y() > 0?
                    zoom_factor = this->_zoom_factor:
                zoom_factor = 1 / this->_zoom_factor;

        this->_view_scale *= zoom_factor;

        this->_view_scale = this->clamp(this->_view_scale,
                                        this->_zoom_clamp[0],this->_zoom_clamp[1]);
        if(this->_view_scale == this->_zoom_clamp[0]||
                this->_view_scale == this->_zoom_clamp[1])
            zoom_factor = 1.0;
        this->scale(zoom_factor, zoom_factor);
        this->update();
    }
}

void NodeGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    switch(event->button())
    {
    case Qt::RightButton:
        this->RightButtonPressed(event);
        break;
    case Qt::LeftButton:
        this->LeftButtonPressed(event);
        break;
    default:
        break;
    }
}

void NodeGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    switch(event->button())
    {
    case Qt::RightButton:
        this->RightButtonRelease(event);
        break;
    case Qt::LeftButton:
        this->LeftButtonRelease(event);
        break;
    default:
        break;
    }
}

void NodeGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
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

void NodeGraphicsView::RightButtonPressed(QMouseEvent *event)
{
    if(this->itemAt(event->pos()) != NULL)
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

void NodeGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(this->_drag_edge_mode)
    {
        this->_drag_edge->update_position(this->mapToScene(event->pos()));
    }
    else
        return QGraphicsView::mouseMoveEvent(event);
}

void NodeGraphicsView::RightButtonRelease(QMouseEvent *event)
{
    this->setDragMode(QGraphicsView::NoDrag);
    this->_is_drag = false;
}

void NodeGraphicsView::LeftButtonPressed(QMouseEvent *event)
{;
    auto *item = this->itemAt(event->pos());
    auto *it = dynamic_cast<Port*>(item);
//    if(typeid(*item) == typeid(Port))
    if(item==NULL)
        this->setDragMode(QGraphicsView::RubberBandDrag);
    if(it != nullptr)
    {
        auto *it = dynamic_cast<Port*>(item);
        this->_drag_edge_mode = true;
        this->create_dragging_edge(it);
    }
    else
        QGraphicsView::mousePressEvent(event);
}

void NodeGraphicsView::LeftButtonRelease(QMouseEvent *event)
{
    if(this->_drag_edge_mode)
    {
        this->_drag_edge_mode = false;
        auto *item = this->itemAt(event->pos());
        auto *it = dynamic_cast<Port*>(item);
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
        this->setDragMode(QGraphicsView::NoDrag);
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void NodeGraphicsView::reset_scale()
{
    this->resetTransform();
    this->_view_scale = 1.0;
}

void NodeGraphicsView::create_dragging_edge(Port *port)
{
    auto port_pos = QPoint(port->get_port_pos().x(),port->get_port_pos().y());
    if(port->type()==EXEC_OUT || port->type()==PARAM_OUT)
        auto drag_from_source = true;
    else
        auto drag_from_source = false;
    if(this->_drag_edge == nullptr)
    {
        this->_drag_edge = new DragEdge(nullptr,true,port_pos,port_pos,port->_port_color,this->_scene);
        this->_drag_edge->add_first_port(port);
        this->_scene->addItem(this->_drag_edge);
    }

}

void NodeGraphicsView::remove_edge(Edge* edge)
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

template <typename T>
T NodeGraphicsView::clamp(T value, T min, T max)
{
    if(value < min)
        return min;
    else if(value > max)
        return max;
    else
        return value;
}

void NodeGraphicsView::getconfig()
{
    this->_obj = SearchObj(View);
    this->_config.clamp.min = this->_obj["zoom_clamp"].toObject()["min"].toDouble();
    this->_config.clamp.max = this->_obj["zoom_clamp"].toObject()["max"].toDouble();

    this->_config.zoom_factor = this->_obj["zoom_factor"].toDouble();
}

