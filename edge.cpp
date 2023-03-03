#include "edge.h"
#include "port.h"
#include "nodegraphicsview.h"

Edge::Edge(QGraphicsItem *parent, Port *source, Port *des, NodeGraphicsScene *scene, QColor color)
{
    this->_source_port = source;
    this->_des_port = des;
    this->_scene = scene;

    this->_edge_color = this->_source_port->_port_color;
    this->_pen_default = QPen(this->_edge_color);
    this->_pen_default.setWidthF(2);

    this->setZValue(-1);

    this->_shadow->setOffset(0,0);
    this->_shadow->setBlurRadius(20);

    this->setFlags(QGraphicsItem::ItemIsSelectable);

    this->add_to_scene();
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    this->update_edge_path();
    painter->setPen(this->_pen_default);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(this->path());

    if(this->isSelected())
    {
        this->_shadow->setColor(this->_shadow_color);
        this->setGraphicsEffect(this->_shadow);
    }
    else
    {
        this->_shadow->setColor(Qt::transparent);
        this->setGraphicsEffect(this->_shadow);
    }
}

void Edge::update_edge_path()
{
    auto source_pos = this->_source_port->get_port_pos();
    auto des_pos = this->_des_port->get_port_pos();

    auto path = QPainterPath(source_pos);

    auto xwidth = source_pos.x()-des_pos.x();
    xwidth==0?xwidth+=0.01:xwidth+=0;
    auto yheight = qAbs(source_pos.y()-des_pos.y());
    auto tangent = float(yheight)/xwidth*0.5;
    tangent *= xwidth;
    if(xwidth>0)
    {
        if(xwidth>150)
            xwidth = 150;
        tangent += xwidth;
    }
    else
    {
        if(tangent>150)
            tangent = 150;
    }
    path.cubicTo(QPointF(source_pos.x()+tangent,source_pos.y()),
                 QPointF(des_pos.x()-tangent,des_pos.y()),
                 des_pos);
    this->setPath(path);
}

void Edge::add_to_scene()
{
    this->_scene->addItem(this);
    this->_source_port->add_edge(this,this->_des_port);
    this->_des_port->add_edge(this,this->_source_port);
}

void Edge::remove_self()
{
    this->_scene->removeItem(this);
    this->_scene->_view;
    this->_source_port->remove_edge(this);
    this->_des_port->remove_edge(this);
}

DragEdge::DragEdge(QGraphicsItem *parent,bool drag_from_source, QPoint source_pos, QPoint des_pos, QColor edge_color, NodeGraphicsScene *scene)
{
    this->_source_pos = source_pos;
    this->_des_pos = des_pos;
    this->_drag_from_source = drag_from_source;
    this->_edge_color = edge_color;
    this->_scene = scene;

    this->_pen_default = QPen(this->_edge_color);
    this->_pen_default.setWidthF(2);
    this->setZValue(-1);

}

void DragEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    this->update_edge_path();
    painter->setPen(this->_pen_default);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(this->path());

}

void DragEdge::update_edge_path()
{
    auto source_pos = this->_source_pos;
    auto des_pos = this->_des_pos;

    auto path = QPainterPath(source_pos);

    auto xwidth = source_pos.x()-des_pos.x();
    xwidth==0?xwidth+=0.01:xwidth+=0;
    auto yheight = qAbs(source_pos.y()-des_pos.y());
    auto tangent = float(yheight)/xwidth*0.5;
    tangent *= xwidth;
    if(xwidth>0)
    {
        if(xwidth>150)
            xwidth = 150;
        tangent += xwidth;
    }
    else
    {
        if(tangent>150)
            tangent = 150;
    }
    path.cubicTo(QPointF(source_pos.x()+tangent,source_pos.y()),
                 QPointF(des_pos.x()-tangent,des_pos.y()),
                 des_pos);
    this->setPath(path);
}

void DragEdge::update_position(QPointF position)
{
    QPoint pos = QPoint(position.x(),position.y());
    if(this->_drag_from_source)
        this->_des_pos = pos;
    else
        this->_source_pos = pos;
    this->update();
}

void DragEdge::add_first_port(Port *port)
{
    if(this->_drag_from_source)
        this->_source_port = port;
    else
        this->_des_port = port;
}

void DragEdge::add_second_port(Port *port)
{
    if(!this->_drag_from_source)
        this->_source_port = port;
    else
        this->_des_port = port;
}

Edge* DragEdge::create_node_edge()
{
    if(this->can_connect())
    {
        auto *edge = new Edge(nullptr,this->_source_port,this->_des_port,this->_scene,this->_edge_color);
        return edge;
    }
    return nullptr;
}

bool DragEdge::can_connect()
{
    if(this->is_pair() && this->not_same_node() && this->has_same_class())
    {
        return true;
    }
    return false;
}

bool DragEdge::is_pair()
{
    if(this->_source_port->type()==EXEC_OUT && this->_des_port->type() == EXEC_IN)
        return true;
    if(this->_source_port->type()==PARAM_OUT && this->_des_port->type() == PARAM_IN)
        return true;
//    if(this->_source_port->type()==EXEC_IN && this->_des_port->type() == EXEC_OUT)
//    {
//        auto *tmp = this->_source_port;
//        this->_source_port = this->_des_port;
//        this->_des_port = tmp;
//        return true;
//    }
//    if(this->_source_port->type()==PARAM_IN && this->_des_port->type() == PARAM_OUT)
//    {
//        auto *tmp = this->_source_port;
//        this->_source_port = this->_des_port;
//        this->_des_port = tmp;
//        return true;
//    }
    return false;
}

bool DragEdge::not_same_node()
{
    if(this->_source_port->_parent_item == this->_des_port->_parent_item)
        return false;
    return true;
}

bool DragEdge::has_same_class()
{
    if(this->_source_port->_port_class == this->_des_port->_port_class)
        return true;
    return false;
}
