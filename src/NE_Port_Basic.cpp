#include "NE_Port_Basic.h"

NE_Port_Basic::NE_Port_Basic(QString port_label,
                             Class port_class,
                             Port_Type type,
                             QGraphicsItem *parent)
        :QGraphicsItem(parent),
         _port_label(port_label),
         _port_class(port_class),
         _port_type(type)
{
    this->_port_color = this->LoadColor(port_class);

    this->_pen_default = QPen(this->_port_color);
    this->_pen_default.setWidthF(1.5);
    this->_brush_default = QBrush(this->_port_color);

    auto cal_unicode = [this]{
        int len = 0;
        for(auto i = 0; i < this->_port_label.length(); ++i)
        {
            ushort code = this->_port_label.at(i).unicode();
            if (code >= 0xFF01 && code <= 0xFF5E)//全角
                len += this->_font_size;
            else if(code >= 0x0020 && code <= 0x007E)//半角
                len += this->_font_size*0.6;
            else//其他字符
                len += this->_font_size;
        }
        return len;
    };

    this->_font = QFont("Arial",this->_font_size);
    this->_port_label_size = cal_unicode();
    this->_port_width = this->_port_ico_size + this->_port_label_size;

    this->_shadow = new QGraphicsDropShadowEffect();
    this->_shadow->setOffset(0,0);
    this->_shadow->setBlurRadius(15);

    this->setAcceptHoverEvents(true);
    this->setFlags(QGraphicsItem::ItemIsFocusable);
}

QRectF NE_Port_Basic::boundingRect() const
{
    return QRectF(0,0,this->_port_width,this->_port_ico_size);
}

void NE_Port_Basic::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::PointingHandCursor);
    this->focus();
    foreach(NE_Line_Basic *edge, this->_edges){
        edge->focus();
    }
    QGraphicsItem::hoverEnterEvent(event);
}

void NE_Port_Basic::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    unsetCursor();
    this->disfocus();
    foreach(NE_Line_Basic *edge, this->_edges){
        edge->disfocus();
    }
    QGraphicsItem::hoverLeaveEvent(event);
}

void NE_Port_Basic::add_to_parent_node(NE_Node_Basic *parent, NE_Scene *scene)
{
    this->setParentItem(parent);
    this->_parent_item = parent;
    this->_scene = scene;
}

QPointF NE_Port_Basic::get_port_pos()
{
    this->_port_pos = this->scenePos();
    return QPointF(this->_port_pos.x()+0.25*this->_port_ico_size,
                   this->_port_pos.y()+0.5*this->_port_ico_size);
}

void NE_Port_Basic::add_edge(NE_Line_Basic *line, NE_Port_Basic *port)
{
    this->conditioned_remove_edge();
    this->_parent_item->add_connected(port->_parent_item,line);
    this->_edges.append(line);
    this->_connected_ports.append(port);
}

bool NE_Port_Basic::is_connect()
{
    return this->_edges.size();
}

void NE_Port_Basic::remove_edge(NE_Line_Basic *line)
{
    if(!this->_edges.contains(line))
        return;
    for(auto i=0; i<this->_edges.size(); ++i)
    {
        if(line == this->_edges[i])
        {
            this->_edges.remove(i);
            break;
        }
    }
    if(line->_source_port=this)
    {
        for(auto i=0; i<this->_connected_ports.size(); ++i)
        {
            if(line->_des_port == this->_connected_ports[i])
            {
                this->_connected_ports.remove(i);
                break;
            }
        }
        this->_parent_item->remove_connected(line->_des_port->_parent_item,line);
    }
    else
    {
        for(auto i=0; i<this->_connected_ports.size(); ++i)
        {
            if(line->_source_port == this->_connected_ports[i])
            {
                this->_connected_ports.remove(i);
                break;
            }
        }
        this->_parent_item->remove_connected(line->_source_port->_parent_item,line);
    }
    this->disfocus();
}

void NE_Port_Basic::remove_all_edge()
{
    foreach(NE_Line_Basic *edge, this->_edges){
        edge->remove_self();
    }
}

