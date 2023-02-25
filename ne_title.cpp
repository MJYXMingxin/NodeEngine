#include "ne_title.h"

NE_Title::NE_Title(QWidget *parent)
    : QWidget{parent}
{
    this->init_title();
    this->init_control();
    this->init_title_bar();
    this->init_menubar();
    this->loadStyleSheet("TitleBar");
}

void NE_Title::init_title()
{
    this->_ico = new QLabel;
    this->_title = new QLabel;

    this->_menu = new QMenuBar;

    this->_min = new QPushButton;
    this->_max = new QPushButton;
    this->_restore = new QPushButton;
    this->_close = new QPushButton;

    this->_min->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    this->_max->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    this->_restore->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    this->_close->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));

    this->_title->setObjectName("Title");
    this->_min->setObjectName("ButtonMin");
    this->_max->setObjectName("ButtonMax");
    this->_restore->setObjectName("ButtonRestore");
    this->_close->setObjectName("ButtonClose");

    this->_min->setToolTip(QStringLiteral("最小化"));
    this->_max->setToolTip(QStringLiteral("最大化"));
    this->_restore->setToolTip(QStringLiteral("还原"));
    this->_close->setToolTip(QStringLiteral("关闭"));

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);
    this->_title->setPalette(pe);

    this->_restore->setVisible(false);

    this->_min->setIcon(this->style()->standardIcon(QStyle::SP_TitleBarMinButton));
    this->_max->setIcon(this->style()->standardIcon(QStyle::SP_TitleBarMaxButton));
    this->_restore->setIcon(this->style()->standardIcon(QStyle::SP_TitleBarNormalButton));
    this->_close->setIcon(this->style()->standardIcon(QStyle::SP_TitleBarCloseButton));

    QHBoxLayout* title_layout = new QHBoxLayout(this);
    title_layout->addWidget(this->_ico);
    title_layout->addWidget(this->_menu);
    title_layout->addWidget(this->_title);

    title_layout->addSpacing(180);

    title_layout->addWidget(this->_min);
    title_layout->addWidget(this->_max);
    title_layout->addWidget(this->_restore);
    title_layout->addWidget(this->_close);

    title_layout->setContentsMargins(5, 0, 0, 0);
    title_layout->setSpacing(0);

    this->_title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(TITLE_HEIGHT);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

void NE_Title::init_menubar()
{
    this->_newAction = new QAction("&New Graph(N)");
    this->_openAction = new QAction("&Open Graph(O)");
    this->_saveAction = new QAction("&Save Graph(S)");

    auto filemenu = this->_menu->addMenu("&File(F)");
    filemenu->addAction(this->_newAction);
    filemenu->addAction(this->_openAction);
    filemenu->addAction(this->_saveAction);

    this->_menu->addSeparator();

    this->_copyAction = new QAction("Copy");
    this->_cutAction = new QAction("Cut");
    this->_pasteAction = new QAction("Paste");
    this->_undoAction = new QAction("Undo");
    this->_redoAction = new QAction("Redo");

    auto editmenu = this->_menu->addMenu("&Edit(E)");
    editmenu->addAction(this->_copyAction);
    editmenu->addAction(this->_cutAction);
    editmenu->addAction(this->_pasteAction);
    editmenu->addAction(this->_undoAction);
    editmenu->addAction(this->_redoAction);

    this->_menu->addSeparator();

    auto selectionmenu = this->_menu->addAction("&Selection(S)");
    auto runmenu = this->_menu->addAction("&Run(R)");
    auto helpmenu = this->_menu->addAction("&Help(H)");

}

void NE_Title::init_control()
{
    connect(this->_min, SIGNAL(clicked(bool)), this, SLOT(onButtonMinClicked()));
    connect(this->_max, SIGNAL(clicked(bool)), this, SLOT(onButtonMaxClicked()));
    connect(this->_restore, SIGNAL(clicked(bool)), this, SLOT(onButtonRestoreClicked()));
    connect(this->_close, SIGNAL(clicked(bool)), this, SLOT(onButtonCloseClicked()));
}

void NE_Title::init_title_bar()
{
    this->set_icon("./resource/NE.png");
    this->set_titleContent(QString("Node Engine"));
    this->set_buttonType(MIN_MAX_BUTTON);
    this->set_titleWidth(this->width());
}

