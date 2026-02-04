#include "backtop.h"
#include "icon.h"
#include "color.h"
#include "shadow.h"
#include "private/utils.h"
#include "constants.h"

#include <QPainter>
#include <QMouseEvent>
#include <QScrollBar>
#include <QPainterPath>

FBacktop::FBacktop(QWidget* parent)
    : FBacktop(nullptr, parent)
{}

FBacktop::FBacktop(QScrollArea* target, QWidget* parent)
    : QLabel(parent)
    , _target(target)
    , _visibilityHeight(FConstants::FBacktop::DefaultVisibilityHeight)
    , _right(FConstants::FBacktop::DefaultRight)
    , _bottom(FConstants::FBacktop::DefaultBottom)
    , _svgRenderer(FIcon::instance().getRenderer(FIcon::CaretTop, FColor::primaryText(), this))
{
    setVisible(false);
    setCursor(Qt::PointingHandCursor);
    setFont(FontHelper().getFont());

    if (_target)
        connect(_target->verticalScrollBar(), &QScrollBar::valueChanged,
                this, &FBacktop::onScrollBarValueChanged);

    setShape(_shape);
    setSize(_size);
    setType(_type);

    FShadowEf::setShadow(this, FShadowEf::Type::Lighter);
}

FBacktop& FBacktop::setShape(Shape shape)
{
    _shape = shape;
    return *this;
}

FBacktop& FBacktop::setSize(Size size)
{
    _size = size;
    if (_size == Size::Default) setFixedSize(FConstants::FBacktop::DefaultSize, FConstants::FBacktop::DefaultSize);
    else if (_size == Size::Large) setFixedSize(FConstants::FBacktop::LargeSize, FConstants::FBacktop::LargeSize);
    else if (_size == Size::Small) setFixedSize(FConstants::FBacktop::SmallSize, FConstants::FBacktop::SmallSize);
    return *this;
}

FBacktop& FBacktop::setType(Type type)
{
    _type = type;
    return *this;
}

FBacktop& FBacktop::setTarget(QScrollArea* target)
{
    if (_target)
        disconnect(_target->verticalScrollBar(), &QScrollBar::valueChanged, this, &FBacktop::onScrollBarValueChanged);

    _target = target;

    if (_target)
        connect(_target->verticalScrollBar(), &QScrollBar::valueChanged, this, &FBacktop::onScrollBarValueChanged);

    return *this;
}

FBacktop& FBacktop::setVisibilityHeight(int visibilityHeight)
{
    _visibilityHeight = visibilityHeight;
    return *this;
}

FBacktop& FBacktop::setRight(int right)
{
    _right = right;
    return *this;
}

FBacktop& FBacktop::setBottom(int bottom)
{
    _bottom = bottom;
    return *this;
}

void FBacktop::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int size = qMin(width(), height());
    int x = (width() - size) / 2;
    int y = (height() - size) / 2;

    QPainterPath clipPath;
    if (_shape == Shape::Circle)      clipPath.addEllipse(x, y, size, size);
    else if (_shape == Shape::Square) clipPath.addRoundedRect(x, y, size, size, FConstants::FBacktop::SquareBorderRadius, FConstants::FBacktop::SquareBorderRadius);
    painter.setClipPath(clipPath);

    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    if (_shape == Shape::Circle)      painter.drawEllipse(x, y, size, size);
    else if (_shape == Shape::Square) painter.drawRoundedRect(x, y, size, size, FConstants::FBacktop::SquareBorderRadius, FConstants::FBacktop::SquareBorderRadius);

    if (_type == Type::Icon && _svgRenderer && _svgRenderer->isValid())
    {
        if (_size == Size::Default)    _svgRenderer->render(&painter, QRectF(FConstants::FBacktop::DefaultIconX, FConstants::FBacktop::DefaultIconY, FConstants::FBacktop::DefaultIconSize, FConstants::FBacktop::DefaultIconSize));
        else if (_size == Size::Large) _svgRenderer->render(&painter, QRectF(FConstants::FBacktop::LargeIconX, FConstants::FBacktop::LargeIconY, FConstants::FBacktop::LargeIconSize, FConstants::FBacktop::LargeIconSize));
        else if (_size == Size::Small) _svgRenderer->render(&painter, QRectF(FConstants::FBacktop::SmallIconX, FConstants::FBacktop::SmallIconY, FConstants::FBacktop::SmallIconSize, FConstants::FBacktop::SmallIconSize));
    }
    else
    {
        QFont font = QLabel::font();
        font.setBold(true);
        font.setPointSize(_size == Size::Default || _size == Size::Large
                          ? FConstants::FBacktop::LargeTextFontSize : Comm::defaultFontSize);

        painter.setPen(FColor::primary());
        painter.setFont(font);

        QRectF textRect(x, y, size, size);
        painter.drawText(textRect, Qt::AlignCenter, "UP");
    }
}

void FBacktop::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && _target)
        _target->verticalScrollBar()->setValue(0);

    QLabel::mousePressEvent(event);
}

void FBacktop::onScrollBarValueChanged(int value)
{
    setVisible(value > _visibilityHeight);
}