void NE_Port_Basic::conditioned_remove_edge()
{
    if(this->_port_type == PORT_EXEC_IN || this->_port_type == PORT_PARAM_IN)
    {
        if(this->_edges.size()>0)
        {
            foreach(NE_Line_Basic *edge, this->_edges){
                edge->remove_self();
            }
        }
    }
}

QColor NE_Port_Basic::LoadColor(Class pclass)
{
    QJsonObject obj = SearchObj(Param);
    QColor res;
    switch(pclass)
    {
        case Exec:
            res.setNamedColor(obj["exec"].toString());
            return res;
        case Bool:
            res.setNamedColor(obj["bool"].toString());
            return res;
        case Byte:
            res.setNamedColor(obj["byte"].toString());
            return res;
        case Int:
            res.setNamedColor(obj["int"].toString());
            return res;
        case Float:
            res.setNamedColor(obj["float"].toString());
            return res;
        case String:
            res.setNamedColor(obj["string"].toString());
            return res;
        case Vec2:
            res.setNamedColor(obj["vec2"].toString());
            return res;
        case Vec3:
            res.setNamedColor(obj["vec3"].toString());
            return res;
        case Enum:
            res.setNamedColor(obj["enum"].toString());
            return res;
        case Struct:
            res.setNamedColor(obj["struct"].toString());
            return res;
        case Else:
            res.setNamedColor(obj["else"].toString());
            return res;
        case UNknown:
        default:
            res.setNamedColor(obj["unknown"].toString());
            return res;
    }
}

EXECport::EXECport(QString port_label,
                   Class port_class,
                   Port_Type type,
                   QGraphicsItem *parent)
        :NE_Port_Basic(port_label, port_class, type, parent)
{}

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

    if(!this->is_connected())
    {
        painter->setPen(this->_pen_default);
        painter->setBrush(Qt::NoBrush);
        painter->drawPath(port_outline.simplified());
    }
    else
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(this->_brush_default);
        painter->drawPath(port_outline.simplified());
    }

    if(this->_is_focused)
    {
        this->_shadow->setColor(Qt::yellow);
        this->setGraphicsEffect(this->_shadow);
    }
    else
    {
        this->_shadow->setColor(Qt::transparent);
        this->setGraphicsEffect(this->_shadow);
    }
}

void EXECInPort::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!this->is_connected())
    {
        painter->setPen(this->_pen_default);
        painter->setBrush(Qt::NoBrush);
    }
    else
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(this->_brush_default);
    }

    auto port_outline = QPainterPath();
    auto poly = QPolygonF();
    poly.append(QPointF(0,0.2*this->_port_ico_size));
    poly.append(QPointF(0.25*this->_port_ico_size,0.2*this->_port_ico_size));
    poly.append(QPointF(0.5*this->_port_ico_size,0.5*this->_port_ico_size));
    poly.append(QPointF(0.25*this->_port_ico_size,0.8*this->_port_ico_size));
    poly.append(QPointF(0,0.8*this->_port_ico_size));

    port_outline.addPolygon(poly);
    painter->drawPath(port_outline.simplified());

    float AlphaF = 2.0f*(this->_scene->getScale())-1.0f;
    AlphaF > 1.0f ? AlphaF = 1.0f : AlphaF;
    AlphaF < 0.0f ? AlphaF = 0.0f : AlphaF;
    QColor color = this->_port_color;
    color.setAlphaF(AlphaF);
    QPen pen(color);
    painter->setPen(pen);
    painter->drawText(QRectF(this->_port_ico_size,0.15*this->_port_ico_size,
                             this->_port_label_size,this->_port_ico_size),
                      Qt::AlignmentFlag::AlignLeft,this->_port_label);

    if(this->_is_focused)
    {
        this->_shadow->setColor(Qt::yellow);
        this->setGraphicsEffect(this->_shadow);
    }
    else
    {
        this->_shadow->setColor(Qt::transparent);
        this->setGraphicsEffect(this->_shadow);
    }
}

