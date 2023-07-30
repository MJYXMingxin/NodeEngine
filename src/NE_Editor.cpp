#include "NE_Editor.h"
//#include "./ui_ne_editor.h"

#include "NE_Node_Basic.h"
#include "nodes/LogicLibrary.h"
#include "nodes/BasicMathLibrary.h"
#include "nodes/interfaces/NodeLibraryPluginInterface.h"

NE_Editor::NE_Editor(QWidget *parent)
        : QMainWindow(parent),
        _centralWidget(Q_NULLPTR),
        _layout(Q_NULLPTR),
        _titlebar(new NE_Title(this)),
        _view(Q_NULLPTR),
        _scene(Q_NULLPTR)
//        , ui(new Ui::NE_Editor)
{
//    ui->setupUi(this);
    setup_editor();
//    LoadPlugins();


//    QDockWidget *dockWidget1 = new QDockWidget("DockWidget1",this);
//    NE_ModelWidget *widget = new NE_ModelWidget(this);
//    dockWidget1->setWidget(widget);
//    addDockWidget(Qt::LeftDockWidgetArea, dockWidget1);

}

void NE_Editor::setup_editor()
{
    //设置窗口大小，标题，位置
    setGeometry(0,0,1260,720);
    setWindowTitle("NodeEngine");
    set_eidtor_center(1260,720);
    setContentsMargins(0,0,0,0);

    _layout = new QBoxLayout(QBoxLayout::TopToBottom);
    _layout->setObjectName("QBoxLayout");
    _layout->setContentsMargins(0,0,0,0);
    _layout->setSpacing(0);

    //初始化scene,view
    _scene = new NE_Scene();
    _view = new NE_View(nullptr, _scene);
    _view->setContentsMargins(0,0,0,0);
    _layout->addWidget(_view);

    _centralWidget = new QWidget(this);
    _centralWidget->setLayout(_layout);
    setCentralWidget(_centralWidget);

    //初始化标题栏
    InitTitleBar();

    //全屏显示
//    QWindowsWindowFunctions::setHasBorderInFullScreen(p_wnd->windowHandle(), true);
    showFullScreen();

    //隐藏状态栏
    statusBar()->setVisible(false);
    setMouseTracking(true);
    setStyleSheetbyQss();

    setWindowOpacity(0);
}

void NE_Editor::InitTitleBar()
{
//    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    setAttribute(Qt::WA_TranslucentBackground);
    _titlebar->setObjectName("QMainWidget::titleBar");
    _titlebar->layout()->setContentsMargins(0,0,0,0);
    _titlebar->layout()->setSpacing(0);
    setMenuWidget(_titlebar);

    //绑定事件
    connect(_titlebar, &NE_Title::signalButtonCloseClicked, this, [this](){close();}, Qt::DirectConnection);
    connect(_titlebar, &NE_Title::signalButtonMaxClicked, this,
            [this]()
            {
                _restore_pos = pos();
                _restore_size = size();
                showMaximized();
            }, Qt::DirectConnection);
    connect(_titlebar, &NE_Title::signalButtonMinClicked, this, [this](){showMinimized();}, Qt::DirectConnection);
    connect(_titlebar, &NE_Title::signalButtonRestoreClicked, this,
            [this]()
            {
                showNormal();
                move(_restore_pos);
                setGeometry(QRect(_restore_pos.x(),
                                  _restore_pos.y(),
                                  _restore_size.width(),
                                  _restore_size.height()));
            }, Qt::DirectConnection);

    connect(_titlebar, &NE_Title::signalStoreScale, this, [this](){_titlebar->setStoredscale(_view->getScale());}, Qt::DirectConnection);
    connect(_titlebar, &NE_Title::signalResetScale, this, [this](){_view->setScale(_titlebar->getStoredscale());}, Qt::DirectConnection);

    connect(_titlebar, &NE_Title::signal25Scale,this, [this](){setScale(0.25);}, Qt::DirectConnection);
    connect(_titlebar, &NE_Title::signal50Scale,this, [this](){setScale(0.5);}, Qt::DirectConnection);
    connect(_titlebar, &NE_Title::signal75Scale,this, [this](){setScale(0.75);}, Qt::DirectConnection);
    connect(_titlebar, &NE_Title::signal100Scale,this, [this](){setScale(1);}, Qt::DirectConnection);
    connect(_titlebar, &NE_Title::signal300Scale,this, [this](){setScale(3);}, Qt::DirectConnection);
    connect(_titlebar, &NE_Title::signal500Scale,this, [this](){setScale(5);}, Qt::DirectConnection);
    connect(_titlebar, &NE_Title::signalSwichStyle,this, [this](){_view->SwitchStyle();update();}, Qt::DirectConnection);
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
    setStyleSheet(style);
}

