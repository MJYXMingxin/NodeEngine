#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsPathItem>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsScene>
#include <QWidget>

#include "nodegraphicsscene.h"

class NodeGraphicsView;
class Port;
class Edge : public QObject, public QGraphicsPathItem
{
    Q_OBJECT
public:
    Edge(QGraphicsItem *parent=nullptr,
         Port *source=nullptr,
         Port *des=nullptr,
         NodeGraphicsScene *scene=nullptr,
         QColor color=QColor(255,255,255));
    void update_edge_path();
    void add_to_scene();

    void remove_self();
public:
    Port *_source_port;
    Port *_des_port;
protected:
    QColor _edge_color;
    QPen _pen_default;
    NodeGraphicsScene *_scene;

    QGraphicsDropShadowEffect *_shadow = new QGraphicsDropShadowEffect();
    QColor _shadow_color = Qt::yellow;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class DragEdge : public QObject, public QGraphicsPathItem
{
public:
    DragEdge(QGraphicsItem *parent=nullptr,
             bool drag_from_source=true,
             QPoint source_pos=QPoint(0,0),
             QPoint des_pos=QPoint(0,0),
             QColor edge_color=QColor(255,255,255),
             NodeGraphicsScene *scene=nullptr);
    void update_edge_path();
    void update_position(QPointF position);
    void add_first_port(Port *port);
    void add_second_port(Port *port);
    Edge *create_node_edge();
    bool can_connect();
    bool is_pair();
    bool not_same_node();
    bool has_same_class();

protected:
    QPoint _source_pos;
    QPoint _des_pos;
    bool _drag_from_source;
    QColor _edge_color;
    NodeGraphicsScene *_scene;

    Port *_source_port;
    Port *_des_port;
    QPen _pen_default;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // EDGE_H
