#ifndef NE_VIEW_H
#define NE_VIEW_H

#include "pch.h"

class NE_Scene;
class NE_Node_Basic;
class NE_Port_Basic;
class NE_Line_Basic;
class NE_Drag_Line;
class NE_Cutting_Line;

class NE_View : public QGraphicsView
{
Q_OBJECT
public:
    NE_View(QWidget *parent = nullptr, NE_Scene *scene = nullptr);
    void getConfig();
    void setScale(double scale);
    double getScale();
    void LeftButtonPressed(QMouseEvent *event);
    void LeftButtonReleased(QMouseEvent *event);
    void RightButtonPressed(QMouseEvent *event);
    void RightButtonReleased(QMouseEvent *event);
    void SwitchStyle();
    void setStyleSheetbyQss();
    void addNode(NE_Node_Basic *node, int x=0, int y=0);

    void add_edge(NE_Port_Basic *source=nullptr, NE_Port_Basic *des=nullptr);
    void remove_edge(NE_Line_Basic* edge);
    void create_dragging_edge(NE_Port_Basic *port);

    void delete_selected_items();
    void remove_node(NE_Node_Basic *node);

    void reset_scale();

    NE_Scene *Scene();
    template <typename T>
    T clamp(T value,T min, T max);
protected:
    NE_Scene *_scene;
    QJsonObject _obj;
    Config_View _config;

    Clamp _zoom_clamp;
    double _zoom_factor;
    double _view_scale;

    bool _is_drag = false;
    QTime _presstime_r;

    QVector<NE_Node_Basic*> _nodes;
    QVector<NE_Line_Basic*> _edges;

    NE_Drag_Line* _drag_edge = nullptr;
    bool _drag_edge_mode = false;
    NE_Cutting_Line *_cutting_line;
    bool _cutting_line_mode = false;
protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif // NE_VIEW_H
