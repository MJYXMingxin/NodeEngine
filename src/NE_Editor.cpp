#include "NE_Editor.h"
//#include "./ui_ne_editor.h"

#include "NE_Node_Basic.h"
#include "./nodes/BranchNode.h"

NE_Editor::NE_Editor(QWidget *parent)
        : QMainWindow(parent)
//        , ui(new Ui::NE_Editor)
{
//    ui->setupUi(this);
    this->setup_editor();

//    QDockWidget *dockWidget1 = new QDockWidget("DockWidget1",this);
//    NE_ModelWidget *widget = new NE_ModelWidget(this);
//    dockWidget1->setWidget(widget);
//    this->addDockWidget(Qt::LeftDockWidgetArea, dockWidget1);

}

void NE_Editor::setup_editor()
{
    //设置窗口大小，标题，位置
    this->setGeometry(0,0,1260,720);
    this->setWindowTitle("NodeEngine");
    this->set_eidtor_center(1260,720);
    this->setContentsMargins(0,0,0,0);

    this->_layout = new QBoxLayout(QBoxLayout::TopToBottom);
    this->_layout->setObjectName("QBoxLayout");
    this->_layout->setContentsMargins(0,0,0,0);
    this->_layout->setSpacing(0);

    //初始化scene,view
    this->_scene = new NE_Scene();
    this->_view = new NE_View(nullptr, this->_scene);
    this->_view->setContentsMargins(0,0,0,0);
    this->_layout->addWidget(this->_view);

    this->_centralWidget = new QWidget(this);
    this->_centralWidget->setLayout(this->_layout);
    this->setCentralWidget(this->_centralWidget);

    //初始化标题栏
    this->InitTitleBar();

    //全屏显示
//    QWindowsWindowFunctions::setHasBorderInFullScreen(p_wnd->windowHandle(), true);
    this->showFullScreen();

    //隐藏状态栏
    this->statusBar()->setVisible(false);
    this->setMouseTracking(true);
    this->setStyleSheetbyQss();
}

void NE_Editor::InitTitleBar()
{
//    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->_titlebar = new NE_Title(this);
    this->_titlebar->setObjectName("QMainWidget::titleBar");
    this->_titlebar->layout()->setContentsMargins(0,0,0,0);
    this->_titlebar->layout()->setSpacing(0);
    setMenuWidget(this->_titlebar);

    //绑定事件
    connect(this->_titlebar, &NE_Title::signalButtonCloseClicked, this, [this](){close();}, Qt::DirectConnection);
    connect(this->_titlebar, &NE_Title::signalButtonMaxClicked, this,
            [this]()
            {
                this->_restore_pos = this->pos();
                this->_restore_size = this->size();
                showMaximized();
            }, Qt::DirectConnection);
    connect(this->_titlebar, &NE_Title::signalButtonMinClicked, this, [this](){showMinimized();}, Qt::DirectConnection);
    connect(this->_titlebar, &NE_Title::signalButtonRestoreClicked, this,
            [this]()
            {
                showNormal();
                this->move(this->_restore_pos);
                this->setGeometry(QRect(this->_restore_pos.x(),
                                        this->_restore_pos.y(),
                                        this->_restore_size.width(),
                                        this->_restore_size.height()));
            }, Qt::DirectConnection);

    connect(this->_titlebar, &NE_Title::signalStoreScale, this, [this](){this->_titlebar->setStoredscale(this->_view->getScale());}, Qt::DirectConnection);
    connect(this->_titlebar, &NE_Title::signalResetScale, this, [this](){this->_view->setScale(this->_titlebar->getStoredscale());}, Qt::DirectConnection);

    connect(this->_titlebar, &NE_Title::signal25Scale,this, [this](){this->setScale(0.25);}, Qt::DirectConnection);
    connect(this->_titlebar, &NE_Title::signal50Scale,this, [this](){this->setScale(0.5);}, Qt::DirectConnection);
    connect(this->_titlebar, &NE_Title::signal75Scale,this, [this](){this->setScale(0.75);}, Qt::DirectConnection);
    connect(this->_titlebar, &NE_Title::signal100Scale,this, [this](){this->setScale(1);}, Qt::DirectConnection);
    connect(this->_titlebar, &NE_Title::signal300Scale,this, [this](){this->setScale(3);}, Qt::DirectConnection);
    connect(this->_titlebar, &NE_Title::signal500Scale,this, [this](){this->setScale(5);}, Qt::DirectConnection);
    connect(this->_titlebar, &NE_Title::signalSwichStyle,this, [this](){this->_view->SwitchStyle();this->update();}, Qt::DirectConnection);
}

