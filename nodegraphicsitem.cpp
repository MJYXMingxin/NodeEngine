#include "nodegraphicsitem.h"

Node::Node(QGraphicsItem *parent,QGraphicsScene *scene,QString title,QVector<Port*> in,QVector<Port*> out,bool is_pure)
    :QGraphicsItem(parent)
{
    this->_scene = scene;
    this->_pen_default = QPen(QColor(21,21,21));
    this->_pen_selected = QPen(QColor(255,238,0,170));
    this->_brush_background = QBrush(QColor(21,21,21,170));

    this->setFlags(QGraphicsItem::ItemIsSelectable |
                   QGraphicsItem::ItemIsMovable );

    this->_title = title;
    this->init_title();

    this->_param_in = in;
    this->_param_out = out;

    this->init_width_height(is_pure);

    if(!is_pure)
        this->init_exec();

    this->init_param_in();
    this->init_param_out();
}

QRectF Node::boundingRect() const
{
    return QRectF(0,0,this->_node_width,this->_node_height);
}

void Node::init_exec()
{
    auto *execin = new EXECInPort;
    auto *execout = new EXECOutPort;
    this->add_port(execin);
    this->add_port(execout);
    this->_port_index+=1;
}

void Node::init_param_in()
{
    for(auto i=0; i<this->_param_in.size(); ++i)
    {
        this->add_port(this->_param_in[i],i+this->_port_index);
    }
}

void Node::init_param_out()
{
    for(auto i=0; i<this->_param_out.size(); ++i)
    {
        this->add_port(this->_param_out[i],i+this->_port_index);
    }
}

void Node::init_width_height(bool is_pure)
{
    int param_height = (this->_param_in.size())*(this->_param_in[0]->icoSize()+this->_port_padding)+this->_title_height;
    is_pure?param_height+=0:param_height+=20+this->_port_padding;
    param_height>this->_node_height?
                param_height+=0:param_height=this->_node_height_min;
    if(this->_node_height < param_height)
        this->_node_height = param_height;

    int out_height = (this->_param_out.size())*(this->_param_out[0]->icoSize()+this->_port_padding)+this->_title_height+this->_node_height_min;
    is_pure?out_height+=0:out_height+=20+this->_port_padding;
    out_height>this->_node_height?
                out_height+=0:out_height=this->_node_height_min;
    if(this->_node_height < out_height)
        this->_node_height = out_height;

    this->_max_param_width = 0;
    for(auto i=0; i<this->_param_in.size(); ++i)
    {
        if(this->_max_param_width<this->_param_in[i]->width())
            this->_max_param_width = this->_param_in[i]->width();
    }

    this->_max_output_width = 0;
    for(auto i=0; i<this->_param_out.size(); ++i)
    {
        if(this->_max_output_width<this->_param_out[i]->width())
            this->_max_output_width = this->_param_out[i]->width();
    }

    if(this->_node_width<this->_max_param_width+this->_max_output_width+this->_port_space)
        this->_node_width = this->_max_param_width+this->_max_output_width+this->_port_space;
}

int Node::width()
{
    return this->_node_width;
}

int Node::height()
{
    return this->_node_height;
}

void Node::set_scene(QGraphicsScene *scene)
{
    this->_scene = scene;
}

void Node::init_title()
{
    this->_title_item = new QGraphicsTextItem(this);
    this->_title_item->setPlainText(this->_title);
    this->_title_item->setFont(this->_title_font);
    this->_title_item->setDefaultTextColor(this->_title_color);
    this->_title_item->setPos(this->_title_padding,this->_title_padding);

    auto title_width = this->_title_font_size*this->_title.size()+this->_node_width_min;
    if(this->_node_width<title_width)
        this->_node_width = title_width;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    painter->setBrush(this->_brush_title_back);
    painter->drawPath(title_outline.simplified());

    //outline
    this->isSelected()?painter->setPen(this->_pen_selected):painter->setPen(this->_pen_default);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(node_outline);
}

//QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
//{
//    if(change == QGraphicsItem::ItemPositionChange)
//    {

//    }
//}

void Node::add_port(Port *port,int index)
{
    switch(port->type())
    {
    case EXEC_IN:
        this->add_exec_in_port(port);
        break;
    case EXEC_OUT:
        this->add_exec_out_port(port);
        break;
    case PARAM_IN:
        this->add_param_in_port(port,index);
        break;
    case PARAM_OUT:
        this->add_param_out_port(port,index);
        break;
    default:
        break;
    }
}

void Node::add_exec_in_port(Port *port)
{
    port->add_to_parent_node(this,this->_scene);
    port->setPos(this->_port_padding,
                 this->_title_height);
}

void Node::add_exec_out_port(Port *port)
{
    port->add_to_parent_node(this,this->_scene);
    port->setPos(this->_node_width+this->_port_padding-port->width(),
                 this->_title_height);
}

void Node::add_param_in_port(Port *port, int index)
{
    port->add_to_parent_node(this,this->_scene);
    port->setPos(this->_port_padding,
                 this->_title_height+index*(this->_port_padding+port->icoSize()));
}

void Node::add_param_out_port(Port *port, int index)
{
    port->add_to_parent_node(this,this->_scene);
    port->setPos(this->_node_width-this->_port_padding-port->width(),
                 this->_title_height+index*(this->_port_padding+port->icoSize()));
}
