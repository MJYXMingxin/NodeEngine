#ifndef PORT_H
#define PORT_H

#include <QGraphicsItem>
#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPainter>

enum Port_Type
{
    EXEC_IN = 1001,
    EXEC_OUT = 1002,
    PARAM_IN,
    PARAM_OUT
};

class Port : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    Port(QString port_label="",
         QString port_class="str",
         QColor port_color=QColor(255,255,255),
         Port_Type type = EXEC_IN,
         QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    Port_Type type();
    int width();
    int icoSize();
    void add_to_parent_node(QGraphicsItem *parent,QGraphicsScene *scene);
protected:
    QString _port_label;
    QString _port_class;
    QColor _port_color;
    Port_Type _port_type;

    QPen _pen_default;
    QBrush _brush_default;

    int _font_size = 12;
    QFont _font;
    int _port_ico_size = 20;
    int _port_label_size;
    int _port_width;

    QGraphicsItem *_parent_item;
    QGraphicsScene *_scene;
};

class EXECport : public Port
{
public:
    EXECport(QString port_label="",
             QString port_class="str",
             QColor port_color=QColor(255,255,255),
             Port_Type type = EXEC_IN,
             QGraphicsItem *parent = nullptr);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class EXECInPort : public EXECport
{
public:
    EXECInPort(QString port_label="",
               QString port_class="str",
               QColor port_color=QColor(255,255,255),
               Port_Type type = EXEC_IN,
               QGraphicsItem *parent = nullptr);
};

class EXECOutPort : public EXECport
{
public:
    EXECOutPort(QString port_label="",
    QString port_class="str",
    QColor port_color=QColor(255,255,255),
    Port_Type type = EXEC_OUT,
    QGraphicsItem *parent = nullptr);
};

class ParamInPort : public Port
{
public:
    ParamInPort(QString port_label="",
              QString port_class="str",
              QColor port_color=QColor(255,255,255),
              Port_Type type = PARAM_IN,
              QGraphicsItem *parent = nullptr);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class ParamOutPort : public Port
{
public:
    ParamOutPort(QString port_label="",
                 QString port_class="str",
                 QColor port_color=QColor(255,255,255),
                 Port_Type type = PARAM_IN,
                 QGraphicsItem *parent = nullptr);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // PORT_H
