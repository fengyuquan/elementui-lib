#include "badge.h"
#include "private/utils.h"
#include "constants.h"

FBadge::FBadge(QWidget* partner)
    : QLabel(partner->parentWidget())
    , _partner(partner)
    , _numValue(0)
    , _max(0)
    , _isDot(false)
{
    setFixedHeight(FConstants::FBadge::Height);
    setMinimumWidth(FConstants::FBadge::Height), setMaximumWidth(FConstants::FBadge::MaxWidth);

    setAttribute(Qt::WA_TransparentForMouseEvents); // 允许鼠标事件穿透到父控件
    setAlignment(Qt::AlignCenter);

    setFont(FontHelper()
            .setPointSize(Comm::smallFontSize)
            .setBold()
            .getFont());

    _qsshelper.setProperty("QLabel", "color", "white")
            .setProperty("QLabel", "border", "none")
            .setProperty("QLabel", "border-radius", QString::number(FConstants::FBadge::BorderRadius) + "px")
            .setProperty("QLabel", "padding", QString::number(FConstants::FBadge::PaddingTop) + "px " + QString::number(FConstants::FBadge::PaddingHorizontal) + "px " + QString::number(FConstants::FBadge::PaddingBottom) + "px " + QString::number(FConstants::FBadge::PaddingHorizontal) + "px")
            .setProperty("QLabel", "background-color", getColor());
    setStyleSheet(_qsshelper.generate());

    hide();
}

FBadge::FBadge(bool isDot, QWidget* partner) : FBadge(partner)
{
    setIsDot(isDot);
}

FBadge::FBadge(int value, QWidget* partner) : FBadge(partner)
{
    setValue(value);
}

FBadge::FBadge(int value, int max, QWidget* partner) : FBadge(partner)
{
    setValue(value);
    setMax(max);
}

FBadge::FBadge(const QString& value, QWidget* partner) : FBadge(partner)
{
    setValue(value);
}

FBadge& FBadge::setType(Type type)
{
    _type = type;
    _qsshelper.setProperty("QLabel", "background-color", getColor());
    setStyleSheet(_qsshelper.generate());
    return *this;
}

FBadge& FBadge::setIsDot(bool isdot)
{
    _isDot = isdot;
    return *this;
}

FBadge& FBadge::setValue(int value)
{
    _numValue = value;

    if (value == 0)
    {
        hide();
    }
    else if (!isVisible())
    {
        if (_max != 0 && value > _max)
            setValue(QString::number(_max) + "+");
        else
            setValue(QString::number(_numValue));
        show();
    }
    return *this;
}

FBadge& FBadge::setValue(const QString& value)
{
    _strValue = value;

    if (value.isEmpty())
    {
        hide();
    }
    else if (!isVisible())
    {
        setText(_strValue);
        adjustSize();
        show();
    }
    return *this;
}

FBadge& FBadge::setMax(int max)
{
     _max = max;
     return *this;
}

void FBadge::resizeEvent(QResizeEvent* event)
{
    QLabel::resizeEvent(event);
    updatePosition();
}

void FBadge::updatePosition()
{
    if (!_partner)
        return;

    QRect partnerGeo = _partner->geometry();

    move(partnerGeo.x() + partnerGeo.width() - width() / 2,
         partnerGeo.y() - height() / 2);
}

QString FBadge::getColor()
{
    if (_type == Type::Primary) return FColor::primary();
    else if (_type == Type::Success) return FColor::success();
    else if (_type == Type::Info) return FColor::info();
    else if (_type == Type::Warning) return FColor::warning();
    else if (_type == Type::Danger) return FColor::danger();
    else return "";
}

