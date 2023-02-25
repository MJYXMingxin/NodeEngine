#include "nodegraphicsitem.h"

Node::Node(QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    this->_pen_default = QPen(QColor(21,21,21));
    this->_pen_selected = QPen(QColor(255,238,0,170));
    this->_brush_background = QBrush(QColor(21,21,21,170));

    this->setFlags(QGraphicsItem::ItemIsSelectable |
                   QGraphicsItem::ItemIsMovable);
}

QRectF Node::boundingRect() const
{
    return QRectF(0,0,this->_node_width,this->_node_height);
}

int Node::width()
{
    return this->_node_width;
}

int Node::height()
{
    return this->_node_height;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto node_outline = QPainterPath();
    node_outline.addRoundedRect(0,0,
                                this->_node_width,
                                this->_node_height,
                                this->_node_radius,
                                this->_node_radius);
    painter->setPen(Qt::NoPen);
    painter->setBrush(this->_brush_background);
    painter->drawPath(node_outline.simplified());

    this->isSelected()?painter->setPen(this->_pen_selected):painter->setPen(this->_pen_default);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(node_outline);
}
