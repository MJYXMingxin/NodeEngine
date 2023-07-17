#ifndef NE_PORT_BASIC_H
#define NE_PORT_BASIC_H

#include "pch.h"

enum Port_Type
{
    PORT_EXEC_IN = 1001,
    PORT_EXEC_OUT = 1002,
    PORT_PARAM_IN,
    PORT_PARAM_OUT
};

class NE_Node_Basic;
class NE_Port_Basic;
class NE_Line_Basic;
class NE_Scene;

class NE_Port_Basic : public QObject,public QGraphicsItem
{
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
    explicit NE_Port_Basic(QString port_label = "",
                  Class port_class = String,
                  Port_Type type = PORT_EXEC_IN,
                  QGraphicsItem *parent = nullptr);

    [[nodiscard]] QRectF boundingRect() const override;

    void add_to_parent_node(NE_Node_Basic *parent, NE_Scene *scene);

    virtual QPointF get_port_pos();

    void add_edge(NE_Line_Basic *line, NE_Port_Basic *port);

    bool is_connect();

    void conditioned_remove_edge();

    void remove_edge(NE_Line_Basic *line);

    void remove_all_edge();

    static QColor LoadColor(Class pclass);

    void focus()
    {
        this->_is_focused = true;
        this->update();
    }

    void disfocus()
    {
        this->_is_focused = false;
        this->update();
    }

    bool is_connected()
    {
        return !this->_edges.empty();
    }

    [[nodiscard]] int PortIcoSize() const
    {
        return this->_port_ico_size;
    }

    [[nodiscard]] int PortWidth() const
    {
        return this->_port_width;
    }

    Port_Type PortType()
    {
        return this->_port_type;
    }

    QColor PortColor()
    {
        return this->_port_color;
    }

    Class PortClass()
    {
        return this->_port_class;
    }

    NE_Node_Basic *ParentItem()
    {
        return this->_parent_item;
    }

    void setScene(NE_Scene *scene)
    {
        this->_scene = scene;
    }
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
protected:
    QString _port_label;
    Port_Type _port_type;
    Class _port_class;

    bool _is_focused = false;
    QGraphicsDropShadowEffect *_shadow;

    QColor _port_color;
    NE_Node_Basic *_parent_item;

    QPen _pen_default;
    QBrush _brush_default;

    int _font_size = 12;
    QFont _font;
    int _port_ico_size = 20;
    int _port_label_size;
    int _port_width;

    NE_Scene *_scene;
    QPointF _port_pos;

    QVector<NE_Port_Basic*> _connected_ports = {};
    QVector<NE_Line_Basic*> _edges = {};
};

class EXECport : public NE_Port_Basic
{
public:
    explicit EXECport(QString port_label = "",
             Class port_class = String,
             Port_Type type = PORT_EXEC_IN,
             QGraphicsItem *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class EXECInPort : public EXECport
{
public:
    explicit EXECInPort(QString port_label = "",
               Class port_class = Exec,
               Port_Type type = PORT_EXEC_IN,
               QGraphicsItem *parent = nullptr)
            :EXECport(std::move(port_label),
                      port_class, type, parent)
    {}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class EXECOutPort : public EXECport
{
public:
    explicit EXECOutPort(QString port_label = "",
                         Class port_class = Exec,
                         Port_Type type = PORT_EXEC_OUT,
                         QGraphicsItem *parent = nullptr)
                         :EXECport(std::move(port_label),
                                   port_class, type, parent)
    {}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPointF get_port_pos() override;
};

class PARAM_IN_Port : public NE_Port_Basic
{
public:
    explicit PARAM_IN_Port(QString port_label = "",
                           Class port_class = String,
                           Port_Type type = PORT_PARAM_IN,
                           QGraphicsItem *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class PARAM_OUT_Port : public NE_Port_Basic
{
public:
    explicit PARAM_OUT_Port(QString port_label = "",
                            Class port_class = String,
                            Port_Type type = PORT_PARAM_OUT,
                            QGraphicsItem *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPointF get_port_pos() override;
};

class NE_Pin
{
public:
    explicit NE_Pin(QString pin_name = "",
                    Class pin_class = Exec,
                    QString pin_type = "exec");
    virtual void init_port();
    NE_Port_Basic *Port()
    {
        return this->port;
    }
protected:
    void initialize();
protected:
    QString _pin_name;
    Class _pin_class;
    QString _pin_type;
    NE_Port_Basic *port;
};

class NE_NodeInput : public NE_Pin
{
public:
    explicit NE_NodeInput(QString pin_name = "",
                          Class pin_class = Exec,
                          QString pin_type = "exec");
    void init_port() override;
};

class NE_NodeOutput : public NE_Pin
{
public:
    explicit NE_NodeOutput(QString pin_name = "",
                           Class pin_class = Exec,
                           QString pin_type = "exec");
    void init_port() override;
};

#endif // NE_PORT_BASIC_H
