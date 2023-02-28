#include "ne_editor.h"
#include "./ui_ne_editor.h"


NE_Editor::NE_Editor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NE_Editor)
{
    ui->setupUi(this);
    this->setup_editor();

    this->debug_node();
}

NE_Editor::~NE_Editor()
{
    delete ui;
}

void NE_Editor::set_eidtor_center(int width, int height)
{
    QRect screenRect = QGuiApplication::primaryScreen()->geometry();
    int screenW = screenRect.width();
    int screenH = screenRect.height();
    this->move((screenW - width) / 2, (screenH - height) / 2);
}

void NE_Editor::setup_editor()
{
    //设置窗口大小，标题，位置
    this->setGeometry(0,0,1260,720);
    this->setWindowTitle("NodeEngine");
    this->set_eidtor_center(1260,720);

    //隐藏窗口边框
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    this->_layout = new QBoxLayout(QBoxLayout::TopToBottom);
    this->_layout->setContentsMargins(0,0,0,0);

    this->_title = new NE_Title(this);
    this->_title->move(0,0);
    //绑定标题栏按键
    connect(this->_title,SIGNAL(signalButtonCloseClicked()),this,SLOT(onButtonCloseClicked()));
    connect(this->_title,SIGNAL(signalButtonMaxClicked()),this,SLOT(onButtonMaxClicked()));
    connect(this->_title,SIGNAL(signalButtonMinClicked()),this,SLOT(onButtonMinClicked()));
    connect(this->_title,SIGNAL(signalButtonRestoreClicked()),this,SLOT(onButtonRestoreClicked()));

    this->_layout->addWidget(this->_title);
    //初始化scene
    this->_scene = new NodeGraphicsScene();
    this->_view = new NodeGraphicsView(nullptr,this->_scene);
    this->_view->setContentsMargins(0,0,0,0);
    this->_layout->addWidget(this->_view);

    this->_layout->setSpacing(0);
    this->setLayout(this->_layout);

    this->setMouseTracking(true);

}

void NE_Editor::debug_node()
{
    auto *param1 = new ParamInPort("Param1","float",QColor(153,255,34),PARAM_IN);
    auto *param2 = new ParamInPort("Param2","float",QColor(153,255,34),PARAM_IN);
    auto *param3 = new ParamInPort("Param3","float",QColor(153,255,34),PARAM_IN);
    auto *param4 = new ParamInPort("Param4","float",QColor(153,255,34),PARAM_IN);
    auto *output = new ParamOutPort("Output","float",QColor(153,255,34),PARAM_OUT);

    QVector<Port*> in;
    QVector<Port*> out;
    in.push_back(param1);
    in.push_back(param2);
    in.push_back(param3);
    in.push_back(param4);
    out.push_back(output);

    Node *node = new Node(nullptr,nullptr,"Test",in,out);
    node->set_scene(this->_scene);
    this->_view->add_node(node,0,0);
}

void NE_Editor::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_F12:
        if(!this->_is_fullscreen)
        {
            this->_is_fullscreen = true;
            showFullScreen();
        }
        else
        {
            this->_is_fullscreen = false;
            showNormal();
        }
        break;
    case Qt::Key_Escape:
        if(this->_is_fullscreen)
        {
            this->_is_fullscreen = false;
            showNormal();
        }

    default:
        break;
    }
}

void NE_Editor::onButtonMinClicked()
{
    showMinimized();
}

void NE_Editor::onButtonRestoreClicked()
{
    showNormal();
    this->move(this->_restore_pos);
    this->setGeometry(QRect(this->_restore_pos.x(),
                            this->_restore_pos.y(),
                            this->_restore_size.width(),
                            this->_restore_size.height()));
}

void NE_Editor::onButtonMaxClicked()
{
    this->_restore_pos = this->pos();
    this->_restore_size = this->size();
    showMaximized();
}

void NE_Editor::onButtonCloseClicked()
{
    close();
}

