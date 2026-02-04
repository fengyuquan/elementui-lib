#include "checkbox.h"

#include "color.h"
#include "private/utils.h"
#include "constants.h"

#include <QApplication>
#include <QPainter>
#include <QStyleOptionButton>

FCheckbox::FCheckbox(QWidget* parent)
    : FCheckbox("", false,  parent)
{}

FCheckbox::FCheckbox(const QString& text, QWidget* parent)
    : FCheckbox(text, false, parent)
{}

FCheckbox::FCheckbox(const QString& text, bool checked, QWidget* parent)
    : QCheckBox(text, parent)
    {
        QCheckBox::setFont(FontHelper()
                .setPixelSize(FConstants::FCheckbox::DefaultFontSize)
                .getFont());

        _qsshelper.setProperty("QCheckBox", "spacing", QString::number(FConstants::FCheckbox::Spacing) + "px");
        _qsshelper.setProperty("QCheckBox", "color", FColor::regularText());
        _qsshelper.setProperty("QCheckBox:checked", "color", FColor::primary());
        _qsshelper.setProperty("QCheckBox:disabled", "color", FColor::placeholderText());
        _qsshelper.setProperty("QCheckBox:disabled:checked", "color", FColor::placeholderText());
        _qsshelper.setProperty("QCheckBox::indicator", "border", "1px solid " + FColor::baseBorder());
        _qsshelper.setProperty("QCheckBox::indicator", "border-radius", QString::number(FConstants::FCheckbox::IndicatorBorderRadius) + "px");
        _qsshelper.setProperty("QCheckBox::indicator", "background-color", "white");
        _qsshelper.setProperty("QCheckBox::indicator:hover", "border-color", FColor::primary());
        _qsshelper.setProperty("QCheckBox::indicator:checked", "border-color", FColor::primary());
        _qsshelper.setProperty("QCheckBox::indicator:checked", "background-color", FColor::primary());
        _qsshelper.setProperty("QCheckBox::indicator:indeterminate", "border-color", FColor::primary());
        _qsshelper.setProperty("QCheckBox::indicator:indeterminate", "background-color", FColor::primary());
        _qsshelper.setProperty("QCheckBox::indicator:disabled", "background-color", FColor::lightFill());
        _qsshelper.setProperty("QCheckBox::indicator:disabled:checked", "background-color", FColor::lightFill());
        _qsshelper.setProperty("QCheckBox::indicator:disabled:checked", "border-color", FColor::baseBorder());
        _qsshelper.setProperty("QCheckBox::indicator:disabled:indeterminate", "background-color", FColor::lightFill());
        _qsshelper.setProperty("QCheckBox::indicator:disabled:indeterminate", "border-color", FColor::baseBorder());
        setStyleSheet(_qsshelper.generate());

        setSize(_size);
        setChecked(checked);
        setCursor(Qt::PointingHandCursor);
    }

FCheckbox& FCheckbox::setValue(const QVariant& value)
{
    _value = value;
    return *this;
}

QVariant FCheckbox::getValue()
{
    return _value;
}

FCheckbox& FCheckbox::setText(const QString& text)
{
    QCheckBox::setText(text);
    return *this;
}

QString FCheckbox::getText()
{
    return QCheckBox::text();
}

FCheckbox& FCheckbox::setDisabled(bool disabled)
{
    QCheckBox::setEnabled(!disabled);
    return *this;
}

bool FCheckbox::isDisabled()
{
    return !QCheckBox::isEnabled();
}

FCheckbox& FCheckbox::setSize(Size size)
{
    _size = size;

    QCheckBox::setFont(FontHelper()
            .setFont(QCheckBox::font())
            .setPixelSize(size == Size::Small ? FConstants::FCheckbox::SmallFontSize : FConstants::FCheckbox::DefaultFontSize)
            .getFont());

    if (size == Size::Small)
    {
        _qsshelper.setProperty("QCheckBox::indicator", "width", QString::number(FConstants::FCheckbox::SmallIndicatorSize) + "px");
        _qsshelper.setProperty("QCheckBox::indicator", "height", QString::number(FConstants::FCheckbox::SmallIndicatorSize) + "px");
    }
    else
    {
        _qsshelper.setProperty("QCheckBox::indicator", "width", QString::number(FConstants::FCheckbox::DefaultIndicatorSize) + "px");
        _qsshelper.setProperty("QCheckBox::indicator", "height", QString::number(FConstants::FCheckbox::DefaultIndicatorSize) + "px");
    }
    setStyleSheet(_qsshelper.generate());

    int height = size == Size::Large ? FConstants::FCheckbox::LargeHeight 
                : size == Size::Default ? FConstants::FCheckbox::DefaultHeight 
                : FConstants::FCheckbox::SmallHeight;
    setFixedHeight(height);
    adjustSize();
    return *this;
}

