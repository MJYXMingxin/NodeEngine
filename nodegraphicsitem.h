#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>

class Node : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    Node(QGraphicsItem *parent=nullptr);
    QRectF boundingRect() const override;
    int width();
    int height();
private:
    int _node_width = 240;
    int _node_height = 160;
    int _node_radius = 10;

    QPen _pen_default;
    QPen _pen_selected;

    QBrush _brush_background;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // NODE_H