void EXECOutPort::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    float AlphaF = 2.0f*(this->_scene->getScale())-1.0f;
    AlphaF > 1.0f ? AlphaF = 1.0f : AlphaF;
    AlphaF < 0.0f ? AlphaF = 0.0f : AlphaF;
    QColor color = this->_port_color;
    color.setAlphaF(AlphaF);
    QPen pen(color);
    painter->setPen(pen);
    painter->drawText(QRectF(0,0.15*this->_port_ico_size,
                             this->_port_label_size,this->_port_ico_size),
                      Qt::AlignmentFlag::AlignRight,this->_port_label);

    if(!this->is_connected())
    {
        painter->setPen(this->_pen_default);
        painter->setBrush(Qt::NoBrush);
    }
    else
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(this->_brush_default);
    }

    auto port_outline = QPainterPath();
    auto poly = QPolygonF();
    poly.append(QPointF(this->_port_label_size+0.25*this->_port_ico_size,0.2*this->_port_ico_size));
    poly.append(QPointF(this->_port_label_size+0.25*this->_port_ico_size+0.25*this->_port_ico_size,0.2*this->_port_ico_size));
    poly.append(QPointF(this->_port_label_size+0.25*this->_port_ico_size+0.5*this->_port_ico_size,0.5*this->_port_ico_size));
    poly.append(QPointF(this->_port_label_size+0.25*this->_port_ico_size+0.25*this->_port_ico_size,0.8*this->_port_ico_size));
    poly.append(QPointF(this->_port_label_size+0.25*this->_port_ico_size,0.8*this->_port_ico_size));

    port_outline.addPolygon(poly);
    painter->drawPath(port_outline.simplified());

    if(this->_is_focused)
    {
        this->_shadow->setColor(Qt::yellow);
        this->setGraphicsEffect(this->_shadow);
    }
    else
    {
        this->_shadow->setColor(Qt::transparent);
        this->setGraphicsEffect(this->_shadow);
    }
}

QPointF EXECOutPort::get_port_pos()
{
    auto pos = this->scenePos();
    return QPointF(pos.x()+ this->_port_label_size+0.5*this->_port_ico_size,
                   pos.y() + 0.5*this->_port_ico_size);
}

PARAM_IN_Port::PARAM_IN_Port(QString port_label,
                             Class port_class,
                             Port_Type type,
                             QGraphicsItem *parent)
        :NE_Port_Basic(port_label, port_class, type, parent)
{}

void PARAM_IN_Port::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!this->is_connected())
    {
        painter->setPen(this->_pen_default);
        painter->setBrush(Qt::NoBrush);
    }
    else
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(this->_brush_default);
    }
    painter->drawEllipse(QPointF(0.25*this->_port_ico_size,0.5*this->_port_ico_size),
                         0.25*this->_port_ico_size,0.25*this->_port_ico_size);

    auto poly = QPolygonF();
    poly.append(QPointF(0.6*this->_port_ico_size,0.35*this->_port_ico_size));
    poly.append(QPointF(0.75*this->_port_ico_size,0.5*this->_port_ico_size));
    poly.append(QPointF(0.6*this->_port_ico_size,0.65*this->_port_ico_size));

    painter->setBrush(this->_brush_default);
    painter->setPen(Qt::NoPen);
    painter->drawPolygon(poly);

    float AlphaF = 2.0f*(this->_scene->getScale())-1.0f;
    AlphaF > 1.0f ? AlphaF = 1.0f : AlphaF;
    AlphaF < 0.0f ? AlphaF = 0.0f : AlphaF;
    QColor color = this->_port_color;
    color.setAlphaF(AlphaF);
    QPen pen(color);
    //    painter->setPen(this->_pen_default);
    painter->setPen(pen);
    painter->drawText(QRectF(this->_port_ico_size,0.15*this->_port_ico_size,
                             this->_port_label_size,this->_port_ico_size),
                      Qt::AlignmentFlag::AlignLeft,this->_port_label);

    if(this->_is_focused)
    {
        this->_shadow->setColor(Qt::yellow);
        this->setGraphicsEffect(this->_shadow);
    }
    else
    {
        this->_shadow->setColor(Qt::transparent);
        this->setGraphicsEffect(this->_shadow);
    }
}