FCheckbox::Size FCheckbox::getSize()
{
    return _size;
}

FCheckbox& FCheckbox::setChecked(bool checked)
{
    QCheckBox::setChecked(checked);
    return *this;
}

bool FCheckbox::getChecked()
{
    return QCheckBox::isChecked();
}

FCheckbox& FCheckbox::setBorder(bool border)
{
    _border = border;

    if (border)
    {
        if (_size == Size::Large)
            _qsshelper.setProperty("QCheckBox", "padding", 
                QString("0px %1px 0px %2px").arg(FConstants::FCheckbox::LargeBorderPaddingRight).arg(FConstants::FCheckbox::LargeBorderPaddingLeft));
        else if (_size == Size::Default)
            _qsshelper.setProperty("QCheckBox", "padding", 
                QString("0px %1px 0px %2px").arg(FConstants::FCheckbox::DefaultBorderPaddingRight).arg(FConstants::FCheckbox::DefaultBorderPaddingLeft));
        else
            _qsshelper.setProperty("QCheckBox", "padding", 
                QString("0px %1px 0px %2px").arg(FConstants::FCheckbox::SmallBorderPaddingRight).arg(FConstants::FCheckbox::SmallBorderPaddingLeft));

        _qsshelper.setProperty("QCheckBox", "border-radius", QString::number(FConstants::FCheckbox::BorderRadius) + "px");
        _qsshelper.setProperty("QCheckBox", "border", "1px solid " + FColor::baseBorder());
        _qsshelper.setProperty("QCheckBox:checked", "border-color", FColor::primary());
    }
    else
    {
        _qsshelper.setProperty("QCheckBox", "padding", "0px");
        _qsshelper.setProperty("QCheckBox", "border", "none");
    }

    setStyleSheet(_qsshelper.generate());
    adjustSize();
    return *this;
}

bool FCheckbox::getBorder()
{
    return _border;
}

FCheckbox& FCheckbox::setIndeterminate(bool indeterminate)
{
    QCheckBox::setCheckState(indeterminate ?
            Qt::CheckState::PartiallyChecked : Qt::CheckState::Unchecked);
    return *this;
}

bool FCheckbox::getIndeterminate()
{
    return QCheckBox::checkState() == Qt::CheckState::PartiallyChecked;
}

void FCheckbox::paintEvent(QPaintEvent* event)
{
    QCheckBox::paintEvent(event);

    // 如果选中或不确定，绘制标记（因为设置了背景色，默认标记可能不显示）
    if (checkState() == Qt::Checked || checkState() == Qt::PartiallyChecked)
    {
        QStyleOptionButton option;
        initStyleOption(&option);
        QRect indicatorRect = style()->subElementRect(QStyle::SE_CheckBoxIndicator, &option, this);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        if (checkState() == Qt::Checked)
        {
            // 绘制对勾
            painter.setPen(QPen(QColor(FColor::blankFill()), FConstants::FCheckbox::MarkLineWidth));
            int x = indicatorRect.x() + indicatorRect.width() / 2;
            int y = indicatorRect.y() + indicatorRect.height() / 2;
            int w = static_cast<int>(indicatorRect.width() * FConstants::FCheckbox::CheckmarkWidthRatio);
            int h = static_cast<int>(indicatorRect.height() * FConstants::FCheckbox::CheckmarkHeightRatio);
            painter.drawLine(x - w/2, y, x, y + h);
            painter.drawLine(x, y + h, x + w, y - h);
        }
        else if (checkState() == Qt::PartiallyChecked)
        {
            // 绘制横线（不确定状态）
            int x = indicatorRect.x() + static_cast<int>(indicatorRect.width() * FConstants::FCheckbox::IndeterminateStartRatio);
            int y = indicatorRect.y() + indicatorRect.height() / 2;
            int w = static_cast<int>(indicatorRect.width() * FConstants::FCheckbox::IndeterminateWidthRatio);
            painter.setPen(QPen(QColor(isEnabled() ? FColor::blankFill() : FColor::placeholderText()), FConstants::FCheckbox::MarkLineWidth));
            painter.drawLine(x, y, x + w, y);
        }
    }
}

