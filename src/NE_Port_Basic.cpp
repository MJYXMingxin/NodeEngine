#include "NE_Port_Basic.h"

NE_Port_Basic::NE_Port_Basic(QString port_label,
                             Class port_class,
                             Port_Type type,
                             bool is_autoport,
                             QVector<Class> canAutoTransClasses,
                             QGraphicsItem *parent)
        :QGraphicsItem(parent),
         _port_label(std::move(port_label)),
         _port_class(port_class),
         _original_class(port_class),
         _port_type(type),
         _is_autoport(is_autoport),
         _canAutoTransClasses(std::move(canAutoTransClasses)),
         _parent_item(nullptr),
         _scene(nullptr)
{
    _port_color = LoadColor(port_class);

    _pen_default = QPen(_port_color);
    _pen_default.setWidthF(1.5);
    _brush_default = QBrush(_port_color);

    auto cal_unicode = [this]{
        int len = 0;
        for(auto i:_port_label)
        {
//            if(i.unicode() >= 0xFF01 && i.unicode() <= 0xFF5E)
//                len += _font_size;
            if(i.unicode() >= 0x0020 && i.unicode() <= 0x007E)
                len += static_cast<int>(_font_size*0.75);
            else
                len += _font_size;
        }
        return len;
    };

    _font = QFont("Arial",_font_size);
    _port_label_size = cal_unicode();
    _port_width = _port_ico_size + _port_label_size;

    _shadow = new QGraphicsDropShadowEffect();
    _shadow->setOffset(0,0);
    _shadow->setBlurRadius(15);

    setAcceptHoverEvents(true);
    setFlags(QGraphicsItem::ItemIsFocusable);
}

[[maybe_unused]] QRectF NE_Port_Basic::boundingRect() const
{
    return {0,0,
            static_cast<qreal>(_port_width),
            static_cast<qreal>(_port_ico_size)};
}

void NE_Port_Basic::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::PointingHandCursor);
    focus();
    foreach(NE_Line_Basic *edge, _edges){
        edge->focus();
    }
    QGraphicsItem::hoverEnterEvent(event);
}

void NE_Port_Basic::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    unsetCursor();
    disfocus();
    foreach(NE_Line_Basic *edge, _edges){
        edge->disfocus();
    }
    QGraphicsItem::hoverLeaveEvent(event);
}

void NE_Port_Basic::add_to_parent_node(NE_Node_Basic *parent, NE_Scene *scene)
{
    setParentItem(parent);
    _parent_item = parent;
    _scene = scene;
}

QPointF NE_Port_Basic::get_port_pos()
{
    _port_pos = scenePos();
    return {_port_pos.x()+0.25*_port_ico_size,
            _port_pos.y()+0.5*_port_ico_size};
}

void NE_Port_Basic::add_edge(NE_Line_Basic *line, NE_Port_Basic *port)
{
    conditioned_remove_edge();
    line->AutoPortTransform();
    _parent_item->add_connected(port->_parent_item,line);
    _edges.append(line);
    _connected_ports.append(port);
}

[[maybe_unused]] bool NE_Port_Basic::is_connect()
{
    return !_edges.empty();
}

void NE_Port_Basic::remove_edge(NE_Line_Basic *line)
{
    if(!_edges.contains(line))
        return;
    for(auto i=0; i<_edges.size(); ++i)
    {
        if(line == _edges[i])
        {
            _edges.remove(i);
            break;
        }
    }
    if(line->_source_port==this)
    {
        for(auto i=0; i<_connected_ports.size(); ++i)
        {
            if(line->_des_port == _connected_ports[i])
            {
                _connected_ports.remove(i);
                break;
            }
        }
        _parent_item->remove_connected(line->_des_port->_parent_item,line);
    }
    else
    {
        for(auto i=0; i<_connected_ports.size(); ++i)
        {
            if(line->_source_port == _connected_ports[i])
            {
                _connected_ports.remove(i);
                break;
            }
        }
        _parent_item->remove_connected(line->_source_port->_parent_item,line);
    }
    if(_is_autoport)
        AutoTransform(_original_class);
    disfocus();
}

