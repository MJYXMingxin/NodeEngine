#ifndef NODEGRAPHICSVIEW_H
#define NODEGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtGui>
#include <QtCore>
#include <QDebug>

#include "nodegraphicsitem.h"
#include "config.h"

class NodeGraphicsView : public QGraphicsView
{
public:
    NodeGraphicsView(QWidget* parent = nullptr, QGraphicsScene* scene = nullptr);

    template <typename T>
    T clamp(T value,T min, T max);

    void RightButtonPressed(QMouseEvent *event);
    void RightButtonRelease(QMouseEvent *event);

    void reset_scale();
    void getconfig();

    void add_node(Node *node,int x=0, int y=0);

private:
    QGraphicsScene* _scene;
    QJsonObject _obj;
    Config_View _config;
    double _zoom_clamp[2];
    double _zoom_factor;
    double _view_scale;
    bool _is_drag = false;
protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // NODEGRAPHICSVIEW_H
