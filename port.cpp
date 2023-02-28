#include "port.h"

Port::Port(QString port_label, QString port_class, QColor port_color, Port_Type type, QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    this->_port_label = port_label;
    this->_port_class = port_class;
    this->_port_color = port_color;
    this->_port_type = type;

    this->_pen_default = QPen(this->_port_color);
    this->_pen_default.setWidthF(1.5);
    this->_brush_default = QBrush(this->_port_color);

    this->_font = QFont("Arial",this->_font_size);
    this->_port_label_size = this->_port_label.length()*this->_font_size;
    this->_port_width = this->_port_ico_size + this->_port_label_size;
}

QRectF Port::boundingRect() const
{
    return QRectF(0,0,this->_port_width,this->_port_ico_size);
}

void Port::add_to_parent_node(QGraphicsItem *parent,QGraphicsScene *scene)
{
    this->setParentItem(parent);
    this->_parent_item = parent;
    this->_scene = scene;
}

int Port::icoSize()
{
    return this->_port_ico_size;
}

Port_Type Port::type()
{
    return this->_port_type;
}

int Port::width()
{
    return this->_port_width;
}

QPointF Port::get_port_pos()
{
    this->_port_pos = this->scenePos();
    return QPointF(this->_port_pos.x()+0.25*this->_port_ico_size,
                   this->_port_pos.y()+0.5*this->_port_ico_size);
}

EXECport::EXECport(QString port_label, QString port_class, QColor port_color, Port_Type type, QGraphicsItem *parent)
{
    this->_port_label = port_label;
    this->_port_class = port_class;
    this->_port_color = port_color;
    this->_port_type = type;

    this->_pen_default = QPen(this->_port_color);
    this->_pen_default.setWidthF(1.5);
    this->_brush_default = QBrush(this->_port_color);

    this->_font = QFont("Consolas",this->_font_size);
    this->_port_label_size = this->_port_label.length()*this->_font_size;
    this->_port_width = this->_port_ico_size + this->_port_label_size;
}

void EXECport::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto port_outline = QPainterPath();
    auto poly = QPolygonF();
    poly.append(QPointF(0,0.2*this->_port_ico_size));
    poly.append(QPointF(0.25*this->_port_ico_size,0.2*this->_port_ico_size));
    poly.append(QPointF(0.5*this->_port_ico_size,0.5*this->_port_ico_size));
    poly.append(QPointF(0.25*this->_port_ico_size,0.8*this->_port_ico_size));
    poly.append(QPointF(0,0.8*this->_port_ico_size));

    port_outline.addPolygon(poly);

    painter->setPen(this->_pen_default);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(port_outline.simplified());
}

EXECInPort::EXECInPort(QString port_label, QString port_class, QColor port_color, Port_Type type, QGraphicsItem *parent)
{
    this->_port_label = port_label;
    this->_port_class = port_class;
    this->_port_color = port_color;
    this->_port_type = type;

    this->_pen_default = QPen(this->_port_color);
    this->_pen_default.setWidthF(1.5);
    this->_brush_default = QBrush(this->_port_color);

    this->_font = QFont("Consolas",this->_font_size);
    this->_port_label_size = this->_port_label.length()*this->_font_size;
    this->_port_width = this->_port_ico_size + this->_port_label_size;
}

EXECOutPort::EXECOutPort(QString port_label, QString port_class, QColor port_color, Port_Type type, QGraphicsItem *parent)
{
    this->_port_label = port_label;
    this->_port_class = port_class;
    this->_port_color = port_color;
    this->_port_type = type;

    this->_pen_default = QPen(this->_port_color);
    this->_pen_default.setWidthF(1.5);
    this->_brush_default = QBrush(this->_port_color);

    this->_font = QFont("Consolas",this->_font_size);
    this->_port_label_size = this->_port_label.length()*this->_font_size;
    this->_port_width = this->_port_ico_size + this->_port_label_size;
}

ParamInPort::ParamInPort(QString port_label, QString port_class, QColor port_color, Port_Type type, QGraphicsItem *parent)
{
    this->_port_label = port_label;
    this->_port_class = port_class;
    this->_port_color = port_color;
    this->_port_type = type;

    this->_pen_default = QPen(this->_port_color);
    this->_pen_default.setWidthF(1.5);
    this->_brush_default = QBrush(this->_port_color);

    this->_font = QFont("Consolas",this->_font_size);
    this->_port_label_size = this->_port_label.length()*this->_font_size;
    this->_port_width = this->_port_ico_size + this->_port_label_size;
}

void ParamInPort::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(this->_pen_default);
    painter->setBrush(Qt::NoBrush);

    painter->drawEllipse(QPointF(0.25*this->_port_ico_size,0.5*this->_port_ico_size),
                         0.25*this->_port_ico_size,0.25*this->_port_ico_size);

    auto poly = QPolygonF();
    poly.append(QPointF(0.6*this->_port_ico_size,0.35*this->_port_ico_size));
    poly.append(QPointF(0.75*this->_port_ico_size,0.5*this->_port_ico_size));
    poly.append(QPointF(0.6*this->_port_ico_size,0.65*this->_port_ico_size));

    painter->setBrush(this->_brush_default);
    painter->setPen(Qt::NoPen);
    painter->drawPolygon(poly);

    painter->setPen(this->_pen_default);
    painter->drawText(QRectF(this->_port_ico_size,0.15*this->_port_ico_size,
                              this->_port_label_size,this->_port_ico_size),
                      Qt::AlignmentFlag::AlignLeft,this->_port_label);
}

ParamOutPort::ParamOutPort(QString port_label, QString port_class, QColor port_color, Port_Type type, QGraphicsItem *parent)
{
    this->_port_label = port_label;
    this->_port_class = port_class;
    this->_port_color = port_color;
    this->_port_type = type;

    this->_pen_default = QPen(this->_port_color);
    this->_pen_default.setWidthF(1.5);
    this->_brush_default = QBrush(this->_port_color);

    this->_font = QFont("Consolas",this->_font_size);
    this->_port_label_size = this->_port_label.length()*this->_font_size;
    this->_port_width = this->_port_ico_size + this->_port_label_size;
}

void ParamOutPort::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(this->_pen_default);
    painter->drawText(QRectF(0,0.15*this->_port_ico_size,
                              this->_port_label_size,this->_port_ico_size),
                      Qt::AlignmentFlag::AlignRight,this->_port_label);

    painter->setPen(this->_pen_default);
    painter->setBrush(Qt::NoBrush);

    painter->drawEllipse(QPointF(this->_port_label_size+0.5*this->_port_ico_size,0.5*this->_port_ico_size),
                         0.25*this->_port_ico_size,0.25*this->_port_ico_size);

    auto poly = QPolygonF();
    poly.append(QPointF(this->_port_label_size+0.85*this->_port_ico_size,0.35*this->_port_ico_size));
    poly.append(QPointF(this->_port_label_size+this->_port_ico_size,0.5*this->_port_ico_size));
    poly.append(QPointF(this->_port_label_size+0.85*this->_port_ico_size,0.65*this->_port_ico_size));

    painter->setBrush(this->_brush_default);
    painter->setPen(Qt::NoPen);
    painter->drawPolygon(poly);
}

QPointF ParamOutPort::get_port_pos()
{
    auto pos = this->scenePos();
    return QPointF(pos.x()+ this->_port_label_size+0.5*this->_port_ico_size,
                   pos.y()+0.5*this->_port_ico_size);
}
