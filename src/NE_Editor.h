#ifndef NE_EDITOR_H
#define NE_EDITOR_H

#include "pch.h"

QT_BEGIN_NAMESPACE
namespace Ui { class NE_Editor; }
QT_END_NAMESPACE

class NE_Title;
class NE_View;
class NE_Scene;

class NE_Editor : public QMainWindow
{
Q_OBJECT

public:
    explicit NE_Editor(QWidget *parent = nullptr);
    ~NE_Editor() override = default;
    void InitTitleBar();
    void setup_editor();
    void setStyleSheetbyQss();
    void set_eidtor_center(int width, int height);
    void LoadPlugins();
//    void getConfig();
    QPointF map_mouse_to_scene();


    [[maybe_unused]] NE_View *getView();

    void debugcustomNode(QPointF pos);
    void debugNode(QPointF pos);
    void right_click_event(QPointF pos);
private:
//    Ui::NE_Editor *ui;
    QWidget *_centralWidget;
    QBoxLayout *_layout;

    NE_Title *_titlebar;
    NE_View *_view;
    NE_Scene *_scene;
    QPoint _restore_pos;
    QSize _restore_size;

    QMap<QString, QMap<QString, const QMetaObject*>> _node_libs;

    QPluginLoader loader;

private:
    void setScale(double scale);
private slots:

protected:
    bool event(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};
#endif // NE_EDITOR_H