void NE_Title::set_background_color(int R, int G, int B)
{
    this->_bcolor_R = R;
    this->_bcolor_G = G;
    this->_bcolor_B = B;
    update();
}

void NE_Title::set_icon(QString path, QSize Iconsize)
{
    QPixmap titleicon(path);
    this->_ico->setPixmap(titleicon.scaled(Iconsize));
}

void NE_Title::set_titleContent(QString text, int titlesize)
{
    QFont font = this->_title->font();
    font.setPointSize(titlesize);
    this->_title->setFont(font);
    this->_title->setText(text);
    this->_title_content = text;
    this->_title->setAlignment(Qt::AlignCenter);
//    this->_title->setStyleSheet("QLabel{padding-left:220px;}");
}

void NE_Title::set_titleWidth(int width)
{
    this->setFixedWidth(width);
}

void NE_Title::set_buttonType(ButtonType type)
{
    this->_button_Type = type;

    switch(type)
    {
    case MIN_BUTTON:
    {
        this->_restore->setVisible(false);
        this->_max->setVisible(false);
    }
        break;
    case MIN_MAX_BUTTON:
    {
        this->_restore->setVisible(false);
    }
        break;
    case ONLY_CLOSE_BUTTON:
    {
        this->_min->setVisible(false);
        this->_max->setVisible(false);
        this->_restore->setVisible(false);
    }
        break;
    default:
        break;
    }
}

void NE_Title::set_windowBorderWidth(int width)
{
    this->_window_border_width = width;
}

void NE_Title::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPainterPath pathback;
    pathback.setFillRule(Qt::WindingFill);
    pathback.addRoundedRect(QRect(0,0,this->width(),this->height()),0,0);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(pathback,QBrush(QColor(this->_bcolor_R,
                                            this->_bcolor_G,
                                            this->_bcolor_B)));
    if (this->width() != (this->parentWidget()->width() - this->_borderwidth))
    {
        this->setFixedWidth(this->parentWidget()->width() - this->_borderwidth);
    }
    QWidget::paintEvent(event);
}

void NE_Title::loadStyleSheet(const QString &sheetName)
{
    QFile file("./Styles/" + sheetName + ".qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }
}

void NE_Title::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(this->_button_Type == MIN_MAX_BUTTON)
    {
        if(this->_max->isVisible())
            onButtonMaxClicked();
        else
            onButtonRestoreClicked();
    }
    return QWidget::mouseDoubleClickEvent(event);
}

void NE_Title::mousePressEvent(QMouseEvent *event)
{
    if(this->_button_Type == MIN_MAX_BUTTON &&
            this->_max->isVisible())
    {
        this->_isPressed = true;
        this->_mouseStartPos = event->globalPosition();
    }
    else
    {
        this->_isPressed = true;
        this->_mouseStartPos = event->globalPosition();
    }
    return QWidget::mousePressEvent(event);
}

void NE_Title::mouseMoveEvent(QMouseEvent *event)
{
    if(this->_isPressed)
    {
        QPointF movepoint = event->globalPosition() - this->_mouseStartPos;
        QPointF widgetPos = this->parentWidget()->pos();
        this->_mouseStartPos = event->globalPosition();
        this->parentWidget()->move(widgetPos.x()+movepoint.x(),
                                   widgetPos.y()+movepoint.y());
    }
    return QWidget::mouseMoveEvent(event);
}

void NE_Title::mouseReleaseEvent(QMouseEvent *event)
{
    this->_isPressed = false;
    return QWidget::mouseReleaseEvent(event);
}


void NE_Title::onButtonMaxClicked()
{
    this->_max->setVisible(false);
    this->_restore->setVisible(true);
    emit signalButtonMaxClicked();
}

void NE_Title::onButtonRestoreClicked()
{
    this->_restore->setVisible(false);
    this->_max->setVisible(true);
    emit signalButtonRestoreClicked();
}

void NE_Title::onButtonMinClicked()
{
    emit signalButtonMinClicked();
}

void NE_Title::onButtonCloseClicked()
{
    emit signalButtonCloseClicked();
}
