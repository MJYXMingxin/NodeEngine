#ifndef NE_TITLE_H
#define NE_TITLE_H

#include <QWidget>
#include <QLabel>
#include <QSize>
#include <QSizePolicy>
#include <QPushButton>
#include <QBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QRect>
#include <QBrush>
#include <QColor>
#include <QPixmap>
#include <QMouseEvent>
#include <QPointF>
#include <QHBoxLayout>
#include <QFile>
#include <QStyle>
#include <QPalette>
#include <QMenuBar>
#include <QAction>
#include <QDebug>

#define BUTTON_WIDTH 30
#define BUTTON_HEIGHT 30
#define TITLE_HEIGHT 30

enum ButtonType
{
    MIN_BUTTON = 0,         // 最小化和关闭按钮;
    MIN_MAX_BUTTON ,        // 最小化、最大化和关闭按钮;
    ONLY_CLOSE_BUTTON       // 只有关闭按钮;
};

class NE_Title : public QWidget
{
    Q_OBJECT
public:
    explicit NE_Title(QWidget *parent = nullptr);
    void init_title();
    void init_control();
    void init_title_bar();
    void set_background_color(int R, int G, int B);
    void set_icon(QString path, QSize Iconsize = QSize(25,25));
    void set_titleContent(QString text, int titlesize = 12);
    void set_titleWidth(int width);
    void set_buttonType(ButtonType type);
    void set_windowBorderWidth(int width);
    void loadStyleSheet(const QString &sheetName);
    void init_menubar();
private:
    QLabel *_ico;
    QLabel *_title;
    QPushButton *_min;
    QPushButton *_max;
    QPushButton *_restore;
    QPushButton *_close;
    QMenuBar *_menu;

    int _bcolor_R = 21;
    int _bcolor_G = 21;
    int _bcolor_B = 21;
    int _borderwidth = 0;

    QString _title_content;
    ButtonType _button_Type = MIN_MAX_BUTTON;
    int _window_border_width = 0;

    QPointF _mouseStartPos;
    bool _isPressed = false;

    QAction *_newAction;
    QAction *_openAction;
    QAction *_saveAction;

    QAction *_copyAction;
    QAction *_cutAction;
    QAction *_pasteAction;
    QAction *_undoAction;
    QAction *_redoAction;


protected:
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void signalButtonMinClicked();
    void signalButtonRestoreClicked();
    void signalButtonMaxClicked();
    void signalButtonCloseClicked();

private slots:
    // 按钮触发的槽;
    void onButtonMinClicked();
    void onButtonRestoreClicked();
    void onButtonMaxClicked();
    void onButtonCloseClicked();
//    void onRollTitle();
};

#endif // NE_TITLE_H
