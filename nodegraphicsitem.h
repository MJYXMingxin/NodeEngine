#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>
#include <QVector>

#include "port.h"

class Node : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    Node(QGraphicsItem *parent=nullptr,
         QGraphicsScene *scene=nullptr,
         QString title="",
         QVector<Port*> in={},
         QVector<Port*> out={},
         bool is_pure=false);
    QRectF boundingRect() const override;
    int width();
    int height();

    void set_scene(QGraphicsScene *scene);

    void init_title();
    void add_port(Port *port,int index=0);
    void add_exec_in_port(Port *port);
    void add_exec_out_port(Port *port);
    void add_param_in_port(Port *port,int index=0);
    void add_param_out_port(Port *port,int index=0);

    void init_exec();
    void init_param_in();
    void init_param_out();

    void init_width_height(bool is_pure=false);
protected:
    int _node_width_min = 20;
    int _node_height_min = 20;
    int _node_width = 50;
    int _node_height = 50;
    int _node_radius = 10;
    int _port_space = 10;

    QPen _pen_default;
    QPen _pen_selected;

    QBrush _brush_background;
    QString _title;
    QGraphicsScene *_scene;

    int _title_height = 35;
    int _title_font_size = 16;
    QFont _title_font = QFont("Arial",_title_font_size);
    QColor _title_color = Qt::white;
    int _title_padding = 3;
    QBrush _brush_title_back = QBrush(QColor(0,0,63,170));

    QGraphicsTextItem *_title_item;
    int _port_padding = 5;

    QVector<Port*> _param_in;
    QVector<Port*> _param_out;

    int _port_index = 0;
    int _max_param_width = 0;
    int _max_output_width = 0;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // NODE_H
