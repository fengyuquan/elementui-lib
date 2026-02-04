#include "notification.h"
#include "private/utils.h"
#include "icon.h"
#include "shadow.h"
#include "constants.h"

#include <QBoxLayout>
#include <QPainter>
#include <QTimer>
#include <QHash>
#include <QEvent>
#include <QPainterPath>

FNotification::FNotification(const QString& title, const QString& content, QWidget* parent)
    : FNotification(title, content, Type::Primary, parent)
{}

FNotification::FNotification(const QString& title, const QString& content, Type type, QWidget* parent)
    : QWidget(parent)
    , _icon(new QLabel(this))
    , _title(new QLabel(title, this))
    , _close(new QLabel(this))
    , _content(new QLabel(content, this))
    , _type(type)
    , _timer(new QTimer(this))
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setMinimumSize(FConstants::FNotification::MinWidth, FConstants::FNotification::MinHeight);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(FConstants::FNotification::MarginHorizontal, FConstants::FNotification::MarginTop, FConstants::FNotification::MarginHorizontal, FConstants::FNotification::MarginBottom);
    mainLayout->setSpacing(FConstants::FNotification::Spacing);

    QHBoxLayout* layout1 = new QHBoxLayout;
    layout1->addWidget(_icon);
    layout1->addWidget(_title);
    layout1->addStretch();
    layout1->addWidget(_close);

    QHBoxLayout* layout2 = new QHBoxLayout;
    layout2->addSpacing(FConstants::FNotification::ContentLeftSpacing);
    layout2->addWidget(_content);
    layout2->addSpacing(FConstants::FNotification::ContentRightSpacing);

    mainLayout->addLayout(layout1);
    mainLayout->addLayout(layout2);
    setLayout(mainLayout);

    setupUI();

    setType(_type);
    connect(_timer, &QTimer::timeout, this, &FNotification::onTimeout);
    connect(_close, &QLabel::linkActivated, this, &FNotification::onTimeout);
}

void FNotification::setupUI()
{
    _title->setFont(FontHelper(_title->font())
            .setPointSize(Comm::largeFontSize)
            .setBold(true)
            .getFont());

    _content->setFont(FontHelper(_content->font())
            .setPointSize(Comm::defaultFontSize)
            .getFont());

    _title->adjustSize();
    _content->setWordWrap(true);
    _content->adjustSize();

    _close->setPixmap(FIcon::instance().getPixmap(FIcon::Close, FColor::secondaryText(), FConstants::FNotification::CloseIconSize));

    _close->setAttribute(Qt::WA_Hover);
    _close->installEventFilter(this);

    QPalette palette = _title->palette();
    palette.setColor(QPalette::WindowText, FColor::primaryText());
    _title->setPalette(palette);

    palette = _content->palette();
    palette.setColor(QPalette::WindowText, FColor::regularText());
    _content->setPalette(palette);

    FShadowEf::setShadow(this, FShadowEf::Type::Dark);
}

void FNotification::show()
{
    updatePosition();
    QWidget::show();
    _timer->start(_duration);
}

FNotification& FNotification::setTitle(const QString& title)
{
    _title->setText(title);
    adjustSize();
    return *this;
}

FNotification& FNotification::setContent(const QString& content)
{
    _content->setText(content);
    adjustSize();
    return *this;
}

FNotification& FNotification::setType(FNotification::Type type)
{
    _type = type;
    _icon->setPixmap(getIcon());
    adjustSize();
    return *this;
}

FNotification& FNotification::setShowClose(bool showClose, bool autoClose)
{
    _showClose = showClose;
    if (!autoClose)
    {}
    return *this;
}

FNotification& FNotification::setPosition(FNotification::Position position)
{
    _positon = position;
    return *this;
}

FNotification& FNotification::setDuration(int msec)
{
    _duration = msec;
    return *this;
}

void FNotification::updatePosition()
{
    QRect parentRect = parentWidget()->geometry();
    QSize widgetSize = size();

    int x = 0, y = 0;

    if (_positon == Position::TopLeft) {
        x = FConstants::FNotification::PositionOffset;
        y = FConstants::FNotification::Offset + (FConstants::FNotification::Offset + widgetSize.height()) * _count[Position::TopLeft]++;
    }
    else if (_positon == Position::TopRight) {
        x = parentRect.width() - widgetSize.width() - FConstants::FNotification::PositionOffset;
        y = FConstants::FNotification::Offset + (FConstants::FNotification::Offset + widgetSize.height()) * _count[Position::TopRight]++;
    }
    else if (_positon == Position::BottomLeft) {
        x = FConstants::FNotification::PositionOffset;
        y = parentRect.height() - (widgetSize.height() + FConstants::FNotification::Offset) * ++_count[Position::BottomLeft];
    }
    else if (_positon == Position::BottomRight) {
        x = parentRect.width() - widgetSize.width() - FConstants::FNotification::PositionOffset;
        y = parentRect.height() - (widgetSize.height() + FConstants::FNotification::Offset) * ++_count[Position::BottomRight];
    }

    move(x, y);
}

QPixmap FNotification::getIcon()
{
    switch (_type)
    {
    case Type::Defualt: return QPixmap();
    case Type::Primary: return FIcon::instance().getPixmap(FIcon::InfoFilled, FColor::primary(), FConstants::FNotification::IconSize);
    case Type::Success: return FIcon::instance().getPixmap(FIcon::SuccessFilled, FColor::success(), FConstants::FNotification::IconSize);
    case Type::Warning: return FIcon::instance().getPixmap(FIcon::WarningFilled, FColor::warning(), FConstants::FNotification::IconSize);
    case Type::Info:    return FIcon::instance().getPixmap(FIcon::InfoFilled, FColor::info(), FConstants::FNotification::IconSize);
    case Type::Error:   return FIcon::instance().getPixmap(FIcon::CircleCloseFilled, FColor::danger(), FConstants::FNotification::IconSize);
    }
    return QPixmap();
}

void FNotification::onTimeout()
{
    _count[_positon]--;
    QWidget::close();
}

void FNotification::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制圆角背景
    QPainterPath path;
    path.addRoundedRect(rect().adjusted(FConstants::FNotification::BorderAdjust, FConstants::FNotification::BorderAdjust, -FConstants::FNotification::BorderAdjust, -FConstants::FNotification::BorderAdjust), FConstants::FNotification::BorderRadius, FConstants::FNotification::BorderRadius, Qt::AbsoluteSize);
    painter.setClipPath(path);

    // 填充背景
    painter.fillPath(path, QColor(Qt::white));

    QWidget::paintEvent(event);
}

bool FNotification::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == _close)
    {
        if (event->type() == QEvent::HoverEnter)
        {
            _close->setPixmap(FIcon::instance().getPixmap(FIcon::Close, FColor::regularText(), FConstants::FNotification::CloseIconSize));
            _close->setCursor(Qt::PointingHandCursor);
            return true;
        }
        else if (event->type() == QEvent::HoverLeave)
        {
            _close->setPixmap(FIcon::instance().getPixmap(FIcon::Close, FColor::secondaryText(), FConstants::FNotification::CloseIconSize));
            _close->setCursor(Qt::ArrowCursor);
            return true;
        }
        else if (event->type() == QEvent::MouseButtonPress)
        {
            emit _close->linkActivated("");
        }
    }
    return QWidget::eventFilter(watched, event);
}

