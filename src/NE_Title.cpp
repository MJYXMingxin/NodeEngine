#include "NE_Title.h"

NE_Title::NE_Title(QWidget *parent)
        : QWidget{parent}
{
    this->init_title();
    this->init_menubar();
    this->init_title_bar();
    this->init_control();
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

    this->_menu->setFixedWidth(700);

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

    auto* title_layout = new QHBoxLayout(this);
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
    auto filemenu = this->_menu->addMenu("&File(F)");
    this->_newAction = new QAction("New File");
    this->_newAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    this->_newWindow = new QAction("New Window");
    this->_newWindow->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_N));
    this->_openAction = new QAction("Open File");
    this->_openAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    this->_saveAction = new QAction("Save File");
    this->_saveAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    this->_exitAction = new QAction("Exit");

    filemenu->addAction(this->_newAction);
    filemenu->addAction(this->_newWindow);
    filemenu->addSeparator();
    filemenu->addAction(this->_openAction);
    filemenu->addSeparator();
    filemenu->addAction(this->_saveAction);
    filemenu->addSeparator();
    filemenu->addAction(this->_exitAction);

    this->_copyAction = new QAction("Copy");
    this->_copyAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_C));
    this->_cutAction = new QAction("Cut");
    this->_cutAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_X));
    this->_pasteAction = new QAction("Paste");
    this->_pasteAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_V));
    this->_undoAction = new QAction("Undo");
    this->_undoAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z));
    this->_redoAction = new QAction("Redo");
    this->_redoAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y));
    this->_findAction = new QAction("Find");
    this->_findAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_F));
    this->_replaceAction = new QAction("Replace");
    this->_replaceAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_H));
    this->_retract = new QAction("Retract All");
    this->_retract->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Tab));
    this->_expand = new QAction("Expand All");
    this->_expand->setShortcut(QKeySequence(Qt::SHIFT | Qt::Key_Tab));

    auto editmenu = this->_menu->addMenu("&Edit(E)");
    editmenu->addAction(this->_undoAction);
    editmenu->addAction(this->_redoAction);
    editmenu->addSeparator();
    editmenu->addAction(this->_copyAction);
    editmenu->addAction(this->_cutAction);
    editmenu->addAction(this->_pasteAction);
    editmenu->addSeparator();
    editmenu->addAction(this->_findAction);
    editmenu->addAction(this->_replaceAction);
    editmenu->addSeparator();
    editmenu->addAction(this->_retract);
    editmenu->addAction(this->_expand);

    this->_selectAll = new QAction("Select All");
    this->_selectAll->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_A));
    this->_duplicate = new QAction("Duplicate");
    this->_duplicate->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_D));

    auto selectionmenu = this->_menu->addMenu("&Selection(S)");
    selectionmenu->addAction(this->_selectAll);
    selectionmenu->addSeparator();
    selectionmenu->addAction(this->_duplicate);

    this->_storescale = new QAction("Store Current Scale");
    this->_storescale->setShortcut(QKeySequence(Qt::SHIFT | Qt::Key_S));
    this->_resetscale = new QAction("Reset Scale by Stored Value");
    this->_resetscale->setShortcut(QKeySequence(Qt::SHIFT | Qt::Key_R));
    this->_view_25 = new QAction("25%");
    this->_view_50 = new QAction("50%");
    this->_view_75 = new QAction("75%");
    this->_view_100 = new QAction("100%");
    this->_view_300 = new QAction("300%");
    this->_view_500 = new QAction("500%");
    this->_style_switch = new QAction("Switch Canvas Style");
    this->_style_switch->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_QuoteLeft));

    auto viewmenu = this->_menu->addMenu("&View(V)");
    viewmenu->addAction(this->_storescale);
    viewmenu->addAction(this->_resetscale);
    viewmenu->addSeparator();
    viewmenu->addAction(this->_view_25);
    viewmenu->addAction(this->_view_50);
    viewmenu->addAction(this->_view_75);
    viewmenu->addAction(this->_view_100);
    viewmenu->addAction(this->_view_300);
    viewmenu->addAction(this->_view_500);
    viewmenu->addSeparator();
    viewmenu->addAction(this->_style_switch);

    this->_run = new QAction("Run");
    this->_run->setShortcut(QKeySequence(Qt::Key_F5));

    auto runmenu = this->_menu->addMenu("&Run(R)");
    runmenu->addAction(this->_run);

    this->_newterminal = new QAction("New Terminal");
    this->_newterminal->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_F1));

    auto terminal = this->_menu->addMenu("&Terminal(T)");
    terminal->addAction(this->_newterminal);

    this->_document = new QAction("Document");

    auto helpmenu = this->_menu->addMenu("&Help(H)");
    helpmenu->addAction(this->_document);

}

