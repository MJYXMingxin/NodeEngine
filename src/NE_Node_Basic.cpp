//#include <utility>
#include "NE_Node_Basic.h"

NE_Node_Basic::NE_Node_Basic(QString title,
                             QVector<NE_Port_Basic*> in,
                             QVector<NE_Port_Basic*> out,
                             bool is_pure,
                             QPointF node_pos,
                             QGraphicsItem *parent,
                             NE_Scene *scene)
                             : QGraphicsItem(parent),
                             _title(std::move(title)),
                             _scene(scene),
                             _param_in(std::move(in)),
                             _param_out(std::move(out)),
                             _is_pure(is_pure),
                             _node_pos(node_pos)
{
    this->loadConfig();
    this->setFlags(QGraphicsItem::ItemIsSelectable |
                   QGraphicsItem::ItemIsMovable |
                   QGraphicsItem::ItemIsFocusable |
                   QGraphicsItem::ItemSendsGeometryChanges);
    this->init_width_height();
    this->init_title();

    if(!is_pure)
        this->_node_height_min += 20;
//        this->init_exec();
    this->init_param();
}

QRectF NE_Node_Basic::boundingRect() const
{
    return {0,0,
            static_cast<qreal>(this->_node_width),
            static_cast<qreal>(this->_node_height)};
}

void NE_Node_Basic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //node
    auto node_outline = QPainterPath();
    node_outline.addRoundedRect(0,0,
                                this->_node_width,
                                this->_node_height,
                                this->_node_radius,
                                this->_node_radius);
    painter->setPen(Qt::NoPen);
    painter->setBrush(this->_brush_background);
    painter->drawPath(node_outline.simplified());

    //title
    auto title_outline = QPainterPath();
    title_outline.setFillRule(Qt::WindingFill);
    title_outline.addRoundedRect(0,0,
                                 this->_node_width,
                                 this->_title_height,
                                 this->_node_radius,
                                 this->_node_radius);
    title_outline.addRect(0,this->_title_height-this->_node_radius,
                          this->_node_radius,this->_node_radius);
    title_outline.addRect(this->_node_width-this->_node_radius,
                          this->_title_height-this->_node_radius,
                          this->_node_radius,this->_node_radius);
    painter->setPen(Qt::NoPen);
    this->_is_pure?
    painter->setBrush(this->_brush_pure_title_back):
    painter->setBrush(this->_brush_function_title_back);
    painter->drawPath(title_outline.simplified());

    //outline
    this->isSelected()?
    painter->setPen(this->_pen_selected):painter->setPen(this->_pen_default);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(node_outline);
}

void NE_Node_Basic::set_scene(NE_Scene *scene)
{
    this->_scene = scene;
    foreach(NE_Port_Basic* in,this->_param_in){
        in->setScene(scene);
    }
    foreach(NE_Port_Basic* out,this->_param_out){
        out->setScene(scene);
    }
}

void NE_Node_Basic::init_exec()
{
    auto *in = new EXECInPort();
    auto *out = new EXECOutPort();
    this->add_port(in);
    this->add_port(out);
    //        this->_port_index += 1;
}

void NE_Node_Basic::init_param()
{
    for(auto i = 0; i < this->_param_in.size(); ++i)
        this->add_port(this->_param_in[i], i);
    for(auto i = 0; i < this->_param_out.size(); ++i)
        this->add_port(this->_param_out[i], i);
}

void NE_Node_Basic::init_ports()
{
    this->init_param();
}

void NE_Node_Basic::add_port(NE_Port_Basic *port, int index)
{
    switch(port->PortType())
    {
        case PORT_EXEC_IN:
            this->add_exec_in_port(port, index);
            break;
        case PORT_EXEC_OUT:
            this->add_exec_out_port(port, index);
            break;
        case PORT_PARAM_IN:
            this->add_param_in_port(port, index);
            break;
        case PORT_PARAM_OUT:
            this->add_param_out_port(port, index);
            break;
    }
}

void NE_Node_Basic::add_exec_in_port(NE_Port_Basic *port, int index)
{
    port->add_to_parent_node(this, this->_scene);
    port->setPos(this->_port_padding,
                 this->_title_height + index*(this->_port_padding+port->PortIcoSize()));
}

void NE_Node_Basic::add_exec_out_port(NE_Port_Basic *port, int index)
{
    port->add_to_parent_node(this,this->_scene);
    port->setPos(this->_node_width/*-this->_port_padding*/-port->PortWidth(),
                 this->_title_height + index*(this->_port_padding+port->PortIcoSize()));
}

void NE_Node_Basic::add_param_in_port(NE_Port_Basic *port, int index)
{
    port->add_to_parent_node(this,this->_scene);
    port->setPos(this->_port_padding,
                 this->_title_height+index*(this->_port_padding+port->PortIcoSize()));
}

void NE_Node_Basic::add_param_out_port(NE_Port_Basic *port, int index)
{
    port->add_to_parent_node(this,this->_scene);
    port->setPos(this->_node_width-this->_port_padding-port->PortWidth(),
                 this->_title_height+index*(this->_port_padding+port->PortIcoSize()));
}

