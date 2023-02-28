#include "edge.h"

Edge::Edge(QGraphicsItem *parent, Port *source, Port *des, QGraphicsScene *scene, QColor color)
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
}
