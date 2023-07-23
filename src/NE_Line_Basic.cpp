#include "NE_Line_Basic.h"

NE_Line_Basic::NE_Line_Basic(QGraphicsItem *parent,
                             NE_Port_Basic *source,
                             NE_Port_Basic *des,
                             NE_Scene *scene)
        :QGraphicsPathItem(parent),
         _source_port(source),
         _des_port(des),
         _scene(scene),
         _shadow(new QGraphicsDropShadowEffect()),
         _shadow_color(Qt::yellow),
         _edge_color(source->PortColor())
{
    _pen_default = QPen(_edge_color);
    _pen_default.setWidthF(2);

    setZValue(-1);

    _shadow->setOffset(0, 0);
    _shadow->setBlurRadius(15);

//    setFlags(QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    setFlags(QGraphicsItem::ItemIsFocusable);
    add_to_scene();
}

void NE_Line_Basic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    update_edge_path();

    if(FocusState())
    {
        _pen_default.setWidthF(4);
        _shadow->setColor(_shadow_color);
        setGraphicsEffect(_shadow);
    }
    else
    {
        _pen_default.setWidthF(2);
        _shadow->setColor(Qt::transparent);
        setGraphicsEffect(_shadow);
    }

    painter->setPen(_pen_default);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path());
}

void NE_Line_Basic::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::PointingHandCursor);
    focus();
    _source_port->focus();
    _des_port->focus();
    QGraphicsItem::hoverEnterEvent(event);
}

void NE_Line_Basic::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    unsetCursor();
    disfocus();
    _source_port->disfocus();
    _des_port->disfocus();
    QGraphicsItem::hoverLeaveEvent(event);
}

void NE_Line_Basic::update_edge_path()
{
    auto source_pos = _source_port->get_port_pos();
    auto des_pos = _des_port->get_port_pos();

    auto path = QPainterPath(source_pos);

    double xwidth = (double)(source_pos.x())-(double)(des_pos.x());
    xwidth==0?xwidth+=0.01:xwidth+=0;
    double yheight = qAbs((double)(source_pos.y())-(double)(des_pos.y()));
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
    setPath(path);
}

void NE_Line_Basic::add_to_scene()
{
    _scene->addItem(this);
    _source_port->add_edge(this,_des_port);
    _des_port->add_edge(this,_source_port);
    _source_port->update();
    _des_port->update();
}

void NE_Line_Basic::AutoPortTransform() const
{
    if(_des_port->isAutoTransform())
        _des_port->AutoTransform(_source_port->PortClass());
    else
        if(_source_port->isAutoTransform())
            _source_port->AutoTransform(_des_port->PortClass());
}

void NE_Line_Basic::remove_self()
{
    _scene->removeItem(this);
    _scene->View()->remove_edge(this);
    _source_port->remove_edge(this);
    _des_port->remove_edge(this);
}

bool NE_Line_Basic::FocusState() const
{
    return _is_focused;
}

void NE_Line_Basic::focus()
{
    _is_focused = true;
    _source_port->focus();
    _des_port->focus();
    update();
}

void NE_Line_Basic::disfocus()
{
    _is_focused = false;
    _source_port->disfocus();
    _des_port->disfocus();
    update();
}

NE_Drag_Line::NE_Drag_Line(QGraphicsItem *parent,
                           bool drag_from_source,
                           QPoint source_pos,
                           QPoint des_pos,
                           QColor edge_color,
                           NE_Scene *scene)
        :QGraphicsPathItem(parent),
         _drag_from_source(drag_from_source),
         _source_pos(source_pos),
         _des_pos(des_pos),
         _edge_color(edge_color),
         _scene(scene),
         _source_port(nullptr),
         _des_port(nullptr)
{
    _pen_default = QPen(_edge_color);
    _pen_default.setWidthF(2);
    setZValue(-1);
}

void NE_Drag_Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    update_edge_path();
    painter->setPen(_pen_default);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path());
}

void NE_Drag_Line::update_edge_path()
{
    QPoint source_pos = _source_pos;
    QPoint des_pos = _des_pos;

    if(source_pos.isNull() or des_pos.isNull())
        return;

    auto path = QPainterPath(source_pos);

    double xwidth = (double)(source_pos.x())-(double)(des_pos.x());
    xwidth==0?xwidth+=0.01:xwidth+=0;
    double yheight = qAbs((double)(source_pos.y())-(double)(des_pos.y()));
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
    setPath(path);
}

void NE_Drag_Line::update_position(QPointF position)
{
    QPoint pos = QPoint(static_cast<int>(position.x()),
                        static_cast<int>(position.y()));
    if(_drag_from_source)
        _des_pos = pos;
    else
        _source_pos = pos;
    update_edge_path();
    update();
}

void NE_Drag_Line::add_first_port(NE_Port_Basic *port)
{
    if(_drag_from_source)
        _source_port = port;
    else
        _des_port = port;
}

void NE_Drag_Line::add_second_port(NE_Port_Basic *port)
{
    if(!_drag_from_source)
        _source_port = port;
    else
        _des_port = port;
}

NE_Line_Basic *NE_Drag_Line::create_node_edge()
{
    if(can_connect())
    {
        auto *edge = new NE_Line_Basic(nullptr,_source_port,_des_port,_scene);
        return edge;
    }
    return nullptr;
}

bool NE_Drag_Line::can_connect()
{
    if(is_pair() && not_same_node() && has_same_class())
    {
        return true;
    }
    else if(_des_port->isAutoTransform() &&
    is_pair() && not_same_node() && (!has_same_class()))
    {
        return _des_port->AutoTransform(_source_port->PortClass());
    }
    return false;
}

bool NE_Drag_Line::is_pair()
{
    if(_source_port->PortType()==PORT_EXEC_OUT && _des_port->PortType() == PORT_EXEC_IN)
        return true;
    if(_source_port->PortType()==PORT_PARAM_OUT && _des_port->PortType() == PORT_PARAM_IN)
        return true;
    return false;
}

bool NE_Drag_Line::not_same_node()
{
    if(_source_port->ParentItem() == _des_port->ParentItem())
        return false;
    return true;
}

bool NE_Drag_Line::has_same_class()
{
    if(_source_port->PortClass() == _des_port->PortClass())
        return true;
    return false;
}

NE_Cutting_Line::NE_Cutting_Line(QGraphicsItem *parent)
        :QGraphicsPathItem(parent)
{
    _pen.setWidthF(1.5);
    _pen.setDashPattern({3,3});
}

void NE_Cutting_Line::reset_points()
{
    _line_points = {};
}

void NE_Cutting_Line::update_points(QPointF point)
{
    _line_points.push_back(point);
    update();
}

void NE_Cutting_Line::remove_intersect_edges(const QVector<NE_Line_Basic *>& edges)
{
    foreach (NE_Line_Basic *edge, edges) {
        auto path = QPainterPath();
        path.addPolygon(QPolygonF(_line_points));
        if(edge->collidesWithPath(path))
            edge->remove_self();
    }
}

void NE_Cutting_Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(_pen);

    auto poly = QPolygonF(_line_points);
    painter->drawPolyline(poly);
}
