#ifndef NE_TITLE_H
#define NE_TITLE_H

#include "pch.h"

#define BUTTON_WIDTH 30
#define BUTTON_HEIGHT 30
#define TITLE_HEIGHT 30

enum ButtonType
{
    MIN_BUTTON = 0,         // 最小化和关闭按钮;
    MIN_MAX_BUTTON ,        // 最小化、最大化和关闭按钮;
    ONLY_CLOSE_BUTTON       // 只有关闭按钮;
};

class NE_Editor;

class NE_Title : public QWidget
{
Q_OBJECT
public:
    explicit NE_Title(QWidget *parent = nullptr);
    void init_title();
    void init_control();
    void init_title_bar();
    void set_background_color(int R, int G, int B);
    void set_icon(const QString& path, QSize Iconsize = QSize(25,25));
    void set_titleContent(const QString& text, int titlesize = 12);
    void set_titleWidth(int width);
    void set_buttonType(ButtonType type);
    void set_windowBorderWidth(int width);
    void loadStyleSheet(const QString &sheetName);
    void init_menubar();

    double getStoredscale() const;
    void setStoredscale(double scale);
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

    double _store_scale = 1.0;

    QAction *_newAction;
    QAction *_newWindow;
    QAction *_openAction;
    QAction *_saveAction;
    QAction *_exitAction;

    QAction *_copyAction;
    QAction *_cutAction;
    QAction *_pasteAction;
    QAction *_undoAction;
    QAction *_redoAction;
    QAction *_findAction;
    QAction *_replaceAction;
    QAction *_retract;
    QAction *_expand;

    QAction *_selectAll;
    QAction *_duplicate;

    QAction *_storescale;
    QAction *_resetscale;
    QAction *_view_25;
    QAction *_view_50;
    QAction *_view_75;
    QAction *_view_100;
    QAction *_view_300;
    QAction *_view_500;
    QAction *_style_switch;

    QAction *_run;

    QAction *_newterminal;

    QAction *_document;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void signalButtonMinClicked();
    void signalButtonMaxClicked();
    void signalButtonRestoreClicked();
    void signalButtonCloseClicked();

    void signalStoreScale();
    void signalResetScale();
    void signal25Scale();
    void signal50Scale();
    void signal75Scale();
    void signal100Scale();
    void signal300Scale();
    void signal500Scale();
    void signalSwichStyle();

private slots:
    // 按钮触发的槽;
    void onButtonMaxClicked();
    void onButtonRestoreClicked();
//    void onRollTitle();
};

#endif // NE_TITLE_H