void NE_Port_Basic::remove_all_edge()
{
    foreach(NE_Line_Basic *edge, _edges){
        edge->remove_self();
    }
}

void NE_Port_Basic::conditioned_remove_edge()
{
    if(/*_port_type == PORT_EXEC_IN || */_port_type == PORT_PARAM_IN || _port_type == PORT_EXEC_OUT)
    {
        if(!_edges.empty())
        {
            foreach(NE_Line_Basic *edge, _edges){
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
                   :NE_Port_Basic(std::move(port_label),
                                  port_class,
                                  type,
                                  false,
                                  {},
                                  parent)
{}

//void EXECport::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    auto port_outline = QPainterPath();
//    auto poly = QPolygonF();
//    poly.append(QPointF(0,0.2*_port_ico_size));
//    poly.append(QPointF(0.25*_port_ico_size,0.2*_port_ico_size));
//    poly.append(QPointF(0.5*_port_ico_size,0.5*_port_ico_size));
//    poly.append(QPointF(0.25*_port_ico_size,0.8*_port_ico_size));
//    poly.append(QPointF(0,0.8*_port_ico_size));
//
//    port_outline.addPolygon(poly);
//
//    if(!is_connected())
//    {
//        painter->setPen(_pen_default);
//        painter->setBrush(Qt::NoBrush);
//        painter->drawPath(port_outline.simplified());
//    }
//    else
//    {
//        painter->setPen(Qt::NoPen);
//        painter->setBrush(_brush_default);
//        painter->drawPath(port_outline.simplified());
//    }
//
//    if(_is_focused)
//    {
//        _shadow->setColor(Qt::yellow);
//        setGraphicsEffect(_shadow);
//    }
//    else
//    {
//        _shadow->setColor(Qt::transparent);
//        setGraphicsEffect(_shadow);
//    }
//}

void EXECInPort::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!is_connected())
    {
        painter->setPen(_pen_default);
        painter->setBrush(Qt::NoBrush);
    }
    else
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(_brush_default);
    }

    auto port_outline = QPainterPath();
    auto poly = QPolygonF();
    poly.append(QPointF(0,0.2*_port_ico_size));
    poly.append(QPointF(0.25*_port_ico_size,0.2*_port_ico_size));
    poly.append(QPointF(0.5*_port_ico_size,0.5*_port_ico_size));
    poly.append(QPointF(0.25*_port_ico_size,0.8*_port_ico_size));
    poly.append(QPointF(0,0.8*_port_ico_size));

    port_outline.addPolygon(poly);
    painter->drawPath(port_outline.simplified());

    auto AlphaF = static_cast<float>(4.0f*(_scene->getScale())-3.0f);
    AlphaF > 1.0f ? AlphaF = 1.0f : AlphaF;
    AlphaF < 0.0f ? AlphaF = 0.0f : AlphaF;
    QColor color = _port_color;
    color.setAlphaF(AlphaF);
    QPen pen(color);
    painter->setPen(pen);
    painter->drawText(QRectF(_port_ico_size,0.15*_port_ico_size,
                             _port_label_size,_port_ico_size),
                      Qt::AlignmentFlag::AlignLeft,_port_label);

    if(_is_focused)
    {
        _shadow->setColor(Qt::yellow);
        setGraphicsEffect(_shadow);
    }
    else
    {
        _shadow->setColor(Qt::transparent);
        setGraphicsEffect(_shadow);
    }
}

void EXECOutPort::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    auto AlphaF = static_cast<float>(4.0f*(_scene->getScale())-3.0f);
    AlphaF > 1.0f ? AlphaF = 1.0f : AlphaF;
    AlphaF < 0.0f ? AlphaF = 0.0f : AlphaF;
    QColor color = _port_color;
    color.setAlphaF(AlphaF);
    QPen pen(color);
    painter->setPen(pen);
    painter->drawText(QRectF(0,0.15*_port_ico_size,
                             _port_label_size,_port_ico_size),
                      Qt::AlignmentFlag::AlignRight,_port_label);

    if(!is_connected())
    {
        painter->setPen(_pen_default);
        painter->setBrush(Qt::NoBrush);
    }
    else
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(_brush_default);
    }

    auto port_outline = QPainterPath();
    auto poly = QPolygonF();
    poly.append(QPointF(_port_label_size+0.25*_port_ico_size,0.2*_port_ico_size));
    poly.append(QPointF(_port_label_size+0.25*_port_ico_size+0.25*_port_ico_size,0.2*_port_ico_size));
    poly.append(QPointF(_port_label_size+0.25*_port_ico_size+0.5*_port_ico_size,0.5*_port_ico_size));
    poly.append(QPointF(_port_label_size+0.25*_port_ico_size+0.25*_port_ico_size,0.8*_port_ico_size));
    poly.append(QPointF(_port_label_size+0.25*_port_ico_size,0.8*_port_ico_size));

    port_outline.addPolygon(poly);
    painter->drawPath(port_outline.simplified());

    if(_is_focused)
    {
        _shadow->setColor(Qt::yellow);
        setGraphicsEffect(_shadow);
    }
    else
    {
        _shadow->setColor(Qt::transparent);
        setGraphicsEffect(_shadow);
    }
}