PARAM_OUT_Port::PARAM_OUT_Port(QString port_label,
                               Class port_class,
                               Port_Type type,
                               QGraphicsItem *parent)
        :NE_Port_Basic(port_label, port_class, type, parent)
{}

void PARAM_OUT_Port::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    float AlphaF = 2.0f*(this->_scene->getScale())-1.0f;
    AlphaF > 1.0f ? AlphaF = 1.0f : AlphaF;
    AlphaF < 0.0f ? AlphaF = 0.0f : AlphaF;
    QColor color = this->_port_color;
    color.setAlphaF(AlphaF);
    QPen pen(color);
//    painter->setPen(this->_pen_default);
    painter->setPen(pen);
    painter->drawText(QRectF(0,0.15*this->_port_ico_size,
                             this->_port_label_size,this->_port_ico_size),
                      Qt::AlignmentFlag::AlignRight,this->_port_label);

    if(!this->is_connected())
    {
        painter->setPen(this->_pen_default);
        painter->setBrush(Qt::NoBrush);
    }
    else
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(this->_brush_default);
    }

    painter->drawEllipse(QPointF(this->_port_label_size+0.5*this->_port_ico_size,0.5*this->_port_ico_size),
                         0.25*this->_port_ico_size,0.25*this->_port_ico_size);

    auto poly = QPolygonF();
    poly.append(QPointF(this->_port_label_size+0.85*this->_port_ico_size,0.35*this->_port_ico_size));
    poly.append(QPointF(this->_port_label_size+this->_port_ico_size,0.5*this->_port_ico_size));
    poly.append(QPointF(this->_port_label_size+0.85*this->_port_ico_size,0.65*this->_port_ico_size));

    painter->setBrush(this->_brush_default);
    painter->setPen(Qt::NoPen);
    painter->drawPolygon(poly);

    if(this->_is_focused)
    {
        this->_shadow->setColor(Qt::yellow);
        this->setGraphicsEffect(this->_shadow);
    }
    else
    {
        this->_shadow->setColor(Qt::transparent);
        this->setGraphicsEffect(this->_shadow);
    }
}

QPointF PARAM_OUT_Port::get_port_pos()
{
    auto pos = this->scenePos();
    return QPointF(pos.x()+ this->_port_label_size+0.5*this->_port_ico_size,
                   pos.y() + 0.5*this->_port_ico_size);
}


NE_Pin::NE_Pin(QString pin_name, Class pin_class, QString pin_type)
        :_pin_name(std::move(pin_name)),
         _pin_class(pin_class),
         _pin_type(std::move(pin_type))
{
    initialize();
}

void NE_Pin::init_port()
{}

void NE_Pin::initialize()
{
    init_port();
}

NE_NodeInput::NE_NodeInput(QString pin_name, Class pin_class, QString pin_type)
: NE_Pin(std::move(pin_name),
         pin_class,
         std::move(pin_type))
{
    initialize();
}

void NE_NodeInput::init_port()
{
    if(this->_pin_type == "data")
        this->port = new PARAM_IN_Port(this->_pin_name,this->_pin_class);
    else if(this->_pin_type == "exec")
        this->port = new EXECInPort(this->_pin_name);
    else
        this->port = nullptr;
}

NE_NodeOutput::NE_NodeOutput(QString pin_name, Class pin_class, QString pin_type)
        : NE_Pin(std::move(pin_name),
                 pin_class,
                 std::move(pin_type))
{
    initialize();
}

void NE_NodeOutput::init_port()
{
    if(this->_pin_type == "data")
        this->port = new PARAM_OUT_Port(this->_pin_name,this->_pin_class);
    else if(this->_pin_type == "exec")
        this->port = new EXECOutPort(this->_pin_name);
    else
        this->port = nullptr;
}
