//#include <utility>
#include "NE_Node_Basic.h"

NE_Node_Basic::NE_Node_Basic(QString title,
                             QVector<NE_Port_Basic*> in,
                             QVector<NE_Port_Basic*> out,
                             FunctionType functype,
                             QPointF node_pos,
                             QGraphicsItem *parent,
                             NE_Scene *scene)
                             : QGraphicsItem(parent),
                             _title(std::move(title)),
                             _scene(scene),
                             _param_in(std::move(in)),
                             _param_out(std::move(out)),
                               _func_type(functype),
                             _node_pos(node_pos),
                             _title_height(35),
                             _title_font_size(16),
                             _title_padding(3),
                             _title_item(nullptr)
{
    loadConfig();
    setFlags(QGraphicsItem::ItemIsSelectable |
                   QGraphicsItem::ItemIsMovable |
                   QGraphicsItem::ItemIsFocusable |
                   QGraphicsItem::ItemSendsGeometryChanges);
    init_width_height();
    init_title();

    if(functype!=Pure)
        _node_height_min += 20;
//        init_exec();
    init_param();
}

QRectF NE_Node_Basic::boundingRect() const
{
    return {0,0,
            static_cast<qreal>(_node_width),
            static_cast<qreal>(_node_height)};
}

void NE_Node_Basic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //node
    auto node_outline = QPainterPath();
    node_outline.addRoundedRect(0,0,
                                _node_width,
                                _node_height,
                                _node_radius,
                                _node_radius);
    painter->setPen(Qt::NoPen);
    painter->setBrush(_brush_background);
    painter->drawPath(node_outline.simplified());

    //title
    auto title_outline = QPainterPath();
    title_outline.setFillRule(Qt::WindingFill);
    title_outline.addRoundedRect(0,0,
                                 _node_width,
                                 _title_height,
                                 _node_radius,
                                 _node_radius);
    title_outline.addRect(0,_title_height-_node_radius,
                          _node_radius,_node_radius);
    title_outline.addRect(_node_width-_node_radius,
                          _title_height-_node_radius,
                          _node_radius,_node_radius);
    painter->setPen(Qt::NoPen);

    painter->setBrush(_brush_title_back);
    painter->drawPath(title_outline.simplified());

    //outline
    isSelected()?
    painter->setPen(_pen_selected):painter->setPen(_pen_default);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(node_outline);
}

void NE_Node_Basic::set_scene(NE_Scene *scene)
{
    _scene = scene;
    foreach(NE_Port_Basic* in,_param_in){
        in->setScene(scene);
    }
    foreach(NE_Port_Basic* out,_param_out){
        out->setScene(scene);
    }
}

void NE_Node_Basic::init_exec()
{
    auto *in = new EXECInPort();
    auto *out = new EXECOutPort();
    add_port(in);
    add_port(out);
    //        _port_index += 1;
}

void NE_Node_Basic::init_param()
{
    for(auto i = 0; i < _param_in.size(); ++i)
        add_port(_param_in[i], i);
    for(auto i = 0; i < _param_out.size(); ++i)
        add_port(_param_out[i], i);
}

void NE_Node_Basic::init_ports()
{
    init_param();
}

void NE_Node_Basic::add_port(NE_Port_Basic *port, int index)
{
    switch(port->PortType())
    {
        case PORT_EXEC_IN:
            add_exec_in_port(port, index);
            break;
        case PORT_EXEC_OUT:
            add_exec_out_port(port, index);
            break;
        case PORT_PARAM_IN:
            add_param_in_port(port, index);
            break;
        case PORT_PARAM_OUT:
            add_param_out_port(port, index);
            break;
    }
}

void NE_Node_Basic::add_exec_in_port(NE_Port_Basic *port, int index)
{
    port->add_to_parent_node(this, _scene);
    port->setPos(_port_padding,
                 _title_height + index*(_port_padding+port->PortIcoSize()));
}

void NE_Node_Basic::add_exec_out_port(NE_Port_Basic *port, int index)
{
    port->add_to_parent_node(this,_scene);
    port->setPos(_node_width/*-_port_padding*/-port->PortWidth(),
                 _title_height + index*(_port_padding+port->PortIcoSize()));
}

void NE_Node_Basic::add_param_in_port(NE_Port_Basic *port, int index)
{
    port->add_to_parent_node(this,_scene);
    port->setPos(_port_padding,
                 _title_height+index*(_port_padding+port->PortIcoSize()));
}

void NE_Node_Basic::add_param_out_port(NE_Port_Basic *port, int index)
{
    port->add_to_parent_node(this,_scene);
    port->setPos(_node_width-_port_padding-port->PortWidth(),
                 _title_height+index*(_port_padding+port->PortIcoSize()));
}