void NE_Node_Basic::init_width_height()
{
    auto cal_unicode = [this]{
        int len = 0;
        for(auto i = 0; i < this->_title.length(); ++i)
        {
            ushort code = this->_title.at(i).unicode();
            if (code >= 0xFF01 && code <= 0xFF5E)//全角
                len += this->_title_font_size;
            else if(code >= 0x0020 && code <= 0x007E)//半角
                len += static_cast<int>(this->_title_font_size*0.6);
            else//其他字符
                len += this->_title_font_size;
        }
        return len;
    };
    //init _node_height
    int param_height,out_height;
    if(!this->_param_in.empty())
        param_height = (static_cast<int>(this->_param_in.size()))*
                (this->_param_in[0]->PortIcoSize()+this->_port_padding)+
                this->_title_height;
    else
        param_height = this->_title_height;
    //        is_pure?param_height+=0:param_height+=20+this->_port_padding;
    param_height>this->_node_height?
            param_height+=0:param_height=this->_node_height_min;
    if(this->_node_height < param_height)
        this->_node_height = param_height;

    if(!this->_param_out.empty())
        out_height = (static_cast<int>(this->_param_out.size()))*
                (this->_param_out[0]->PortIcoSize()+this->_port_padding)+
                this->_title_height;
    else
        out_height = this->_title_height;
    //        is_pure?out_height:out_height+=20+this->_port_padding;
    out_height>this->_node_height?
    out_height:out_height=this->_node_height_min;
    if(this->_node_height < out_height)
        this->_node_height = out_height;

    //init _node_width
    this->_max_param_width = 0;
    if(!this->_param_in.empty()){
        foreach (NE_Port_Basic *port, this->_param_in) {
            if(this->_max_param_width < port->PortWidth())
                this->_max_param_width = port->PortWidth();
        }
    }

    this->_max_output_width = 0;
    if(!this->_param_out.empty()){
        foreach (NE_Port_Basic *port, this->_param_out){
            if(this->_max_output_width < port->PortWidth())
                this->_max_output_width = port->PortWidth();
        }
    }

    if(this->_node_width < this->_max_param_width + this->_max_output_width + this->_port_space)
        this->_node_width = this->_max_param_width + this->_max_output_width + this->_port_space;

    if(this->_node_width < cal_unicode() + 2 * 10 + 4*this->_port_padding)
        this->_node_width = cal_unicode() + 2 * 10 + 4*this->_port_padding;

    //        if(this->_node_width < this->_title.length() * this->_title_font_size + 2 * this->_port_padding)
    //            this->_node_width = this->_title.length() * this->_title_font_size + 2 * this->_port_padding;
}

void NE_Node_Basic::loadConfig()
{
    this->_pen_default = QPen(QColor(49,49,49));
    this->_pen_selected = QPen(QColor(255,238,0));
    this->_brush_background = QBrush(QColor(21,21,21,170));

    this->_pen_default.setWidthF(3);
    this->_pen_selected.setWidthF(3);

    this->_title_height = 35;
    this->_title_font_size = 16;
    this->_title_padding = 3;
    this->_title_font = QFont("Arial",this->_title_font_size);
    this->_title_color = Qt::white;
    this->_brush_pure_title_back = QBrush(QColor(153,255,34,170));
    this->_brush_function_title_back = QBrush(QColor(22,97,171,170));
}

void NE_Node_Basic::init_title()
{
    this->_title_item = new QGraphicsTextItem(this);
    this->_title_item->setPlainText(this->_title);
    this->_title_item->setFont(this->_title_font);
    this->_title_item->setDefaultTextColor(this->_title_color);
//    this->_title_item->setPos(this->_title_padding, this->_title_padding);
    this->_title_item->setPos(static_cast<qreal>(this->_node_width)/2-this->_title_item->boundingRect().width()/2,
                              this->_title_padding);
}

void NE_Node_Basic::add_connected(NE_Node_Basic *node, NE_Line_Basic *edge)
{
    this->_connected_nodes.append(node);
    this->_edges.append(edge);
}

void NE_Node_Basic::remove_connected(NE_Node_Basic *node, NE_Line_Basic *edge)
{
    for(auto i=0; i<this->_connected_nodes.size(); ++i)
    {
        if(this->_connected_nodes[i]==node)
        {
            this->_connected_nodes.remove(i);
            break;
        }
    }

    for(auto i=0; i<this->_edges.size(); ++i)
    {
        if(this->_edges[i]==edge)
        {
            this->_edges.remove(i);
            break;
        }
    }
}

void NE_Node_Basic::remove_self()
{
    QVector<NE_Line_Basic*> edges = this->_edges;
            foreach (NE_Line_Basic *edge, edges) {
            edge->remove_self();
        }
    this->_scene->removeItem(this);
    this->_scene->View()->remove_node(this);
}

QVariant NE_Node_Basic::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemPositionChange)
    {
        if(!this->_edges.empty())
        {
            foreach(NE_Line_Basic *edge, this->_edges){
                edge->update();
            }
        }
    }
    return QGraphicsItem::itemChange(change,value);
}

NE_Node::NE_Node(QString title,
                 QString description,
                 QVector<NE_NodeInput *> in_pins,
                 QVector<NE_NodeOutput *> out_pins,
                 bool is_pure)
                 : node_title(std::move(title)),
                 node_description(std::move(description)),
                 input_pins(std::move(in_pins)),
                 output_pins(std::move(out_pins)),
                 NE_Node_Basic(std::move(title),
                               InitNodeInput(in_pins),
                               InitNodeOutput(out_pins),
                               is_pure)
{
}

QVector<NE_Port_Basic *> NE_Node::InitNodeInput(QVector<NE_NodeInput *> pins) {
    QVector<NE_Port_Basic *> res;
    foreach(NE_NodeInput *pin, pins){
        res.push_back(pin->Port());
    }
    return res;
}

QVector<NE_Port_Basic *> NE_Node::InitNodeOutput(QVector<NE_NodeOutput *> pins) {
    QVector<NE_Port_Basic *> res;
    foreach(NE_NodeOutput *pin, pins){
        res.push_back(pin->Port());
    }
    return res;
}
