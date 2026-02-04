#include "inputnumber.h"

#include "private/utils.h"
#include "color.h"
#include "constants.h"

#include <QLineEdit>

FInputNumber::FInputNumber(int value, QWidget* parent)
    : FInputNumber(parent)
{
    QSpinBox::setValue(value);
    setSize(Size::Small);
}

FInputNumber::FInputNumber(QWidget* parent)
    : QSpinBox(parent)
{
    setSize(Size::Default);
    setAlignment(Qt::AlignCenter);
    connect(this, QOverload<int>::of(&QSpinBox::valueChanged), this, &FInputNumber::onvalueChanged);
}

FInputNumber::Size FInputNumber::getSize()
{
    return _size;
}

FInputNumber& FInputNumber::setSize(Size size)
{
    _size = size;

    int width;
    int height;
    QString fontSize;
    QString buttonWidth;
    QString buttonHeight;

    if (size == Size::Large)
    {
        fontSize = QString::number(FConstants::FInputNumber::LargeFontSize) + "px";
        width = FConstants::FInputNumber::LargeWidth;
        height = FConstants::FInputNumber::LargeHeight;
        buttonWidth = QString::number(FConstants::FInputNumber::LargeButtonWidth) + "px";
        buttonHeight = QString::number(FConstants::FInputNumber::LargeButtonHeight) + "px";
    }
    else if (size == Size::Default)
    {
        fontSize = QString::number(FConstants::FInputNumber::DefaultFontSize) + "px";
        width = FConstants::FInputNumber::DefaultWidth;
        height = FConstants::FInputNumber::DefaultHeight;
        buttonWidth = QString::number(FConstants::FInputNumber::DefaultButtonWidth) + "px";
        buttonHeight = QString::number(FConstants::FInputNumber::DefaultButtonHeight) + "px";
    }
    else
    {
        fontSize = QString::number(FConstants::FInputNumber::SmallFontSize) + "px";
        width = FConstants::FInputNumber::SmallWidth;
        height = FConstants::FInputNumber::SmallHeight;
        buttonWidth = QString::number(FConstants::FInputNumber::SmallButtonWidth) + "px";
        buttonHeight = QString::number(FConstants::FInputNumber::SmallButtonHeight) + "px";
    }

    _qssHelper.setProperty("QSpinBox", "font-family", Comm::fontFmaily)
        .setProperty("QSpinBox", "font-size", fontSize)
        .setProperty("QSpinBox", "color", FColor::regularText())
        .setProperty("QSpinBox", "background", FColor::baseBackground())
        .setProperty("QSpinBox", "border-radius", QString::number(FConstants::FInputNumber::BorderRadius) + "px")
        .setProperty("QSpinBox", "border", "1px solid " + FColor::baseBorder())
        .setProperty("QSpinBox", "min-height", QString::number(height) + "px")
        .setProperty("QSpinBox:hover", "border", "1px solid " + FColor::disabledText())
        .setProperty("QSpinBox:focus", "border", "1px solid " + FColor::primary())
        .setProperty("QSpinBox:disabled", "border", "1px solid " + FColor::lightBorder())
        .setProperty("QSpinBox:disabled", "background", FColor::lightFill())
        .setProperty("QSpinBox:disabled", "color", FColor::placeholderText())

        .setProperty("QSpinBox:down-button", "subcontrol-origin", "margin")
        .setProperty("QSpinBox:down-button", "subcontrol-position", "center left")
        .setProperty("QSpinBox:down-button", "background-color", FColor::lightFill())
        .setProperty("QSpinBox:down-button", "left", QString::number(FConstants::FInputNumber::ButtonPositionOffset) + "px")
        .setProperty("QSpinBox:down-button", "width", buttonWidth)
        .setProperty("QSpinBox:down-button", "height", buttonHeight)

        .setProperty("QSpinBox:up-button", "subcontrol-origin", "margin")
        .setProperty("QSpinBox:up-button", "subcontrol-position", "center right")
        .setProperty("QSpinBox:up-button", "background-color", FColor::lightFill())
        .setProperty("QSpinBox:up-button", "right", QString::number(FConstants::FInputNumber::ButtonPositionOffset) + "px")
        .setProperty("QSpinBox:up-button", "width", buttonWidth)
        .setProperty("QSpinBox:up-button", "height", buttonHeight);

    if (size == Size::Large || size == Size::Default)
    {
        QString iconSize = QString::number(FConstants::FInputNumber::LargeDefaultIconSize);
        _qssHelper.setProperty("QSpinBox:down-button", "image", "url(:/icons/special/minus-regular-text-" + iconSize + ".png)")
            .setProperty("QSpinBox:down-button:hover", "image", "url(:/icons/special/minus-primary-" + iconSize + ".png)")
            .setProperty("QSpinBox:down-button:disabled", "image", "url(:/icons/special/minus-light-border-" + iconSize + ".png)")
            .setProperty("QSpinBox:up-button", "image", "url(:/icons/special/plus-regular-text-" + iconSize + ".png)")
            .setProperty("QSpinBox:up-button:hover", "image", "url(:/icons/special/plus-primary-" + iconSize + ".png)")
            .setProperty("QSpinBox:up-button:disabled", "image", "url(:/icons/special/plus-light-border-" + iconSize + ".png)");
    }
    else
    {
        QString iconSize = QString::number(FConstants::FInputNumber::SmallIconSize);
        _qssHelper.setProperty("QSpinBox:down-button", "image", "url(:/icons/special/minus-regular-text-" + iconSize + ".png)")
            .setProperty("QSpinBox:down-button:hover", "image", "url(:/icons/special/minus-primary-" + iconSize + ".png)")
            .setProperty("QSpinBox:down-button:disabled", "image", "url(:/icons/special/minus-light-border-" + iconSize + ".png)")
            .setProperty("QSpinBox:up-button", "image", "url(:/icons/special/plus-regular-text-" + iconSize + ".png)")
            .setProperty("QSpinBox:up-button:hover", "image", "url(:/icons/special/plus-primary-" + iconSize + ".png)")
            .setProperty("QSpinBox:up-button:disabled", "image", "url(:/icons/special/plus-light-border-" + iconSize + ".png)");
    }

    setStyleSheet(_qssHelper.generate());
    setFixedSize(width, height);

    return *this;
}

