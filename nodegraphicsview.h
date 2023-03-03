#ifndef NODEGRAPHICSVIEW_H
#define NODEGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtGui>
#include <QtCore>
#include <QVector>
#include <QDebug>

#include "nodegraphicsitem.h"
#include "nodegraphicsscene.h"
#include "edge.h"
#include "port.h"
#include "config.h"

class NodeGraphicsView : public QGraphicsView
{
public:
    NodeGraphicsView(QWidget* parent = nullptr, NodeGraphicsScene* scene = nullptr);

    template <typename T>
    T clamp(T value,T min, T max);

    void RightButtonPressed(QMouseEvent *event);
    void RightButtonRelease(QMouseEvent *event);

    void LeftButtonPressed(QMouseEvent *event);
    void LeftButtonRelease(QMouseEvent *event);

    void reset_scale();
    void getconfig();

    void add_node(Node *node,int x=0, int y=0);
    void add_edge(Port *source=nullptr, Port *des=nullptr);
    void remove_edge(Edge* edge);
    void create_dragging_edge(Port *port);

private:
    NodeGraphicsScene* _scene;
    QJsonObject _obj;
    Config_View _config;
    double _zoom_clamp[2];
    double _zoom_factor;
    double _view_scale;
    bool _is_drag = false;

    QVector<Node*> _ports;
    QVector<Edge*> _edges;

    DragEdge* _drag_edge = nullptr;
    bool _drag_edge_mode = false;
protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // NODEGRAPHICSVIEW_H
