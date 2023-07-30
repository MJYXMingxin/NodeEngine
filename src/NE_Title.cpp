#include "NE_Title.h"

NE_Title::NE_Title(QWidget *parent)
        : QWidget{parent}
{
    init_title();
    init_menubar();
    init_title_bar();
    init_control();
    loadStyleSheet("TitleBar");
}

void NE_Title::init_title()
{
    _ico = new QLabel;
    _title = new QLabel;
    _menu = new QMenuBar;
    _min = new QPushButton;
    _max = new QPushButton;
    _restore = new QPushButton;
    _close = new QPushButton;

    _menu->setFixedWidth(700);

    _min->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    _max->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    _restore->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    _close->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));

    _title->setObjectName("Title");
    _min->setObjectName("ButtonMin");
    _max->setObjectName("ButtonMax");
    _restore->setObjectName("ButtonRestore");
    _close->setObjectName("ButtonClose");

    _min->setToolTip(QStringLiteral("最小化"));
    _max->setToolTip(QStringLiteral("最大化"));
    _restore->setToolTip(QStringLiteral("还原"));
    _close->setToolTip(QStringLiteral("关闭"));

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);
    _title->setPalette(pe);

    _restore->setVisible(false);

    _min->setIcon(style()->standardIcon(QStyle::SP_TitleBarMinButton));
    _max->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
    _restore->setIcon(style()->standardIcon(QStyle::SP_TitleBarNormalButton));
    _close->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));

    auto* title_layout = new QHBoxLayout(this);
    title_layout->addWidget(_ico);
    title_layout->addWidget(_menu);
    title_layout->addWidget(_title);

    title_layout->addSpacing(180);

    title_layout->addWidget(_min);
    title_layout->addWidget(_max);
    title_layout->addWidget(_restore);
    title_layout->addWidget(_close);

    title_layout->setContentsMargins(5, 0, 0, 0);
    title_layout->setSpacing(0);

    _title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setFixedHeight(TITLE_HEIGHT);
    setWindowFlags(Qt::FramelessWindowHint);
}

