#include "message.h"
#include "private/utils.h"
#include "icon.h"
#include "constants.h"

#include <QBoxLayout>
#include <QPainter>
#include <QTimer>
#include <QHash>
#include <QPainterPath>

FMessage::FMessage(const QString& message, QWidget* parent)
    : FMessage(message, "", Type::Info, parent)
{}

FMessage::FMessage(const QString& message, const QString& paramater, QWidget* parent)
    : FMessage(message, paramater, Type::Info, parent)
{}

FMessage::FMessage(const QString& message, FMessage::Type type, QWidget* parent)
    : FMessage(message, "", type, parent)
{}

FMessage::FMessage(const QString& message, const QString& paramater, Type type, QWidget* parent)
    : QWidget(parent)
    , _message(message)
    , _paramater(paramater)
    , _type(type)
    , _icon(new QLabel(this))
    , _text(new QLabel(this))
    , _timer(new QTimer(this))
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);

    _text->setFont(FontHelper(_text->font())
            .setPointSize(Comm::defaultFontSize)
            .getFont());

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(FConstants::FMessage::Margin, FConstants::FMessage::Margin, FConstants::FMessage::Margin, FConstants::FMessage::Margin);
    layout->setSpacing(FConstants::FMessage::Spacing);
    layout->addWidget(_icon);
    layout->addWidget(_text);

    setLayout(layout);

    setType(_type);
    connect(_timer, &QTimer::timeout, this, &FMessage::onTimeout);
}

void FMessage::show()
{
    updatePosition();
    QWidget::show();
    _timer->start(_duration);
}

FMessage& FMessage::setMessage(const QString& message)
{
    _message = message;
    updateTextAndIcon();
    adjustSize();

    return *this;
}

FMessage& FMessage::setParamater(const QString& paramater)
{
    _paramater = paramater;
    updateTextAndIcon();
    adjustSize();
    return *this;
}

FMessage& FMessage::setType(FMessage::Type type)
{
    _type = type;
    updateTextAndIcon();
    adjustSize();
    return *this;
}

FMessage& FMessage::setPlain(bool plain)
{
    _plain = plain;
    return *this;
}

FMessage& FMessage::setShowClose(bool showClose, bool autoClose)
{
    _showClose = showClose;
    if (!autoClose)
    {}
    return *this;
}

FMessage& FMessage::setPlacement(FMessage::Place placement)
{
    _placement = placement;
    return *this;
}

FMessage& FMessage::setDuration(int msec)
{
    _duration = msec;
    return *this;
}

void FMessage::updateTextAndIcon()
{
    QString coloredMessage = QString("<span style='color:%1'>%2</span>")
        .arg(getColor())
        .arg(_message);

    QString coloredParameter = QString("<span style='color:%1'>%2</span>")
        .arg(FConstants::FMessage::ParameterColor)
        .arg(_paramater);

    _text->setText(coloredMessage + coloredParameter);

    _icon->setPixmap(getIcon());
}

void FMessage::updatePosition()
{
    QRect parentRect = parentWidget()->geometry();
    QSize widgetSize = size();

    int x = 0, y = 0;

    if (_placement == Place::Top) {
        x = (parentRect.width() - widgetSize.width()) / 2;
        y = FConstants::FMessage::Offset + (FConstants::FMessage::Offset + widgetSize.height()) * _count[Place::Top]++;
    }
    else if (_placement == Place::TopLeft) {
        x = FConstants::FMessage::Offset;
        y = FConstants::FMessage::Offset + (FConstants::FMessage::Offset + widgetSize.height()) * _count[Place::TopLeft]++;
    }
    else if (_placement == Place::TopRight) {
        x = parentRect.width() - widgetSize.width() - FConstants::FMessage::Offset;
        y = FConstants::FMessage::Offset + (FConstants::FMessage::Offset + widgetSize.height()) * _count[Place::TopRight]++;
    }
    else if (_placement == Place::Bottom) {
        x = (parentRect.width() - widgetSize.width()) / 2;
        y = parentRect.height() - (widgetSize.height() + FConstants::FMessage::Offset) * ++_count[Place::Bottom];
    }
    else if (_placement == Place::BottomLeft) {
        x = FConstants::FMessage::Offset;
        y = parentRect.height() - (widgetSize.height() + FConstants::FMessage::Offset) * ++_count[Place::BottomLeft];
    }
    else if (_placement == Place::BottomRight) {
        x = parentRect.width() - widgetSize.width() - FConstants::FMessage::Offset;
        y = parentRect.height() - (widgetSize.height() + FConstants::FMessage::Offset) * ++_count[Place::BottomRight];
    }

    move(x, y);
}

QString FMessage::getColor()
{
    switch (_type)
    {
    case Type::Primary: return FColor::primary();
    case Type::Success: return FColor::success();
    case Type::Warning: return FColor::warning();
    case Type::Info: return FColor::info();
    case Type::Error: return FColor::danger();
    }
    return "#000000";
}

QString FMessage::getBorderColor()
{
    switch (_type)
    {
    case Type::Primary: return FColor::primaryL4();
    case Type::Success: return FColor::successL4();
    case Type::Warning: return FColor::warningL4();
    case Type::Info: return FColor::infoL4();
    case Type::Error: return FColor::dangerL4();
    }
    return "#000000";
}

QString FMessage::getBackgroundColor()
{
    switch (_type)
    {
    case Type::Primary: return FColor::primaryL5();
    case Type::Success: return FColor::successL5();
    case Type::Warning: return FColor::warningL5();
    case Type::Info: return FColor::infoL5();
    case Type::Error: return FColor::dangerL5();
    }
    return "#000000";
}

QPixmap FMessage::getIcon()
{
    switch (_type)
    {
    case Type::Primary: return FIcon::instance().getPixmap(FIcon::InfoFilled, FColor::primary(), FConstants::FMessage::IconSize);
    case Type::Success: return FIcon::instance().getPixmap(FIcon::SuccessFilled, FColor::success(), FConstants::FMessage::IconSize);
    case Type::Warning: return FIcon::instance().getPixmap(FIcon::WarningFilled, FColor::warning(), FConstants::FMessage::IconSize);
    case Type::Info:    return FIcon::instance().getPixmap(FIcon::InfoFilled, FColor::info(), FConstants::FMessage::IconSize);
    case Type::Error:   return FIcon::instance().getPixmap(FIcon::CircleCloseFilled, FColor::danger(), FConstants::FMessage::IconSize);
    }
    return QPixmap();
}

void FMessage::onTimeout()
{
    _count[_placement]--;
    QWidget::close();
}

void FMessage::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制圆角背景
    QPainterPath path;
    path.addRoundedRect(rect().adjusted(0, 0, 0, 0), FConstants::FMessage::BorderRadius, FConstants::FMessage::BorderRadius, Qt::AbsoluteSize);
    painter.setClipPath(path);

    // 填充背景
    painter.fillPath(path, QColor(getBackgroundColor()));

    // 绘制边框
    painter.setPen(QPen(QColor(getBorderColor()), FConstants::FMessage::BorderWidth));
    painter.drawRoundedRect(rect().adjusted(0, 0, 0, 0), FConstants::FMessage::BorderRadius, FConstants::FMessage::BorderRadius, Qt::AbsoluteSize);

    QWidget::paintEvent(event);
}