bool FInputNumber::isDisabled()
{
    return !QSpinBox::isEnabled();
}

FInputNumber& FInputNumber::setDisabled(bool disabled)
{
    QSpinBox::setDisabled(disabled);
    return *this;
}

bool FInputNumber::getReadOnly()
{
    return QSpinBox::isReadOnly();
}

FInputNumber& FInputNumber::setReadOnly(bool readonly)
{
    QSpinBox::setReadOnly(readonly);
    return *this;
}

FInputNumber::ControlsPosition FInputNumber::getControlsPosition()
{
    return _controlsPosition;
}

FInputNumber& FInputNumber::setControlsPosition(ControlsPosition controlsPosition)
{
    _controlsPosition = controlsPosition;
    return *this;
}

int FInputNumber::getValue()
{
    return QSpinBox::value();
}

FInputNumber& FInputNumber::setValue(int value)
{
    QSpinBox::setValue(value);
    return *this;
}

QString FInputNumber::getPrefix()
{
    return QSpinBox::prefix();
}

FInputNumber& FInputNumber::setPrefix(const QString &prefix)
{
    QSpinBox::setPrefix(prefix + " ");
    return *this;
}

QString FInputNumber::getSuffix()
{
    return QSpinBox::suffix();
}

FInputNumber& FInputNumber::setSuffix(const QString &suffix)
{
    QSpinBox::setSuffix(" " + suffix);
    return *this;
}

int FInputNumber::getStep()
{
    return QSpinBox::singleStep();
}

FInputNumber& FInputNumber::setStep(int val)
{
    QSpinBox::setSingleStep(val);
    return *this;
}

int FInputNumber::getMin()
{
    return QSpinBox::minimum();
}

FInputNumber& FInputNumber::setMin(int min)
{
    QSpinBox::setMinimum(min);
    return *this;
}

int FInputNumber::getMax()
{
    return QSpinBox::maximum();
}

FInputNumber& FInputNumber::setMax(int max)
{
    QSpinBox::setMaximum(max);
    return *this;
}

FInputNumber& FInputNumber::setRange(int min, int max)
{
    QSpinBox::setRange(min, max);
    return *this;
}

void FInputNumber::onvalueChanged(int)
{
    QSpinBox::lineEdit()->deselect();
}