void NE_Title::init_menubar()
{
    auto filemenu = _menu->addMenu("&File(F)");
    _newAction = new QAction("New File");
    _newAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    _newWindow = new QAction("New Window");
    _newWindow->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_N));
    _openAction = new QAction("Open File");
    _openAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    _saveAction = new QAction("Save File");
    _saveAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    _exitAction = new QAction("Exit");

    filemenu->addAction(_newAction);
    filemenu->addAction(_newWindow);
    filemenu->addSeparator();
    filemenu->addAction(_openAction);
    filemenu->addSeparator();
    filemenu->addAction(_saveAction);
    filemenu->addSeparator();
    filemenu->addAction(_exitAction);

    _copyAction = new QAction("Copy");
    _copyAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_C));
    _cutAction = new QAction("Cut");
    _cutAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_X));
    _pasteAction = new QAction("Paste");
    _pasteAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_V));
    _undoAction = new QAction("Undo");
    _undoAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z));
    _redoAction = new QAction("Redo");
    _redoAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y));
    _findAction = new QAction("Find");
    _findAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_F));
    _replaceAction = new QAction("Replace");
    _replaceAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_H));
    _retract = new QAction("Retract All");
    _retract->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Tab));
    _expand = new QAction("Expand All");
    _expand->setShortcut(QKeySequence(Qt::SHIFT | Qt::Key_Tab));

    auto editmenu = _menu->addMenu("&Edit(E)");
    editmenu->addAction(_undoAction);
    editmenu->addAction(_redoAction);
    editmenu->addSeparator();
    editmenu->addAction(_copyAction);
    editmenu->addAction(_cutAction);
    editmenu->addAction(_pasteAction);
    editmenu->addSeparator();
    editmenu->addAction(_findAction);
    editmenu->addAction(_replaceAction);
    editmenu->addSeparator();
    editmenu->addAction(_retract);
    editmenu->addAction(_expand);

    _selectAll = new QAction("Select All");
    _selectAll->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_A));
    _duplicate = new QAction("Duplicate");
    _duplicate->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_D));

    auto selectionmenu = _menu->addMenu("&Selection(S)");
    selectionmenu->addAction(_selectAll);
    selectionmenu->addSeparator();
    selectionmenu->addAction(_duplicate);

    _storescale = new QAction("Store Current Scale");
    _storescale->setShortcut(QKeySequence(Qt::SHIFT | Qt::Key_S));
    _resetscale = new QAction("Reset Scale by Stored Value");
    _resetscale->setShortcut(QKeySequence(Qt::SHIFT | Qt::Key_R));
    _view_25 = new QAction("25%");
    _view_50 = new QAction("50%");
    _view_75 = new QAction("75%");
    _view_100 = new QAction("100%");
    _view_300 = new QAction("300%");
    _view_500 = new QAction("500%");
    _style_switch = new QAction("Switch Canvas Style");
    _style_switch->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_QuoteLeft));

    auto viewmenu = _menu->addMenu("&View(V)");
    viewmenu->addAction(_storescale);
    viewmenu->addAction(_resetscale);
    viewmenu->addSeparator();
    viewmenu->addAction(_view_25);
    viewmenu->addAction(_view_50);
    viewmenu->addAction(_view_75);
    viewmenu->addAction(_view_100);
    viewmenu->addAction(_view_300);
    viewmenu->addAction(_view_500);
    viewmenu->addSeparator();
    viewmenu->addAction(_style_switch);

    _run = new QAction("Run");
    _run->setShortcut(QKeySequence(Qt::Key_F5));

    auto runmenu = _menu->addMenu("&Run(R)");
    runmenu->addAction(_run);

    _newterminal = new QAction("New Terminal");
    _newterminal->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_F1));

    auto terminal = _menu->addMenu("&Terminal(T)");
    terminal->addAction(_newterminal);

    _document = new QAction("Document");

    auto helpmenu = _menu->addMenu("&Help(H)");
    helpmenu->addAction(_document);

}

double NE_Title::getStoredscale() const
{
    return _store_scale;
}

void NE_Title::setStoredscale(double scale)
{
    _store_scale = scale;
}

void NE_Title::init_control()
{
    connect(_min, &QPushButton::clicked, this, [this](){emit signalButtonMinClicked();}, Qt::DirectConnection);
    connect(_max, &QPushButton::clicked, this,[this](){onButtonMaxClicked();}, Qt::DirectConnection);
    connect(_restore, &QPushButton::clicked, this,[this](){onButtonRestoreClicked();}, Qt::DirectConnection);
    connect(_close, &QPushButton::clicked, this, [this](){emit signalButtonCloseClicked();}, Qt::DirectConnection);

    connect(_exitAction, &QAction::triggered, this, [this](){emit signalButtonCloseClicked();}, Qt::DirectConnection);

    connect(_storescale, &QAction::triggered, this, [this](){emit signalStoreScale();}, Qt::DirectConnection);
    connect(_resetscale, &QAction::triggered, this, [this](){emit signalResetScale();}, Qt::DirectConnection);
    connect(_view_25, &QAction::triggered, this, [this](){emit signal25Scale();}, Qt::DirectConnection);
    connect(_view_50, &QAction::triggered, this, [this](){emit signal50Scale();}, Qt::DirectConnection);
    connect(_view_75, &QAction::triggered, this, [this](){emit signal75Scale();}, Qt::DirectConnection);
    connect(_view_100, &QAction::triggered, this, [this](){emit signal100Scale();}, Qt::DirectConnection);
    connect(_view_300, &QAction::triggered, this, [this](){emit signal300Scale();}, Qt::DirectConnection);
    connect(_view_500, &QAction::triggered, this, [this](){emit signal500Scale();}, Qt::DirectConnection);
    connect(_style_switch, &QAction::triggered, this, [this](){emit signalSwichStyle();}, Qt::DirectConnection);

}

