#include "tag.h"

#include "color.h"
#include "icon.h"
#include "private/utils.h"
#include "constants.h"

#include <QEvent>

FTag::FTag(QWidget* parent) : FTag("Tag 1", Type::Info, parent)
{}

FTag::FTag(const QString& text, QWidget* parent) : FTag(text, Type::Info, parent)
{}

FTag::FTag(const QString& text, Type type, QWidget* parent)
    : QLabel(parent)
    , _type(type)
    , _textLabel(new QLabel(text, this))
    , _closeIcon(new QLabel(this))
    , _layout(new QHBoxLayout(this))
{
    _textLabel->setFont(FontHelper(_textLabel->font())
            .setPointSize(FConstants::FTag::TextFontSize)
            .getFont());
    _textLabel->setAlignment(Qt::AlignCenter);

    _closeIcon->setFixedSize(FConstants::FTag::CloseIconSize, FConstants::FTag::CloseIconSize);
    _closeIcon->setScaledContents(true);
    _closeIcon->setVisible(false);
    _closeIcon->installEventFilter(this);

    _layout->setContentsMargins(0, 0, 0, 0);
    _layout->setSpacing(FConstants::FTag::LayoutSpacing);
    _layout->addWidget(_textLabel);
    _layout->addWidget(_closeIcon);

    setLayout(_layout);

    setStyleSheet(_qsshelper.setProperty("QLabel", "border-radius", QString::number(FConstants::FTag::BorderRadius) + "px")
                            .setProperty("QLabel", "padding", QString::number(FConstants::FTag::PaddingVertical) + "px " + QString::number(FConstants::FTag::PaddingHorizontal) + "px")
                            .generate());
    adjustSize();
    setEffect(_effect);
    setType(_type);
    setSize(_size);
}

FTag& FTag::setEffect(Effect effect)
{
    _effect = effect;
    setType(_type);
    return *this;
}

FTag& FTag::setType(Type type)
{
    _type = type;
    setStyleSheet(_qsshelper.setProperty("QLabel", "color", getColor())
                            .setProperty("QLabel", "background-color", getBackgroundColor())
                            .setProperty("QLabel", "border", "1px solid " + getBorderColor())
                            .generate());

    _internalQsshelper.setProperty("QLabel", "border", "none")
                      .setProperty("QLabel", "padding", "0px");
    _textLabel->setStyleSheet(_internalQsshelper.generate());
    _closeIcon->setStyleSheet(_internalQsshelper.generate());

    _textLabel->adjustSize();
    return *this;
}

FTag& FTag::setSize(Size size)
{
    _size = size;
    if (_size == Size::Default)    setFixedHeight(FConstants::FTag::DefaultHeight), setMinimumWidth(FConstants::FTag::DefaultMinWidth);
    else if (_size == Size::Large) setFixedHeight(FConstants::FTag::LargeHeight), setMinimumWidth(FConstants::FTag::LargeMinWidth);
    else if (_size == Size::Small) setFixedHeight(FConstants::FTag::SmallHeight), setMinimumWidth(FConstants::FTag::SmallMinWidth);
    return *this;
}

FTag& FTag::setCloseable(bool closeable)
{
    _closeable = closeable;
    _closeIcon->setPixmap(FIcon::instance().getPixmap(FIcon::Close, getColor(), FConstants::FTag::CloseIconSize));
    _closeIcon->setVisible(closeable);
    return *this;
}

FTag& FTag::setRound(bool round)
{
    _round = round;
    if (_round)
        setStyleSheet(_qsshelper.setProperty("QLabel", "border-radius", QString::number(FConstants::FTag::RoundBorderRadius) + "px")
                                .generate());
    else
        setStyleSheet(_qsshelper.setProperty("QLabel", "border-radius", QString::number(FConstants::FTag::BorderRadius) + "px")
                                .generate());
    return *this;
}

FTag& FTag::setText(const QString& text)
{
    _textLabel->setText(text);
    return *this;
}

bool FTag::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == _closeIcon && _closeable)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            deleteLater();
            return true;
        }
        else if (event->type() == QEvent::Enter)
        {
            _closeIcon->setPixmap(FIcon::instance().getPixmap(FIcon::CircleCloseFilled, getColor(), FConstants::FTag::CloseIconSize));
        }
        else if (event->type() == QEvent::Leave)
        {
            _closeIcon->setPixmap(FIcon::instance().getPixmap(FIcon::Close, getColor(), FConstants::FTag::CloseIconSize));
        }
    }
    return QWidget::eventFilter(obj, event);
}

QString FTag::getColor()
{
    switch (_effect)
    {
    case Effect::Light:
    case Effect::Plain:
        switch (_type) {
            case Type::Primary: return FColor::primary();
            case Type::Success: return FColor::success();
            case Type::Warning: return FColor::warning();
            case Type::Info:    return FColor::info();
            case Type::Danger:  return FColor::danger();
        }
    case Effect::Dark:
        return FColor::basicWhite();
    }

    return "#000000";
}

QString FTag::getBorderColor()
{
    switch (_effect)
    {
    case Effect::Light:
        switch (_type) {
            case Type::Primary: return FColor::primaryL4();
            case Type::Success: return FColor::successL4();
            case Type::Warning: return FColor::warningL4();
            case Type::Info:    return FColor::infoL4();
            case Type::Danger:  return FColor::dangerL4();
        }
    case Effect::Plain:
        switch (_type) {
            case Type::Primary: return FColor::primaryL2();
            case Type::Success: return FColor::successL2();
            case Type::Warning: return FColor::warningL2();
            case Type::Info:    return FColor::infoL2();
            case Type::Danger:  return FColor::dangerL2();
        }
    case Effect::Dark:
        switch (_type) {
            case Type::Primary: return FColor::primary();
            case Type::Success: return FColor::success();
            case Type::Warning: return FColor::warning();
            case Type::Info:    return FColor::info();
            case Type::Danger:  return FColor::danger();
        }
    }
    return "#000000";
}

QString FTag::getBackgroundColor()
{
    switch (_effect)
    {
    case Effect::Light:
        switch (_type) {
            case Type::Primary: return FColor::primaryL5();
            case Type::Success: return FColor::successL5();
            case Type::Warning: return FColor::warningL5();
            case Type::Info:    return FColor::infoL5();
            case Type::Danger:  return FColor::dangerL5();
        }
    case Effect::Dark:
        switch (_type) {
            case Type::Primary: return FColor::primary();
            case Type::Success: return FColor::success();
            case Type::Warning: return FColor::warning();
            case Type::Info:    return FColor::info();
            case Type::Danger:  return FColor::danger();
        }
    case Effect::Plain:
           return FColor::basicWhite();
    }
    return "#000000";
}

