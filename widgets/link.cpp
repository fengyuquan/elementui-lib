#include "link.h"
#include "color.h"
#include "private/utils.h"

#include <QApplication>

FLink::FLink(QWidget* parent)
    : QLabel(parent)
    , _type(Type::Default)
    , _underline(Underline::Default)
{
    QLabel::setFont(FontHelper()
            .setPointSize(Comm::defaultFontSize)
            .setBold(true)
            .getFont());

    setType(_type);
    setUnderline(_underline);
}

FLink::FLink(const QString& text, QWidget* parent)
    : FLink(parent)
{
    QLabel::setText(text);
    QLabel::adjustSize();
}

FLink::Type FLink::getType()
{
    return _type;
}

FLink& FLink::setType(Type type)
{
    _type = type;

    if (type == Type::Default)
    {
        _qsshelper.setProperty("QLabel", "color", FColor::regularText());
        _qsshelper.setProperty("QLabel:hover", "color", FColor::primary());
        _qsshelper.setProperty("QLabel:disabled", "color", FColor::placeholderText());
    }
    else if (type == Type::Primary)
    {
        _qsshelper.setProperty("QLabel", "color", FColor::primary());
        _qsshelper.setProperty("QLabel:hover", "color", FColor::primaryL1());
        _qsshelper.setProperty("QLabel:disabled", "color", FColor::primaryL2());
    }
    else if (type == Type::Success)
    {
        _qsshelper.setProperty("QLabel", "color", FColor::success());
        _qsshelper.setProperty("QLabel:hover", "color", FColor::successL1());
        _qsshelper.setProperty("QLabel:disabled", "color", FColor::successL2());
    }
    else if (type == Type::info)
    {
        _qsshelper.setProperty("QLabel", "color", FColor::info());
        _qsshelper.setProperty("QLabel:hover", "color", FColor::infoL1());
        _qsshelper.setProperty("QLabel:disabled", "color", FColor::infoL2());
    }
    else if (type == Type::warning)
    {
        _qsshelper.setProperty("QLabel", "color", FColor::warning());
        _qsshelper.setProperty("QLabel:hover", "color", FColor::warningL1());
        _qsshelper.setProperty("QLabel:disabled", "color", FColor::warningL2());
    }
    else if (type == Type::Danger)
    {
        _qsshelper.setProperty("QLabel", "color", FColor::danger());
        _qsshelper.setProperty("QLabel:hover", "color", FColor::dangerL1());
        _qsshelper.setProperty("QLabel:disabled", "color", FColor::dangerL2());
    }

    QLabel::setStyleSheet(_qsshelper.generate());
    return *this;
}

FLink::Underline FLink::getUnderline()
{
    return _underline;
}

FLink& FLink::setUnderline(Underline underline)
{
    _underline = underline;

    if (underline == Underline::Always)
        _qsshelper.setProperty("QLabel", "text-decoration", "underline");
    else if (underline == Underline::Never)
        _qsshelper.setProperty("QLabel", "text-decoration", "none");

    QLabel::setStyleSheet(_qsshelper.generate());
    return *this;
}

bool FLink::isDisabled()
{
    return !QLabel::isEnabled();
}

FLink& FLink::setDisabled(bool disabled)
{
    QLabel::setDisabled(disabled);
    return *this;
}

FLink& FLink::setText(const QString& text)
{
    QLabel::setText(text);
    adjustSize();
    return *this;
}

void FLink::enterEvent(QEvent *event)
{
    if (!isEnabled())
        QApplication::setOverrideCursor(Qt::ForbiddenCursor);
    else if (_underline != Underline::Never)
        setText("<u>" + text() + "</u>");

    QLabel::enterEvent(event);
}

void FLink::leaveEvent(QEvent *event)
{
    QApplication::restoreOverrideCursor();
    if (_underline != Underline::Always)
        setText(text().remove("<u>").remove("</u>"));

    QLabel::leaveEvent(event);
}

