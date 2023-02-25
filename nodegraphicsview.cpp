#include "nodegraphicsview.h"

NodeGraphicsView::NodeGraphicsView(QWidget* parent, QGraphicsScene* scene)
    :QGraphicsView{parent}
{
    this->getconfig();

    this->_scene = scene;
    this->setScene(this->_scene);

    this->setRenderHints(QPainter::Antialiasing|
                         QPainter::TextAntialiasing|
                         QPainter::SmoothPixmapTransform);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    //隐藏滚动条
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->_zoom_clamp[0] = this->_config.clamp.min;
    this->_zoom_clamp[1] = this->_config.clamp.max;
    this->_zoom_factor = this->_config.zoom_factor;
    this->_view_scale = 1.0;

    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

void NodeGraphicsView::add_node(Node *node, int x, int y)
{
    this->_scene->addItem(node);
    node->setPos(x-node->width()/2,y-node->height()/2);
}

void NodeGraphicsView::wheelEvent(QWheelEvent *event)
{
    if(!this->_is_drag)
    {
        double zoom_factor;
        event->angleDelta().y() > 0?
                    zoom_factor = this->_zoom_factor:
                zoom_factor = 1 / this->_zoom_factor;

        this->_view_scale *= zoom_factor;

        this->_view_scale = this->clamp(this->_view_scale,
                                        this->_zoom_clamp[0],this->_zoom_clamp[1]);
        if(this->_view_scale == this->_zoom_clamp[0]||
                this->_view_scale == this->_zoom_clamp[1])
            zoom_factor = 1.0;
        this->scale(zoom_factor, zoom_factor);
        this->update();
    }
}

void NodeGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    switch(event->button())
    {
    case Qt::RightButton:
        this->RightButtonPressed(event);
        break;
    default:
        break;
    }
}

void NodeGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    switch(event->button())
    {
    case Qt::RightButton:
        this->RightButtonRelease(event);
        break;
    default:
        break;
    }
}

void NodeGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    switch(event->button())
    {
    case Qt::MiddleButton:
        this->reset_scale();
        break;
    default:
        QGraphicsView::mouseDoubleClickEvent(event);
        break;
    }
}

void NodeGraphicsView::RightButtonPressed(QMouseEvent *event)
{
    if(this->itemAt(event->pos()) != NULL)
        return;
    else
    {
        auto release_event = new QMouseEvent(QEvent::MouseButtonRelease,
                                         event->position(),
                                         event->globalPosition(),
                                         Qt::LeftButton,
                                         Qt::NoButton,
                                         event->modifiers());
        QGraphicsView::mouseReleaseEvent(release_event);

        this->setDragMode(QGraphicsView::ScrollHandDrag);
        this->_is_drag = true;

        auto click_event = new QMouseEvent(QEvent::MouseButtonPress,
                                       event->position(),
                                       event->globalPosition(),
                                       Qt::LeftButton,
                                       Qt::NoButton,
                                       event->modifiers());
        QGraphicsView::mousePressEvent(click_event);


    }
}

void NodeGraphicsView::RightButtonRelease(QMouseEvent *event)
{
    this->setDragMode(QGraphicsView::NoDrag);
    this->_is_drag = false;
}

void NodeGraphicsView::reset_scale()
{
    this->resetTransform();
    this->_view_scale = 1.0;
}


template <typename T>
T NodeGraphicsView::clamp(T value, T min, T max)
{
    if(value < min)
        return min;
    else if(value > max)
        return max;
    else
        return value;
}

void NodeGraphicsView::getconfig()
{
    this->_obj = SearchObj(View);
    this->_config.clamp.min = this->_obj["zoom_clamp"].toObject()["min"].toDouble();
    this->_config.clamp.max = this->_obj["zoom_clamp"].toObject()["max"].toDouble();

    this->_config.zoom_factor = this->_obj["zoom_factor"].toDouble();
}

