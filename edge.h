#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsPathItem>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsScene>
#include <QWidget>

#include "port.h"

class Edge : public QObject, public QGraphicsPathItem
{
    Q_OBJECT
public:
    Edge(QGraphicsItem *parent=nullptr,
         Port *source=nullptr,
         Port *des=nullptr,
         QGraphicsScene *scene=nullptr,
         QColor color=QColor(255,255,255));
    void update_edge_path();
    void add_to_scene();
protected:
    Port *_source_port;
    Port *_des_port;
    QColor _edge_color;
    QPen _pen_default;
    QGraphicsScene *_scene;

    QGraphicsDropShadowEffect *_shadow = new QGraphicsDropShadowEffect();
    QColor _shadow_color = Qt::yellow;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // EDGE_H
