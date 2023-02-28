#ifndef NE_EDITOR_H
#define NE_EDITOR_H

#include <QWidget>
#include <QScreen>
#include <QGuiApplication>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QApplication>
#include <QDebug>

#include "ne_title.h"
#include "nodegraphicsscene.h"
#include "nodegraphicsview.h"
#include "port.h"

#define PADDING 10

QT_BEGIN_NAMESPACE
namespace Ui { class NE_Editor; }
QT_END_NAMESPACE

class NE_Editor : public QWidget
{
    Q_OBJECT

public:
    NE_Editor(QWidget *parent = nullptr);
    ~NE_Editor();

    void setup_editor();
    void set_eidtor_center(int width, int height);
    void create_actions();

    void debug_node();

private:
    Ui::NE_Editor *ui;
    NE_Title* _title;
    QBoxLayout* _layout;
    NodeGraphicsScene* _scene;
    NodeGraphicsView* _view;
    bool _is_fullscreen = false;

    QPoint _restore_pos;
    QSize _restore_size;

protected:
    void keyPressEvent(QKeyEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void onButtonMinClicked();
    void onButtonRestoreClicked();
    void onButtonMaxClicked();
    void onButtonCloseClicked();

};
#endif // NE_EDITOR_H
