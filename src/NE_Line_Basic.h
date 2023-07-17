#ifndef NE_LINE_BASIC_H
#define NE_LINE_BASIC_H

#include "pch.h"

class NE_View;
class NE_Port_Basic;


class NE_Line_Basic : public QObject, public QGraphicsPathItem
{
Q_OBJECT
public:
    explicit NE_Line_Basic(QGraphicsItem *parent=nullptr,
                  NE_Port_Basic *source=nullptr,
                  NE_Port_Basic *des=nullptr,
                  NE_Scene *scene=nullptr);
    void update_edge_path();
    void add_to_scene();

    void remove_self();

    bool FocusState();
    void focus();
    void disfocus();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

public:
    NE_Port_Basic *_source_port;
    NE_Port_Basic *_des_port;

protected:
    QColor _edge_color;
    QPen _pen_default;
    NE_Scene *_scene;

    bool _is_focused = false;

    QGraphicsDropShadowEffect *_shadow;
    QColor _shadow_color;
};


class NE_Drag_Line : public QObject, public QGraphicsPathItem
{
Q_OBJECT
public:
    explicit NE_Drag_Line(QGraphicsItem *parent=nullptr,
                 bool drag_from_source=true,
                 QPoint source_pos=QPoint(0,0),
                 QPoint des_pos=QPoint(0,0),
                 QColor edge_color=QColor(255,255,255),
                 NE_Scene *scene=nullptr);
    void update_edge_path();
    void update_position(QPointF position);
    void add_first_port(NE_Port_Basic *port);
    void add_second_port(NE_Port_Basic *port);
    NE_Line_Basic *create_node_edge();
    bool can_connect();
    bool is_pair();
    bool not_same_node();
    bool has_same_class();

protected:
    QPoint _source_pos;
    QPoint _des_pos;
    bool _drag_from_source;
    QColor _edge_color;
    NE_Scene *_scene;

    NE_Port_Basic *_source_port;
    NE_Port_Basic *_des_port;
    QPen _pen_default;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class NE_Cutting_Line : public QObject, public QGraphicsPathItem
{
public:
    explicit NE_Cutting_Line(QGraphicsItem *parent = nullptr);

    void reset_points();
    void update_points(QPointF point);
    void remove_intersect_edges(QVector<NE_Line_Basic*> edges);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
protected:
    QVector<QPointF> _line_points = {};

    QPen _pen = QPen(Qt::white);

};

#endif // NE_LINE_BASIC_H
