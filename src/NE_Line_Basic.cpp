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
    this->_pen_default = QPen(this->_edge_color);
    this->_pen_default.setWidthF(2);

    this->setZValue(-1);

    this->_shadow->setOffset(0, 0);
    this->_shadow->setBlurRadius(15);

//    this->setFlags(QGraphicsItem::ItemIsSelectable);
    this->setAcceptHoverEvents(true);
    this->setFlags(QGraphicsItem::ItemIsFocusable);
    this->add_to_scene();
}

void NE_Line_Basic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    this->update_edge_path();
    painter->setPen(this->_pen_default);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(this->path());

    if(this->FocusState())
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

void NE_Line_Basic::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::PointingHandCursor);
    this->focus();
    this->_source_port->focus();
    this->_des_port->focus();
    QGraphicsItem::hoverEnterEvent(event);
}

void NE_Line_Basic::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    unsetCursor();
    this->disfocus();
    this->_source_port->disfocus();
    this->_des_port->disfocus();
    QGraphicsItem::hoverLeaveEvent(event);
}

void NE_Line_Basic::update_edge_path()
{
    auto source_pos = this->_source_port->get_port_pos();
    auto des_pos = this->_des_port->get_port_pos();

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
    this->setPath(path);
}

void NE_Line_Basic::add_to_scene()
{
    this->_scene->addItem(this);
    this->_source_port->add_edge(this,this->_des_port);
    this->_des_port->add_edge(this,this->_source_port);
    this->_source_port->update();
    this->_des_port->update();
}

void NE_Line_Basic::remove_self()
{
    this->_scene->removeItem(this);
    this->_scene->View()->remove_edge(this);
    this->_source_port->remove_edge(this);
    this->_des_port->remove_edge(this);
}

bool NE_Line_Basic::FocusState()
{
    return this->_is_focused;
}

void NE_Line_Basic::focus()
{
    this->_is_focused = true;
    this->_source_port->focus();
    this->_des_port->focus();
    this->update();
}

void NE_Line_Basic::disfocus()
{
    this->_is_focused = false;
    this->_source_port->disfocus();
    this->_des_port->disfocus();
    this->update();
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
         _scene(scene)
{
    this->_pen_default = QPen(this->_edge_color);
    this->_pen_default.setWidthF(2);
    this->setZValue(-1);
}

void NE_Drag_Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    this->update_edge_path();
    painter->setPen(this->_pen_default);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(this->path());
}

void NE_Drag_Line::update_edge_path()
{
    QPoint source_pos = this->_source_pos;
    QPoint des_pos = this->_des_pos;

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
    this->setPath(path);
}

void NE_Drag_Line::update_position(QPointF position)
{
    QPoint pos = QPoint(position.x(),position.y());
    if(this->_drag_from_source)
        this->_des_pos = pos;
    else
        this->_source_pos = pos;
    this->update_edge_path();
    this->update();
}

void NE_Drag_Line::add_first_port(NE_Port_Basic *port)
{
    if(this->_drag_from_source)
        this->_source_port = port;
    else
        this->_des_port = port;
}

void NE_Drag_Line::add_second_port(NE_Port_Basic *port)
{
    if(!this->_drag_from_source)
        this->_source_port = port;
    else
        this->_des_port = port;
}

NE_Line_Basic *NE_Drag_Line::create_node_edge()
{
    if(this->can_connect())
    {
        auto *edge = new NE_Line_Basic(nullptr,this->_source_port,this->_des_port,this->_scene);
        return edge;
    }
    return nullptr;
}

bool NE_Drag_Line::can_connect()
{
    if(this->is_pair() && this->not_same_node() && this->has_same_class())
    {
        return true;
    }
    return false;
}

bool NE_Drag_Line::is_pair()
{
    if(this->_source_port->PortType()==PORT_EXEC_OUT && this->_des_port->PortType() == PORT_EXEC_IN)
        return true;
    if(this->_source_port->PortType()==PORT_PARAM_OUT && this->_des_port->PortType() == PORT_PARAM_IN)
        return true;
    return false;
}

bool NE_Drag_Line::not_same_node()
{
    if(this->_source_port->ParentItem() == this->_des_port->ParentItem())
        return false;
    return true;
}

bool NE_Drag_Line::has_same_class()
{
    if(this->_source_port->PortClass() == this->_des_port->PortClass())
        return true;
    return false;
}

NE_Cutting_Line::NE_Cutting_Line(QGraphicsItem *parent)
        :QGraphicsPathItem(parent)
{
    this->_pen.setWidthF(1.5);
    this->_pen.setDashPattern({3,3});
}

void NE_Cutting_Line::reset_points()
{
    this->_line_points = {};
}

void NE_Cutting_Line::update_points(QPointF point)
{
    this->_line_points.push_back(point);
    this->update();
}

void NE_Cutting_Line::remove_intersect_edges(QVector<NE_Line_Basic *> edges)
{
            foreach (NE_Line_Basic *edge, edges) {
            auto path = QPainterPath();
            path.addPolygon(QPolygonF(this->_line_points));
            if(edge->collidesWithPath(path))
                edge->remove_self();
        }
}

void NE_Cutting_Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(this->_pen);

    auto poly = QPolygonF(this->_line_points);
    painter->drawPolyline(poly);
}
