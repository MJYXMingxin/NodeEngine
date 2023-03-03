#ifndef NODEGRAPHICSSCENE_H
#define NODEGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QWidget>
#include <QColor>
#include <QPen>
#include <QDebug>
#include <QPainter>
#include <QRectF>
#include <QtMath>
#include <QBrush>
#include <QLine>

#include "config.h"

class NodeGraphicsView;
class Edge;

class NodeGraphicsScene : public QGraphicsScene
{
public:
    NodeGraphicsScene(QObject *parent = nullptr);
    void getconfig();
    void set_view(NodeGraphicsView *view);
public:
    NodeGraphicsView *_view;
private:
    QJsonObject _obj;
    Config_Scene _config;
    QPen _normal_line_pen;
    QPen _dark_line_pen;
    QVector<QLine> Lines,Dark_Lines;

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
};

#endif // NODEGRAPHICSSCENE_H
