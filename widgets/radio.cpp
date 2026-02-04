#include "radio.h"

#include "color.h"
#include "private/utils.h"
#include "constants.h"

#include <QApplication>
#include <QPainter>
#include <QStyleOptionButton>

FRadio::FRadio(QWidget* parent)
    : FRadio("", false,  parent)
{}

FRadio::FRadio(const QString& text, QWidget* parent)
    : FRadio(text, false, parent)
{}

FRadio::FRadio(const QString& text, bool checked, QWidget* parent)
    : QRadioButton(text, parent)
{
    QRadioButton::setFont(FontHelper().setPixelSize(FConstants::FRadio::DefaultFontSize).getFont());

    _qsshelper.setProperty("QRadioButton", "spacing", QString::number(FConstants::FRadio::Spacing) + "px");
    _qsshelper.setProperty("QRadioButton", "color", FColor::regularText());
    _qsshelper.setProperty("QRadioButton:checked", "color", FColor::primary());
    _qsshelper.setProperty("QRadioButton:disabled", "color", FColor::placeholderText());
    _qsshelper.setProperty("QRadioButton:disabled:checked", "color", FColor::placeholderText());
    _qsshelper.setProperty("QRadioButton::indicator", "border", "1px solid " + FColor::baseBorder());

    _qsshelper.setProperty("QRadioButton::indicator", "background-color", "white");
    _qsshelper.setProperty("QRadioButton::indicator:checked", "border-color", FColor::primary());
    _qsshelper.setProperty("QRadioButton::indicator:checked", "background-color", FColor::primary());
    _qsshelper.setProperty("QRadioButton::indicator:disabled", "background-color", FColor::lightFill());
    _qsshelper.setProperty("QRadioButton::indicator:disabled:checked", "background-color", FColor::lightFill());
    _qsshelper.setProperty("QRadioButton::indicator:disabled:checked", "border-color", FColor::baseBorder());
    setStyleSheet(_qsshelper.generate());

    setSize(_size);
    setChecked(checked);
    setCursor(Qt::PointingHandCursor);
}

FRadio& FRadio::setValue(const QVariant& value)
{
    _value = value;
    return *this;
}

QVariant FRadio::getValue()
{
    return _value;
}

FRadio& FRadio::setText(const QString& text)
{
    QRadioButton::setText(text);
    return *this;
}

QString FRadio::getText()
{
    return QRadioButton::text();
}

FRadio& FRadio::setDisabled(bool disabled)
{
    QRadioButton::setEnabled(!disabled);
    return *this;
}

bool FRadio::isDisabled()
{
    return !QRadioButton::isEnabled();
}

FRadio& FRadio::setSize(Size size)
{
    _size = size;

    QRadioButton::setFont(FontHelper(QRadioButton::font())
            .setPixelSize(size == Size::Small ? FConstants::FRadio::SmallFontSize : FConstants::FRadio::DefaultFontSize)
            .getFont());

    if (size == Size::Small)
    {
        _qsshelper.setProperty("QRadioButton::indicator", "border-radius", QString::number(FConstants::FRadio::SmallIndicatorBorderRadius) + "px");
        _qsshelper.setProperty("QRadioButton::indicator", "width", QString::number(FConstants::FRadio::SmallIndicatorSize) + "px");
        _qsshelper.setProperty("QRadioButton::indicator", "height", QString::number(FConstants::FRadio::SmallIndicatorSize) + "px");
    }
    else
    {
        _qsshelper.setProperty("QRadioButton::indicator", "border-radius", QString::number(FConstants::FRadio::DefaultIndicatorBorderRadius) + "px");
        _qsshelper.setProperty("QRadioButton::indicator", "width", QString::number(FConstants::FRadio::DefaultIndicatorSize) + "px");
        _qsshelper.setProperty("QRadioButton::indicator", "height", QString::number(FConstants::FRadio::DefaultIndicatorSize) + "px");
    }

    setStyleSheet(_qsshelper.generate());
    int height = size == Size::Large ? FConstants::FRadio::LargeHeight 
                : size == Size::Default ? FConstants::FRadio::DefaultHeight 
                : FConstants::FRadio::SmallHeight;
    setFixedHeight(height);

    adjustSize();
    return *this;
}

FRadio::Size FRadio::getSize()
{
    return _size;
}

FRadio& FRadio::setChecked(bool checked)
{
    QRadioButton::setChecked(checked);
    return *this;
}

