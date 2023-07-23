#ifndef NE_NODE_BASIC_H
#define NE_NODE_BASIC_H

#include "pch.h"

class NE_Port_Basic;
class NE_Line_Basic;
class NE_Pin;
class NE_NodeInput;
class NE_NodeOutput;

class NE_Node_Basic : public QObject, public QGraphicsItem
{
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
    explicit NE_Node_Basic(QString title = "Test",
                  QVector<NE_Port_Basic*> in = {},
                  QVector<NE_Port_Basic*> out = {},
                  FunctionType functype = Normal,
                  QPointF node_pos=QPointF(0,0),
                  QGraphicsItem *parent = nullptr,
                  NE_Scene *scene = nullptr);

    [[nodiscard]] QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void set_scene(NE_Scene *scene);

    [[maybe_unused]] void init_exec();

    void init_param();

    void init_ports();

    void add_port(NE_Port_Basic *port, int index = 0);

    void add_exec_in_port(NE_Port_Basic *port, int index);

    void add_exec_out_port(NE_Port_Basic *port, int index);

    void add_param_in_port(NE_Port_Basic *port, int index);

    void add_param_out_port(NE_Port_Basic *port, int index);

    void init_width_height();

    void loadConfig();

    void init_title();

    void add_connected(NE_Node_Basic* node, NE_Line_Basic* edge);

    void remove_connected(NE_Node_Basic* node, NE_Line_Basic* edge);

    void remove_self();

protected:
    QJsonObject _obj;
    Config_Node _config;
//    int _node_width_min = 20;
    int _node_height_min = 20;
    int _node_width = 50;
    int _node_height = 50;
    int _node_radius = 10;
    int _port_space = 15;
    int _port_padding = 5;

    QPointF _node_pos;
    //Node 边框
    QPen _pen_default;
    QPen _pen_selected;
    //Node 背景
    QBrush _brush_background;

    QString _title;
    NE_Scene *_scene;

    int _title_height;
    int _title_font_size;
    int _title_padding;
    QFont _title_font;
    QColor _title_color;
    QBrush _brush_title_back;
    QGraphicsTextItem *_title_item;

    FunctionType _func_type;

    int _max_param_width = 0;
    int _max_output_width = 0;

    QVector<NE_Port_Basic*> _param_in;
    QVector<NE_Port_Basic*> _param_out;

    QVector<NE_Line_Basic*> _edges;
    QVector<NE_Node_Basic*> _connected_nodes;
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

class NE_Node : public NE_Node_Basic
{
Q_OBJECT
public:
    explicit NE_Node(QString title = "Test",
                     QString description = "",
                     QVector<NE_NodeInput *> in_pins = {},
                     QVector<NE_NodeOutput *> out_pins = {},
                     bool need_port_transform = false,
                     FunctionType functype = Normal);
    [[nodiscard]] virtual int run_node() = 0;
    static QVector<NE_Port_Basic *> InitNodeInput(const QVector<NE_NodeInput*>& pins);
    static QVector<NE_Port_Basic *> InitNodeOutput(const QVector<NE_NodeOutput*>& pins);

    NE_NodeInput *get_input_pin(int index) { return input_pins[index]; }
    NE_NodeOutput *get_output_pin(int index) { return output_pins[index]; }

protected:
    QString node_title = "";
    QString node_description = "";
    QVector<NE_NodeInput *> input_pins = {};
    QVector<NE_NodeOutput *> output_pins = {};
    bool _input_data_ready = false;
    bool _output_data_ready = false;
    bool _need_port_transform = false;
};

#endif
