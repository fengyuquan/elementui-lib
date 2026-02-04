#include "text.h"
#include "color.h"
#include "private/utils.h"

#include <QFont>

FText::FText(QWidget* parent)
    : FText("", Type::Default, parent)
{}

FText::FText(const QString& text, QWidget* parent)
    : FText(text, Type::Default, parent)
{}

FText::FText(const QString& text, FText::Type type, QWidget* parent)
    : QLabel(text, parent)
    , _type(type)
{
    setFont(FontHelper()
            .setPointSize(Comm::defaultFontSize)
            .getFont());

    QLabel::setWordWrap(true);
    QLabel::adjustSize();

    setType(_type);
    setSize(_size);
}

FText::Type FText::getType()
{
    return _type;
}

FText& FText::setType(Type type)
{
    _type = type;

    if (type == Type::Default)
        setColor(FColor::regularText());
    else if (type == Type::Primary)
        setColor(FColor::primary());
    else if (type == Type::Success)
        setColor(FColor::success());
    else if (type == Type::Info)
        setColor(FColor::info());
    else if (type == Type::Warning)
        setColor(FColor::warning());
    else if (type == Type::Danger)
        setColor(FColor::danger());

    // setSize(_size);

    return *this;
}

FText::Size FText::getSize()
{
    return _size;
}

FText& FText::setSize(Size size)
{
    _size = size;
    if (size == Size::Default)
        setFontSize(Comm::defaultFontSize);
    else if (size == Size::Large)
        setFontSize(Comm::largeFontSize);
    else if (size == Size::Small)
        setFontSize(Comm::smallFontSize);

    QLabel::adjustSize();
    return *this;
}

FText::Tag FText::getTag()
{
    return _tag;
}

FText& FText::setTag(Tag tag)
{
    _tag = tag;
    QFont font = QLabel::font();

    if (tag == Tag::Paragraph)
    {
        QLabel::setWordWrap(true);
        QLabel::setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
    else if (tag == Tag::Bold)
         font.setBold(true);
    else if (tag == Tag::Italic)
        font.setItalic(true);
    else if (tag == Tag::Subscript)
        setSubscript();
    else if (tag == Tag::Superscript)
        setSupscript();
    else if (tag == Tag::Inserted)
        font.setUnderline(true);
    else if (tag == Tag::Deleted)
        font.setStrikeOut(true);
    else if (tag == Tag::Marked)
        setFontColor(Qt::yellow);

    QLabel::setFont(font);
    return *this;
}

bool FText::getTruncated()
{
    return _truncated;
}

FText& FText::setTruncated(bool truncated)
{
    _truncated = truncated;
    return *this;
}

FText& FText::setColor(const QString& color)
{
    QPalette palette = QLabel::palette();
    palette.setColor(QPalette::WindowText, color);
    palette.setColor(QPalette::Window, FColor::baseBackground());
    QLabel::setAutoFillBackground(true);
    QLabel::setPalette(palette);
    return *this;
}

void FText::setFontColor(int color)
{
    QPalette palette = QLabel::palette();
    palette.setColor(QPalette::WindowText, color);
    palette.setColor(QPalette::Window, FColor::baseBackground());
    QLabel::setAutoFillBackground(true);
    QLabel::setPalette(palette);
}

FText& FText::setFontSize(int size)
{
    QFont font = QLabel::font();
    font.setPointSize(size);
    QLabel::setFont(font);
    QLabel::adjustSize();
    return *this;
}

void FText::setSubscript()
{
    QLabel::setTextFormat(Qt::RichText);
    QLabel::setText("<sub>" + QLabel::text() + "</sub>");
}

void FText::setSupscript()
{
    QLabel::setTextFormat(Qt::RichText);
    QLabel::setText("<sup>" + QLabel::text() + "</sup>");
}

void FText::enterEvent(QEvent* event)
{
    QLabel::enterEvent(event);
    emit hovered(true);
}

void FText::leaveEvent(QEvent* event)
{
    QLabel::leaveEvent(event);
    emit hovered(false);
}

void FText::mousePressEvent(QMouseEvent* event)
{
    QLabel::mousePressEvent(event);
}

void FText::mouseReleaseEvent(QMouseEvent* event)
{
    QLabel::mouseReleaseEvent(event);

    if (rect().contains(event->pos()))
    {
        if (event->button() == Qt::LeftButton)
            emit clicked();
        else if (event->button() == Qt::RightButton)
            emit rightClicked();
    }
}