double NE_Title::getStoredscale() const
{
    return this->_store_scale;
}

void NE_Title::setStoredscale(double scale)
{
    this->_store_scale = scale;
}

void NE_Title::init_control()
{
    connect(this->_min, &QPushButton::clicked, this, [this](){emit signalButtonMinClicked();}, Qt::DirectConnection);
    connect(this->_max, &QPushButton::clicked, this,[this](){this->onButtonMaxClicked();}, Qt::DirectConnection);
    connect(this->_restore, &QPushButton::clicked, this,[this](){this->onButtonRestoreClicked();}, Qt::DirectConnection);
    connect(this->_close, &QPushButton::clicked, this, [this](){emit signalButtonCloseClicked();}, Qt::DirectConnection);

    connect(this->_storescale, &QAction::triggered, this, [this](){emit signalStoreScale();}, Qt::DirectConnection);
    connect(this->_resetscale, &QAction::triggered, this, [this](){emit signalResetScale();}, Qt::DirectConnection);
    connect(this->_view_25, &QAction::triggered, this, [this](){emit signal25Scale();}, Qt::DirectConnection);
    connect(this->_view_50, &QAction::triggered, this, [this](){emit signal50Scale();}, Qt::DirectConnection);
    connect(this->_view_75, &QAction::triggered, this, [this](){emit signal75Scale();}, Qt::DirectConnection);
    connect(this->_view_100, &QAction::triggered, this, [this](){emit signal100Scale();}, Qt::DirectConnection);
    connect(this->_view_300, &QAction::triggered, this, [this](){emit signal300Scale();}, Qt::DirectConnection);
    connect(this->_view_500, &QAction::triggered, this, [this](){emit signal500Scale();}, Qt::DirectConnection);
    connect(this->_style_switch, &QAction::triggered, this, [this](){emit signalSwichStyle();}, Qt::DirectConnection);

}

void NE_Title::init_title_bar()
{
    this->set_icon(":/resource/icons/NE.png");
    this->set_titleContent(QString("Node Engine"));
    this->set_buttonType(MIN_BUTTON);
    this->set_titleWidth(this->width());
}

void NE_Title::set_background_color(int R, int G, int B)
{
    this->_bcolor_R = R;
    this->_bcolor_G = G;
    this->_bcolor_B = B;
    update();
}

void NE_Title::set_icon(const QString& path, QSize Iconsize)
{
    QPixmap titleicon(path);
    this->_ico->setPixmap(titleicon.scaled(Iconsize));
}

void NE_Title::set_titleContent(const QString& text, int titlesize)
{
    QFont font = this->_title->font();
    font.setPointSize(titlesize);
    this->_title->setFont(font);
    this->_title->setText(text);
    this->_title_content = text;
    this->_title->setAlignment(Qt::AlignLeft);
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
    QFile file(":/resource/styles/" + sheetName + ".qss");
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
//        this->_isPressed = true;
//        this->_mouseStartPos = event->globalPosition();
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
        this->parentWidget()->move(static_cast<int>(widgetPos.x()+movepoint.x()),
                                   static_cast<int>(widgetPos.y()+movepoint.y()));
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