QPointF EXECOutPort::get_port_pos()
{
    auto pos = scenePos();
    return {pos.x()+ _port_label_size+0.5*_port_ico_size,
            pos.y() + 0.5*_port_ico_size};
}

PARAM_IN_Port::PARAM_IN_Port(QString port_label,
                             Class port_class,
                             bool is_Auto,
                             QVector<Class> canAutoTransClasses,
                             Port_Type type,
                             QGraphicsItem *parent)
                             :NE_Port_Basic(std::move(port_label),
                                            port_class,
                                            type,
                                            is_Auto,
                                            std::move(canAutoTransClasses),
                                            parent)
{}

void PARAM_IN_Port::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!is_connected())
    {
        painter->setPen(_pen_default);
        painter->setBrush(Qt::NoBrush);
    }
    else
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(_brush_default);
    }
    painter->drawEllipse(QPointF(0.25*_port_ico_size,0.5*_port_ico_size),
                         0.25*_port_ico_size,0.25*_port_ico_size);

    auto poly = QPolygonF();
    poly.append(QPointF(0.6*_port_ico_size,0.35*_port_ico_size));
    poly.append(QPointF(0.75*_port_ico_size,0.5*_port_ico_size));
    poly.append(QPointF(0.6*_port_ico_size,0.65*_port_ico_size));

    painter->setBrush(_brush_default);
    painter->setPen(Qt::NoPen);
    painter->drawPolygon(poly);

    auto AlphaF = static_cast<float>(4.0f*(_scene->getScale())-3.0f);
    AlphaF > 1.0f ? AlphaF = 1.0f : AlphaF;
    AlphaF < 0.0f ? AlphaF = 0.0f : AlphaF;
    QColor color = _port_color;
    color.setAlphaF(AlphaF);
    QPen pen(color);
    //    painter->setPen(_pen_default);
    painter->setPen(pen);
    painter->drawText(QRectF(_port_ico_size,0.15*_port_ico_size,
                             _port_label_size,_port_ico_size),
                      Qt::AlignmentFlag::AlignLeft,_port_label);

    if(_is_focused)
    {
        _shadow->setColor(Qt::yellow);
        setGraphicsEffect(_shadow);
    }
    else
    {
        _shadow->setColor(Qt::transparent);
        setGraphicsEffect(_shadow);
    }
}

PARAM_OUT_Port::PARAM_OUT_Port(QString port_label,
                               Class port_class,
                               bool is_Auto,
                               QVector<Class> canAutoTransClasses,
                               Port_Type type,
                               QGraphicsItem *parent)
                               :NE_Port_Basic(std::move(port_label),
                                              port_class,
                                              type,
                                              is_Auto,
                                              std::move(canAutoTransClasses),
                                              parent)
{}