void NE_Editor::set_eidtor_center(int width, int height)
{
    QRect screenRect = QGuiApplication::primaryScreen()->geometry();
    int screenW = screenRect.width();
    int screenH = screenRect.height();
    move((screenW - width) / 2, (screenH - height) / 2);
}


void NE_Editor::LoadPlugins()
{
    QDir dir("../lib");
    QStringList filters;
    filters << "*.dll";

    QStringList fileList = dir.entryList(filters, QDir::Files);
    qDebug()<<dir.path();
    foreach (QString file, fileList) {
        qDebug() << file;
    }
}

[[maybe_unused]] NE_View *NE_Editor::getView()
{
    return _view;
}

void NE_Editor::setScale(double scale)
{
    _view->setScale(scale);
}

QPointF NE_Editor::map_mouse_to_scene()
{
    return _view->mapToScene(_view->mapFromGlobal(QCursor::pos()));
}

void NE_Editor::right_click_event(QPointF pos)
{
//    debugNode(pos);
//    debugcustomNode(pos);
}

void NE_Editor::mousePressEvent(QMouseEvent *event)
{
    switch(event->button())
    {
        case Qt::MiddleButton:
            break;
        case Qt::RightButton:
            right_click_event(map_mouse_to_scene());
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
//    auto *in4 = new PARAM_IN_Port("浮点数",);
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
    auto *ein = new EXECInPort();
    auto *in1 = new PARAM_IN_Port("param1",Float);
    auto *in2 = new PARAM_IN_Port("param2",Float);
    auto *in3 = new PARAM_IN_Port("count",Int);

    auto *eout = new EXECOutPort();
    auto *out1 = new PARAM_OUT_Port("output",Float);
    auto *out2 = new PARAM_OUT_Port("num",Int);

    QVector<NE_Port_Basic*> in;
    QVector<NE_Port_Basic*> out;

    in.push_back(ein);
    in.push_back(in1);
    in.push_back(in2);
    in.push_back(in3);

    out.push_back(eout);
    out.push_back(out1);
    out.push_back(out2);

    auto *node = new NE_Node_Basic("TEST",in,out,
                                   Normal,
                                   QPointF(0,0));
//    node->set_scene(_view->Scene());
    _view->addNode(node,
                         static_cast<int>(pos.x()),
                         static_cast<int>(pos.y()));
}

void NE_Editor::debugcustomNode(QPointF pos)
{
    QDir dir(qApp->applicationDirPath());
    dir.cdUp();
    dir.cd("lib");
    loader.setFileName(dir.filePath("nativelib.dll"));
    if(!loader.load()){
        QMessageBox::critical(this,"",loader.errorString());
    }
    NodeLibraryPluginInterface *pi = qobject_cast<NodeLibraryPluginInterface*>(loader.instance());
    if(pi){
        auto *node = pi->CreateNodeByName("Add");
        _view->addNode(node,
                       static_cast<int>(pos.x()),
                       static_cast<int>(pos.y()));
    }

//    auto *node = new LogicLibrary();
//    auto *node = new AddNode();

//    _view->addNode(node,
//                   static_cast<int>(pos.x()),
//                   static_cast<int>(pos.y()));
}

void NE_Editor::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    auto *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000); // 动画持续时间为1秒
    animation->setStartValue(0.0); // 起始透明度为0
    animation->setEndValue(1.0); // 结束透明度为1
    animation->start(QAbstractAnimation::DeleteWhenStopped); // 开始动画并在结束后释放动画对象
}

void NE_Editor::closeEvent(QCloseEvent *event) {
    // 创建动画对象
    auto *animation = new QPropertyAnimation(this, "windowOpacity");
    // 设置动画的起始值和结束值
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    // 设置动画的持续时间
    animation->setDuration(1000); // 持续1秒
    // 启动动画
    animation->start();
    // 等待动画结束
    QEventLoop loop;
    // 连接动画的finished信号和QEventLoop的quit槽函数
    connect(animation, &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
    // 进入事件循环，等待动画完成
    loop.exec();
    QMainWindow::closeEvent(event);
}