void NE_Node_Basic::init_width_height()
{
    auto cal_unicode = [this]{
        int len = 0;
        for(auto i:_title)
        {
//            if(i.unicode() >= 0xFF01 && i.unicode() <= 0xFF5E)
//                len += _title_font_size;
            if(i.unicode() >= 0x0020 && i.unicode() <= 0x007E)
                len += static_cast<int>(_title_font_size*0.7);
            else
                len += _title_font_size;
        }
        return len;
    };
    //init _node_height
    int param_height,out_height;
    if(!_param_in.empty())
        param_height = (static_cast<int>(_param_in.size()))*
                (_param_in[0]->PortIcoSize()+_port_padding)+
                _title_height;
    else
        param_height = _title_height;

    param_height>_node_height?
            param_height+=0:param_height=_node_height_min;
    if(_node_height < param_height)
        _node_height = param_height;

    if(!_param_out.empty())
        out_height = (static_cast<int>(_param_out.size()))*
                (_param_out[0]->PortIcoSize()+_port_padding)+
                _title_height;
    else
        out_height = _title_height;

    out_height>_node_height?
    out_height:out_height=_node_height_min;
    if(_node_height < out_height)
        _node_height = out_height;

    //init _node_width
    _max_param_width = 0;
    if(!_param_in.empty()){
        foreach (NE_Port_Basic *port, _param_in) {
            if(_max_param_width < port->PortWidth())
                _max_param_width = port->PortWidth();
        }
    }

    _max_output_width = 0;
    if(!_param_out.empty()){
        foreach (NE_Port_Basic *port, _param_out){
            if(_max_output_width < port->PortWidth())
                _max_output_width = port->PortWidth();
        }
    }

    if(_node_width < _max_param_width + _max_output_width + _port_space)
        _node_width = _max_param_width + _max_output_width + _port_space;

    if(_node_width < cal_unicode() + 2 * 10 + 4*_port_padding)
        _node_width = cal_unicode() + 2 * 10 + 4*_port_padding;

    //        if(_node_width < _title.length() * _title_font_size + 2 * _port_padding)
    //            _node_width = _title.length() * _title_font_size + 2 * _port_padding;
}

void NE_Node_Basic::loadConfig()
{
    _obj = SearchObj(Node);
    _config.Default_Pen_Color = _obj["Default_Pen_Color"].toString();
    _config.Selected_Pen_Color = _obj["Selected_Pen_Color"].toString();
    _config.Background_Color = _obj["Background_Color"].toString();
    _config.Default_Pen_Width = _obj["Default_Pen_Width"].toDouble();
    _config.Selected_Pen_Width = _obj["Selected_Pen_Width"].toDouble();
    _config.Title_Height = _obj["Title_Height"].toInt();
    _config.Title_Font_Size = _obj["Title_Font_Size"].toInt();
    _config.Title_Padding = _obj["Title_Padding"].toInt();
    _config.Title_Color = _obj["Title_Color"].toString();
    _config.Pure_Title_Back = _obj["Pure_Title_Back"].toString();
    _config.Func_Title_Back = _obj["Func_Title_Back"].toString();
    _config.Inline_Title_Back = _obj["Inline_Title_Back"].toString();

    QColor tmp;
    tmp.setNamedColor(_config.Default_Pen_Color);
    _pen_default = QPen(tmp);
    tmp.setNamedColor(_config.Selected_Pen_Color);
    _pen_selected = QPen(tmp);
    tmp.setNamedColor(_config.Background_Color);
    _brush_background = QBrush(tmp);

    _pen_default.setWidthF(_config.Default_Pen_Width);
    _pen_selected.setWidthF(_config.Selected_Pen_Width);

    _title_height = _config.Title_Height;
    _title_font_size = _config.Title_Font_Size;
    _title_padding = _config.Title_Padding;
    _title_font = QFont("Arial",_title_font_size);
    _title_color = _config.Title_Color;

    switch(_func_type)
    {
        case Normal:
            tmp.setNamedColor(_config.Func_Title_Back);
            break;
        case Pure:
            tmp.setNamedColor(_config.Pure_Title_Back);
            break;
        case Inline:
            tmp.setNamedColor(_config.Inline_Title_Back);
            break;
        default:
            break;
    }
    _brush_title_back = QBrush(tmp);
}

void NE_Node_Basic::init_title()
{
    _title_item = new QGraphicsTextItem(this);
    _title_item->setPlainText(_title);
    _title_item->setFont(_title_font);
    _title_item->setDefaultTextColor(_title_color);
//    _title_item->setPos(_title_padding, _title_padding);
    _title_item->setPos(static_cast<qreal>(_node_width)/2-_title_item->boundingRect().width()/2,
                              _title_padding);
}

void NE_Node_Basic::add_connected(NE_Node_Basic *node, NE_Line_Basic *edge)
{
    _connected_nodes.append(node);
    _edges.append(edge);
}

void NE_Node_Basic::remove_connected(NE_Node_Basic *node, NE_Line_Basic *edge)
{
    for(auto i=0; i<_connected_nodes.size(); ++i)
    {
        if(_connected_nodes[i]==node)
        {
            _connected_nodes.remove(i);
            break;
        }
    }

    for(auto i=0; i<_edges.size(); ++i)
    {
        if(_edges[i]==edge)
        {
            _edges.remove(i);
            break;
        }
    }
}

void NE_Node_Basic::remove_self()
{
    QVector<NE_Line_Basic*> edges = _edges;
            foreach (NE_Line_Basic *edge, edges) {
            edge->remove_self();
        }
    _scene->removeItem(this);
    _scene->View()->remove_node(this);
}

QVariant NE_Node_Basic::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemPositionChange)
    {
        if(!_edges.empty())
        {
            foreach(NE_Line_Basic *edge, _edges){
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
                 bool need_port_transform,
                 FunctionType functype)
                 : node_title(std::move(title)),
                 node_description(std::move(description)),
                 input_pins(std::move(in_pins)),
                 output_pins(std::move(out_pins)),
                 _need_port_transform(need_port_transform),
                 NE_Node_Basic(std::move(title),
                               InitNodeInput(in_pins),
                               InitNodeOutput(out_pins),
                               functype)
{
}

QVector<NE_Port_Basic *> NE_Node::InitNodeInput(const QVector<NE_NodeInput *>& pins) {
    QVector<NE_Port_Basic *> res{};
    foreach(NE_NodeInput *pin, pins){
        res.push_back(pin->Port());
    }
    return res;
}

QVector<NE_Port_Basic *> NE_Node::InitNodeOutput(const QVector<NE_NodeOutput *>& pins) {
    QVector<NE_Port_Basic *> res{};
    foreach(NE_NodeOutput *pin, pins){
        res.push_back(pin->Port());
    }
    return res;
}