void PARAM_OUT_Port::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto AlphaF = static_cast<float>(4.0f*(_scene->getScale())-3.0f);
    AlphaF > 1.0f ? AlphaF = 1.0f : AlphaF;
    AlphaF < 0.0f ? AlphaF = 0.0f : AlphaF;
    QColor color = _port_color;
    color.setAlphaF(AlphaF);
    QPen pen(color);
//    painter->setPen(_pen_default);
    painter->setPen(pen);
    painter->drawText(QRectF(0,0.15*_port_ico_size,
                             _port_label_size,_port_ico_size),
                      Qt::AlignmentFlag::AlignRight,_port_label);

    if(!is_connected())
    {
        painter->setPen(_pen_default);
        painter->setBrush(Qt::NoBrush);
    }
    else
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(_brush_default);
    }

    painter->drawEllipse(QPointF(_port_label_size+0.5*_port_ico_size,0.5*_port_ico_size),
                         0.25*_port_ico_size,0.25*_port_ico_size);

    auto poly = QPolygonF();
    poly.append(QPointF(_port_label_size+0.85*_port_ico_size,0.35*_port_ico_size));
    poly.append(QPointF(_port_label_size+_port_ico_size,0.5*_port_ico_size));
    poly.append(QPointF(_port_label_size+0.85*_port_ico_size,0.65*_port_ico_size));

    painter->setBrush(_brush_default);
    painter->setPen(Qt::NoPen);
    painter->drawPolygon(poly);

    if(_is_focused)
    {
        _shadow->setColor(Qt::yellow);
        setGraphicsEffect(_shadow);
    }
    else
    {
        _shadow->setColor(Qt::transparent);
        setGraphicsEffect(_shadow);
    }
}

QPointF PARAM_OUT_Port::get_port_pos()
{
    auto pos = scenePos();
    return {pos.x()+ _port_label_size+0.5*_port_ico_size,
            pos.y() + 0.5*_port_ico_size};
}


NE_Pin::NE_Pin(QString pin_name,
               Class pin_class,
               QString pin_type,
               bool isAuto,
               const QVector<Class> &canAutoTransClasses)
               :_pin_name(std::move(pin_name)),
               _pin_class(pin_class),
               _pin_type(std::move(pin_type)),
               _canAutoTransClasses(canAutoTransClasses),
               port(nullptr),
               _val(),
               _cur_session(-1),
               _has_set_val(false)
{
    initialize(isAuto);
}

void NE_Pin::init_port(bool is_autoport)
{}

void NE_Pin::initialize(bool is_autoport)
{
    init_port(is_autoport);
}

NE_NodeInput::NE_NodeInput(QString pin_name,
                           Class pin_class,
                           QString pin_type,
                           bool isAuto,
                           const QVector<Class> &canAutoTransClasses)
                           : NE_Pin(std::move(pin_name),
                                    pin_class,
                                    std::move(pin_type),
                                    isAuto,
                                    canAutoTransClasses)
{
    initialize(isAuto);
}

void NE_NodeInput::init_port(bool isAuto)
{
    if(_pin_type == "data")
        port = new PARAM_IN_Port(_pin_name,_pin_class,isAuto,_canAutoTransClasses);
    else if(_pin_type == "exec")
        port = new EXECInPort(_pin_name);
    else
        port = nullptr;
}

NE_NodeOutput::NE_NodeOutput(QString pin_name,
                             Class pin_class,
                             QString pin_type,
                             bool isAuto,
                             const QVector<Class> &canAutoTransClasses)
                             : NE_Pin(std::move(pin_name),
                                      pin_class,
                                      std::move(pin_type),
                                      isAuto,
                                      canAutoTransClasses)
{
    initialize(isAuto);
}

void NE_NodeOutput::init_port(bool isAuto)
{
    if(_pin_type == "data")
        port = new PARAM_OUT_Port(_pin_name,_pin_class,isAuto,_canAutoTransClasses);
    else if(_pin_type == "exec")
        port = new EXECOutPort(_pin_name);
    else
        port = nullptr;
}
