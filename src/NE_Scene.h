#ifndef NE_SCENE_H
#define NE_SCENE_H

#include "pch.h"

class NE_View;

class NE_Scene : public QGraphicsScene
{
Q_OBJECT
public:
    explicit NE_Scene(QObject *parent = nullptr);
    void getConfig();
    void setView(NE_View* view);
    void drawDots(QPainter *painter, const QRectF &rect);
    void drawLines(QPainter *painter, const QRectF &rect);
    void switchStyle();
    double getScale();
    NE_View *View();
private:
    QJsonObject _obj;
    Config_Scene _config;
    Canvas_Style Style = Dots;
    NE_View* _view;

    QBrush _normal_dot_brush;
    QBrush _lighter_dot_brush;

    QPen _normal_line_pen;
    QPen _lighter_line_pen;

    QColor _scene_background_color;
    QColor _dot_normal_color;
    QColor _dot_lighter_color;
protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
};

#endif // NE_SCENE_H