bool NE_Editor::event(QEvent *event)
{
#if defined(Q_OS_WIN)
    if (event->type() == QEvent::WinIdChange) {
        if (windowHandle()) {
            HWND handle = reinterpret_cast<HWND>(windowHandle()->winId());
            SetWindowLongPtr(handle, GWL_STYLE, GetWindowLongPtr(handle, GWL_STYLE) | WS_BORDER);
        }
    }
#endif
    return QMainWindow::event(event);
}

void NE_Editor::setStyleSheetbyQss()
{
    QString style = loadStyleSheet("MainWindow");
    this->setStyleSheet(style);
}

void NE_Editor::set_eidtor_center(int width, int height)
{
    QRect screenRect = QGuiApplication::primaryScreen()->geometry();
    int screenW = screenRect.width();
    int screenH = screenRect.height();
    this->move((screenW - width) / 2, (screenH - height) / 2);
}

NE_View *NE_Editor::getView()
{
    return this->_view;
}

void NE_Editor::setScale(double scale)
{
    this->_view->setScale(scale);
}

QPointF NE_Editor::map_mouse_to_scene()
{
    return this->_view->mapToScene(this->_view->mapFromGlobal(QCursor::pos()));
}

void NE_Editor::right_click_event(QPointF pos)
{
//    this->debugNode(pos);
    this->debugcustomNode(pos);
}

void NE_Editor::mousePressEvent(QMouseEvent *event)
{
    switch(event->button())
    {
        case Qt::MiddleButton:
            break;
        case Qt::RightButton:
            this->right_click_event(this->map_mouse_to_scene());
            break;
        default:
            break;
    }
    QMainWindow::mousePressEvent(event);
}

void NE_Editor::debugNode(QPointF pos)
{
    checkConfig();
//    auto *in1 = new PARAM_IN_Port("布尔",Bool);
//    auto *in2 = new PARAM_IN_Port("比特",Byte);
//    auto *in3 = new PARAM_IN_Port("整数",Int);
//    auto *in4 = new PARAM_IN_Port("浮点数",Float);
//    auto *in5 = new PARAM_IN_Port("字符串",String);
//
//    auto *out1 = new PARAM_OUT_Port("二维向量",Vec2);
//    auto *out2 = new PARAM_OUT_Port("三维向量",Vec3);
//    auto *out3 = new PARAM_OUT_Port("枚举",Enum);
//    auto *out4 = new PARAM_OUT_Port("结构体",Struct);
//    auto *out5 = new PARAM_OUT_Port("其他",Else);
//    auto *out6 = new PARAM_OUT_Port("未知",UNknown);
//
//    QVector<NE_Port_Basic*> in;
//    QVector<NE_Port_Basic*> out;
//
//    in.push_back(in1);
//    in.push_back(in2);
//    in.push_back(in3);
//    in.push_back(in4);
//    in.push_back(in5);
//
//    out.push_back(out1);
//    out.push_back(out2);
//    out.push_back(out3);
//    out.push_back(out4);
//    out.push_back(out5);
//    out.push_back(out6);

    auto *in1 = new PARAM_IN_Port("param1",Float);
    auto *in2 = new PARAM_IN_Port("param2",Float);
    auto *in3 = new PARAM_IN_Port("count",Int);

    auto *out1 = new PARAM_OUT_Port("output",Float);
    auto *out2 = new PARAM_OUT_Port("num",Int);

    QVector<NE_Port_Basic*> in;
    QVector<NE_Port_Basic*> out;

    in.push_back(in1);
    in.push_back(in2);
    in.push_back(in3);

    out.push_back(out1);
    out.push_back(out2);

    auto *node = new NE_Node_Basic("TEST",in,out,
                                   false,
                                   QPointF(0,0));
//    node->set_scene(this->_view->Scene());
    this->_view->addNode(node,
                         static_cast<int>(pos.x()),
                         static_cast<int>(pos.y()));
}

void NE_Editor::debugcustomNode(QPointF pos)
{
    auto *node = new BranchNode();
    this->_view->addNode(node,
                         static_cast<int>(pos.x()),
                         static_cast<int>(pos.y()));
}

