#include "avatar.h"
#include "color.h"
#include "private/utils.h"
#include "constants.h"

#include <QPainter>
#include <QPainterPath>

FAvatar::FAvatar(QWidget* parent) : QLabel(parent)
{
    setSize(_size);
}

FAvatar::FAvatar(FIcon::Name icon, QWidget* parent) : FAvatar(parent)
{
    setIcon(icon);
}
FAvatar::FAvatar(const QImage& image, QWidget* parent) : FAvatar(parent)
{
    setImage(image);
}
FAvatar::FAvatar(const QString& text, QWidget* parent) : FAvatar(parent)
{
    setText(text);
}

FAvatar::FAvatar(FIcon::Name icon, Shape shape, Size size, QWidget* parent) : FAvatar(parent)
{
    setIcon(icon);
    _shape = shape, _size = size;
}
FAvatar::FAvatar(const QImage& image, Shape shape, Size size, QWidget* parent) : FAvatar(parent)
{
    setImage(image);
    _shape = shape, _size = size;
}
FAvatar::FAvatar(const QString& text, Shape shape, Size size, QWidget* parent) : FAvatar(parent)
{
    setText(text);
    _shape = shape, _size = size;
}

FAvatar& FAvatar::setIcon(FIcon::Name icon)
{
    _type = Type::Icon;
    if (_svgRenderer)
        _svgRenderer->deleteLater();
    _svgRenderer = FIcon::instance().getRenderer(icon, FColor::basicWhite(), this);
    return *this;
}

FAvatar& FAvatar::setImage(const QImage& image)
{
    _type = Type::Image;

    if (image.isNull())
        _image.load(":/icons/other/avatar-load-failed.png");
    else
        _image = image;

    return *this;
}

FAvatar& FAvatar::setText(const QString& text)
{
    _type = Type::Text;
    _text = text;
    return *this;
}

FAvatar& FAvatar::setSize(Size size)
{
    _size = size;
    setFixedSize(calcSize(), calcSize());
    return *this;
}

FAvatar& FAvatar::setShape(Shape shape)
{
    _shape = shape;
    return *this;
}

void FAvatar::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int size = qMin(width(), height());
    int x = (width() - size) / 2;
    int y = (height() - size) / 2;

    QPainterPath clipPath;
    if (_shape == Shape::Circle)      clipPath.addEllipse(x, y, size, size);
    else if (_shape == Shape::Square) clipPath.addRoundedRect(x, y, size, size, FConstants::FAvatar::SquareBorderRadius, FConstants::FAvatar::SquareBorderRadius);
    painter.setClipPath(clipPath);

    painter.setBrush(QColor(FColor::disabledText()));
    painter.setPen(Qt::NoPen);
    if (_shape == Shape::Circle)      painter.drawEllipse(x, y, size, size);
    else if (_shape == Shape::Square) painter.drawRoundedRect(x, y, size, size, FConstants::FAvatar::SquareBorderRadius, FConstants::FAvatar::SquareBorderRadius);

    if (_type == Type::Icon && _svgRenderer && _svgRenderer->isValid())
    {
        if (_size == Size::Default)    _svgRenderer->render(&painter, QRectF(FConstants::FAvatar::DefaultIconX, FConstants::FAvatar::DefaultIconY, FConstants::FAvatar::DefaultIconSize, FConstants::FAvatar::DefaultIconSize));
        else if (_size == Size::Large) _svgRenderer->render(&painter, QRectF(FConstants::FAvatar::LargeIconX, FConstants::FAvatar::LargeIconY, FConstants::FAvatar::LargeIconSize, FConstants::FAvatar::LargeIconSize));
        else if (_size == Size::Small) _svgRenderer->render(&painter, QRectF(FConstants::FAvatar::SmallIconX, FConstants::FAvatar::SmallIconY, FConstants::FAvatar::SmallIconSize, FConstants::FAvatar::SmallIconSize));
    }
    else if (_type == Type::Text)
    {
        QFont font = FontHelper()
            .setPointSize(_size == Size::Small ? Comm::smallFontSize : Comm::defaultFontSize)
            .setBold()
            .getFont();
        painter.setPen(Qt::white);
        painter.setFont(font);

        QRectF textRect(x, y, size, size);
        painter.drawText(textRect, Qt::AlignCenter, _text);
    }
    else if (_type == Type::Image && !_image.isNull())
    {
        QRectF imageRect(0, 0, calcSize(), calcSize());
        QImage scaledImage = _image.scaled(imageRect.size().toSize(),
                                          Qt::KeepAspectRatio,
                                          Qt::SmoothTransformation);
        painter.drawImage(imageRect, scaledImage);
    }
}

int FAvatar::calcSize()
{
    if (_size == Size::Default) return FConstants::FAvatar::DefaultSize;
    else if (_size == Size::Small) return FConstants::FAvatar::SmallSize;
    else if (_size == Size::Large) return FConstants::FAvatar::LargeSize;
    else return 0;
}