void FCheckbox::enterEvent(QEvent* event)
{
    if (!isEnabled())
        QApplication::setOverrideCursor(Qt::ForbiddenCursor);
    QCheckBox::enterEvent(event);
}

void FCheckbox::leaveEvent(QEvent* event)
{
    if (!isEnabled())
        QApplication::restoreOverrideCursor();
    QCheckBox::leaveEvent(event);
}


FCheckboxGroup::FCheckboxGroup(QWidget* parent)
    : FCheckboxGroup({}, parent)
{}

FCheckboxGroup::FCheckboxGroup(const QList<FCheckbox*>& checkboxs, QWidget* parent)
    : QGroupBox(parent)
    , _checkboxs(checkboxs)
    , _layout(new QHBoxLayout(this))
{
    setTitle("");

    _layout->setContentsMargins(FConstants::FCheckbox::GroupMarginLeft, FConstants::FCheckbox::GroupMarginTop, 
                                 FConstants::FCheckbox::GroupMarginRight, FConstants::FCheckbox::GroupMarginBottom);
    _layout->setSpacing(FConstants::FCheckbox::GroupSpacing);

    for (auto* checkbox : checkboxs)
        addCheckbox(checkbox);

    setStyleSheet("QGroupBox { border: none; }");
}

FCheckboxGroup& FCheckboxGroup::addCheckbox(FCheckbox* checkbox)
{
    _checkboxs.append(checkbox);
    connect(checkbox, &QCheckBox::stateChanged, this, &FCheckboxGroup::onStateChanged);

    _layout->addWidget(checkbox);
    adjustSize();
    return *this;
}

FCheckboxGroup& FCheckboxGroup::setTitle(const QString&)
{
    QGroupBox::setTitle("");
    return *this;
}

FCheckboxGroup& FCheckboxGroup::setSize(Size size)
{
    _size = size;

    for (auto* checkbox : _checkboxs)
        checkbox->setSize(static_cast<FCheckbox::Size>(_size));

    adjustSize();
    return *this;
}

FCheckboxGroup::Size FCheckboxGroup::getSize()
{
    return _size;
}

FCheckboxGroup& FCheckboxGroup::setDisabled(bool disabled)
{
    QGroupBox::setEnabled(!disabled);
    return *this;
}

bool FCheckboxGroup::isDisabled()
{
    return !QGroupBox::isEnabled();
}

FCheckboxGroup& FCheckboxGroup::setMin(int min)
{
    _min = qMax(0, min);
    onStateChanged();
    return *this;
}

int FCheckboxGroup::getMin()
{
    return _min;
}

FCheckboxGroup& FCheckboxGroup::setMax(int max)
{
    _max = qMax(0, max);
    onStateChanged();
    return *this;
}

int FCheckboxGroup::getMax()
{
    return _max;
}

void FCheckboxGroup::onStateChanged()
{
    if (_min == 0 && _max == 0)
        return;

    int checkedCount = countChecked();

    if (_max > 0 && checkedCount == _max)
    {
        for (auto* checkbox : _checkboxs)
            checkbox->setDisabled(!checkbox->isChecked());
    }

    if (_min > 0 && checkedCount == _min)
    {
        for (auto* checkbox : _checkboxs)
            checkbox->setDisabled(checkbox->isChecked());
    }
}

int FCheckboxGroup::countChecked()
{
    int cnt = 0;
    for (auto* checkbox : _checkboxs)
    {
        if (checkbox->isChecked())
            cnt++;
    }
    return cnt;
}