void NE_Title::init_title_bar()
{
    set_icon(":/resource/icons/NE.png");
    set_titleContent(QString("Node Engine"));
    set_buttonType(MIN_BUTTON);
    set_titleWidth(width());
}

void NE_Title::set_background_color(int R, int G, int B)
{
    _bcolor_R = R;
    _bcolor_G = G;
    _bcolor_B = B;
    update();
}

void NE_Title::set_icon(const QString& path, QSize Iconsize)
{
    QPixmap titleicon(path);
    _ico->setPixmap(titleicon.scaled(Iconsize));
}

void NE_Title::set_titleContent(const QString& text, int titlesize)
{
    QFont font = _title->font();
    font.setPointSize(titlesize);
    _title->setFont(font);
    _title->setText(text);
    _title_content = text;
    _title->setAlignment(Qt::AlignLeft);
//    _title->setStyleSheet("QLabel{padding-left:220px;}");
}

void NE_Title::set_titleWidth(int width)
{
    setFixedWidth(width);
}

void NE_Title::set_buttonType(ButtonType type)
{
    _button_Type = type;

    switch(type)
    {
        case MIN_BUTTON:
        {
            _restore->setVisible(false);
            _max->setVisible(false);
        }
            break;
        case MIN_MAX_BUTTON:
        {
            _restore->setVisible(false);
        }
            break;
        case ONLY_CLOSE_BUTTON:
        {
            _min->setVisible(false);
            _max->setVisible(false);
            _restore->setVisible(false);
        }
            break;
        default:
            break;
    }
}

void NE_Title::set_windowBorderWidth(int width)
{
    _window_border_width = width;
}

void NE_Title::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPainterPath pathback;
    pathback.setFillRule(Qt::WindingFill);
    pathback.addRoundedRect(QRect(0,0,width(),height()),0,0);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(pathback,QBrush(QColor(_bcolor_R,
                                            _bcolor_G,
                                            _bcolor_B)));
    if (width() != (parentWidget()->width() - _borderwidth))
    {
        setFixedWidth(parentWidget()->width() - _borderwidth);
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
        setStyleSheet(styleSheet);
    }
}

void NE_Title::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(_button_Type == MIN_MAX_BUTTON)
    {
        if(_max->isVisible())
            onButtonMaxClicked();
        else
            onButtonRestoreClicked();
    }
    return QWidget::mouseDoubleClickEvent(event);
}

void NE_Title::mousePressEvent(QMouseEvent *event)
{
    if(_button_Type == MIN_MAX_BUTTON &&
       _max->isVisible())
    {
        _isPressed = true;
        _mouseStartPos = event->globalPosition();
    }
    else
    {
//        _isPressed = true;
//        _mouseStartPos = event->globalPosition();
    }
    return QWidget::mousePressEvent(event);
}

void NE_Title::mouseMoveEvent(QMouseEvent *event)
{
    if(_isPressed)
    {
        QPointF movepoint = event->globalPosition() - _mouseStartPos;
        QPointF widgetPos = parentWidget()->pos();
        _mouseStartPos = event->globalPosition();
        parentWidget()->move(static_cast<int>(widgetPos.x()+movepoint.x()),
                                   static_cast<int>(widgetPos.y()+movepoint.y()));
    }
    return QWidget::mouseMoveEvent(event);
}

void NE_Title::mouseReleaseEvent(QMouseEvent *event)
{
    _isPressed = false;
    return QWidget::mouseReleaseEvent(event);
}

void NE_Title::onButtonMaxClicked()
{
    _max->setVisible(false);
    _restore->setVisible(true);
    emit signalButtonMaxClicked();
}

void NE_Title::onButtonRestoreClicked()
{
    _restore->setVisible(false);
    _max->setVisible(true);
    emit signalButtonRestoreClicked();
}