bool FRadio::getChecked()
{
    return QRadioButton::isChecked();
}

FRadio& FRadio::setBorder(bool border)
{
    _border = border;

    if (border)
    {
        if (_size == Size::Large)
            _qsshelper.setProperty("QRadioButton", "padding", 
                QString("0px %1px 0px %2px").arg(FConstants::FRadio::LargeBorderPaddingRight).arg(FConstants::FRadio::LargeBorderPaddingLeft));
        else if (_size == Size::Default)
            _qsshelper.setProperty("QRadioButton", "padding", 
                QString("0px %1px 0px %2px").arg(FConstants::FRadio::DefaultBorderPaddingRight).arg(FConstants::FRadio::DefaultBorderPaddingLeft));
        else
            _qsshelper.setProperty("QRadioButton", "padding", 
                QString("0px %1px 0px %2px").arg(FConstants::FRadio::SmallBorderPaddingRight).arg(FConstants::FRadio::SmallBorderPaddingLeft));

        _qsshelper.setProperty("QRadioButton", "border-radius", QString::number(FConstants::FRadio::BorderRadius) + "px");
        _qsshelper.setProperty("QRadioButton", "border", "1px solid " + FColor::baseBorder());
        _qsshelper.setProperty("QRadioButton:checked", "border-color", FColor::primary());
    }
    else
    {
        _qsshelper.setProperty("QRadioButton", "padding", "0px");
        _qsshelper.setProperty("QRadioButton", "border", "none");
    }

    setStyleSheet(_qsshelper.generate());
    adjustSize();
    return *this;
}

bool FRadio::getBorder()
{
    return _border;
}

void FRadio::paintEvent(QPaintEvent* event)
{
    QRadioButton::paintEvent(event);

    // 如果选中，绘制内部圆点（因为设置了背景色，默认圆点可能不显示）
    if (isChecked())
    {
        QStyleOptionButton option;
        initStyleOption(&option);
        QRect indicatorRect = style()->subElementRect(QStyle::SE_RadioButtonIndicator, &option, this);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        int centerX = indicatorRect.x() + indicatorRect.width() / 2;
        int centerY = indicatorRect.y() + indicatorRect.height() / 2;
        int radius = static_cast<int>(indicatorRect.width() * FConstants::FRadio::DotRadiusRatio);
        painter.setBrush(QBrush(QColor(isEnabled() ? FColor::blankFill() : FColor::placeholderText())));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
    }
}

void FRadio::enterEvent(QEvent* event)
{
    if (!isEnabled())
        QApplication::setOverrideCursor(Qt::ForbiddenCursor);
    QRadioButton::enterEvent(event);
}

void FRadio::leaveEvent(QEvent* event)
{
    if (!isEnabled())
        QApplication::restoreOverrideCursor();
    QRadioButton::leaveEvent(event);
}


FRadioGroup::FRadioGroup(QWidget* parent)
    : FRadioGroup({}, parent)
{}

FRadioGroup::FRadioGroup(const QList<FRadio*>& radios, QWidget* parent)
    : QGroupBox(parent)
    , _radios(radios)
    , _layout(new QHBoxLayout(this))
{
    setTitle("");

    _layout->setContentsMargins(FConstants::FRadio::GroupMarginLeft, FConstants::FRadio::GroupMarginTop, 
                                 FConstants::FRadio::GroupMarginRight, FConstants::FRadio::GroupMarginBottom);
    _layout->setSpacing(FConstants::FRadio::GroupSpacing);

    for (auto* radio : radios)
        addRadio(radio);

    setStyleSheet("QGroupBox { border: none; }");
}

FRadioGroup& FRadioGroup::addRadio(FRadio* checkbox)
{
    _radios.append(checkbox);
    _layout->addWidget(checkbox);
    adjustSize();
    return *this;
}

FRadioGroup& FRadioGroup::setTitle(const QString&)
{
    QGroupBox::setTitle("");
    return *this;
}

FRadioGroup& FRadioGroup::setSize(Size size)
{
    _size = size;

    for (auto* radio : _radios)
        radio->setSize(static_cast<FRadio::Size>(_size));

    adjustSize();
    return *this;
}

FRadioGroup::Size FRadioGroup::getSize()
{
    return _size;
}

FRadioGroup& FRadioGroup::setDisabled(bool disabled)
{
    QGroupBox::setEnabled(!disabled);
    return *this;
}

bool FRadioGroup::isDisabled()
{
    return !QGroupBox::isEnabled();
}

