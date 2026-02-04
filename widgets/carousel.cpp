#include "carousel.h"
#include "icon.h"
#include "color.h"
#include "private/utils.h"
#include "constants.h"

#include <QPainter>
#include <QMouseEvent>

FCarousel::FCarousel(QWidget *parent)
    : FCarousel({}, parent)
{}

FCarousel::FCarousel(const QList<QPixmap>& images, QWidget* parent)
    : QWidget(parent)
    , _leftArrowRenderer(FIcon::instance().getRenderer(FIcon::ArrowLeft, FColor::blankFill(), this))
    , _rightArrowRenderer(FIcon::instance().getRenderer(FIcon::ArrowRight, FColor::blankFill(), this))
{
    foreach (auto& image, images)
        addImage(image);

    setMouseTracking(true);
}

FCarousel& FCarousel::setTigger(Trigger trigger)
{
    _trigger = trigger;
    return *this;
}

FCarousel& FCarousel::setIndicatorPos(IndicatorPos pos)
{
    _indicatorPos = pos;
    return *this;
}

FCarousel& FCarousel::setArrow(Arrow arrow)
{
    _arrow = arrow;
    return *this;
}

FCarousel& FCarousel::setAutoplay(bool autoplay)
{
    _autoplay = autoplay;
    return *this;
}

FCarousel& FCarousel::setInterval(int interval)
{
    _interval = interval;
    return *this;
}

FCarousel& FCarousel::setType(Type type)
{
    _type = type;
    return *this;
}

FCarousel& FCarousel::setCardScale(double scale)
{
    _cardScale = scale;
    return *this;
}

FCarousel& FCarousel::setLoop(bool loop)
{
    _loop = loop;
    return *this;
}

FCarousel& FCarousel::setDirection(Direction direction)
{
    _direction = direction;
    return *this;
}

FCarousel& FCarousel::setPauseOnHover(bool pauseOnHover)
{
    _pauseOnHover = pauseOnHover;
    return *this;
}

FCarousel& FCarousel::addImage(const QPixmap& image)
{
    _images.append(image);
    return *this;
}

void FCarousel::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    if (!_images.isEmpty())
    {
        const QPixmap& pixmap = _images.at(_index);

        QRect drawRect = rect();

        if (_type == Type::Default)
        {
            painter.drawPixmap(drawRect, pixmap);
        }
        else if (_type == Type::Card)
        {
            QSize scaledSize = pixmap.size();
            scaledSize.scale(drawRect.size() * _cardScale, Qt::KeepAspectRatio);

            QRect targetRect(QPoint(0, 0), scaledSize);
            targetRect.moveCenter(drawRect.center());

            painter.drawPixmap(targetRect, pixmap);
        }
    }

    if ((_arrow == Arrow::Always) || (_arrow == Arrow::Hover && underMouse()))
    {
        QColor bg = _leftArrowHovered ? QColor(31, 45, 61, int(0.23 * 255)) : QColor(31, 45, 61, int(0.11 * 255));
        painter.setBrush(bg);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(_leftArrowRect);

        if (_leftArrowRenderer && _leftArrowRenderer->isValid())
        {
            QRect iconRect(0, 0, sc(FConstants::FCarousel::ArrowIconSize), sc(FConstants::FCarousel::ArrowIconSize));
            iconRect.moveCenter(_leftArrowRect.center());
            _leftArrowRenderer->render(&painter, iconRect);
        }

        QColor bgRight = _rightArrowHovered ? QColor(31, 45, 61, int(0.23 * 255)) : QColor(31, 45, 61, int(0.11 * 255));
        painter.setBrush(bgRight);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(_rightArrowRect);

        if (_rightArrowRenderer && _rightArrowRenderer->isValid())
        {
            QRect iconRect(0, 0, sc(FConstants::FCarousel::ArrowIconSize), sc(FConstants::FCarousel::ArrowIconSize));
            iconRect.moveCenter(_rightArrowRect.center());
            _rightArrowRenderer->render(&painter, iconRect);
        }
    }

    if (_indicatorPos != IndicatorPos::None && !_images.isEmpty() && !_indicatorRects.isEmpty())
    {
        for (int i = 0; i < _indicatorRects.size(); ++i)
        {
            painter.setBrush(QColor(255, 255, 255, i == _index ? 255 : int(0.48 * 255)));
            painter.setPen(Qt::NoPen);

            const QRect& rect = _indicatorRects[i];
            painter.drawRect(rect);
        }
    }

}

void FCarousel::enterEvent(QEvent* event)
{
    if (_arrow != Arrow::Never)
        update();
    QWidget::enterEvent(event);
}

void FCarousel::leaveEvent(QEvent* event)
{
    if (_arrow != Arrow::Never)
        update();
    QWidget::leaveEvent(event);
}

void FCarousel::mouseMoveEvent(QMouseEvent* event)
{
    // check arrows hover
    bool leftChanged = _leftArrowHovered != _leftArrowRect.contains(event->pos());
    bool rightChanged = _rightArrowHovered != _rightArrowRect.contains(event->pos());

    _leftArrowHovered = _leftArrowRect.contains(event->pos());
    _rightArrowHovered = _rightArrowRect.contains(event->pos());


    // check indicators hover
    int hoveredIndicator = -1;
    if (_indicatorPos != IndicatorPos::None && !_indicatorRects.isEmpty())
    {
        for (int i = 0; i < _indicatorRects.size(); ++i)
        {
            if (_indicatorRects[i].contains(event->pos()))
            {
                hoveredIndicator = i;
                break;
            }
        }
    }

    bool indicatorHovered = (hoveredIndicator != -1);
    bool indicatorChanged = _hoveredIndicatorIndex != hoveredIndicator;
    _hoveredIndicatorIndex = hoveredIndicator;

    if (_leftArrowHovered || _rightArrowHovered || indicatorHovered)
        setCursor(Qt::PointingHandCursor);
    else
        unsetCursor();

    if (leftChanged || rightChanged || indicatorChanged)
        update();

    QWidget::mouseMoveEvent(event);
}

void FCarousel::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (_leftArrowRect.contains(event->pos()))
        {
            showPrevious();
            return;
        }
        else if (_rightArrowRect.contains(event->pos()))
        {
            showNext();
            return;
        }

        if (_indicatorPos != IndicatorPos::None && !_indicatorRects.isEmpty())
        {
            for (int i = 0; i < _indicatorRects.size(); ++i)
            {
                if (_indicatorRects[i].contains(event->pos()))
                {
                    if (_index != i)
                    {
                        _index = i;
                        update();
                    }
                    return;
                }
            }
        }
    }

    QWidget::mousePressEvent(event);
}

void FCarousel::showEvent(QShowEvent* event)
{
    static bool first = true;
    if (first)
    {
        calcArrowPos();
        calcIndicatorPos();
        first = false;
    }

    QWidget::showEvent(event);
}

void FCarousel::showPrevious()
{
    if (_images.isEmpty()) return;

    if (_index > 0)
        --_index;
    else if (_loop)
        _index = _images.size() - 1;

    update();
}

void FCarousel::showNext()
{
    if (_images.isEmpty()) return;

    if (_index < _images.size() - 1)
        ++_index;
    else if (_loop)
        _index = 0;

    update();
}

void FCarousel::calcArrowPos()
{
    if (_arrow == Arrow::Never)
        return;

    const int diameter = FConstants::FCarousel::ArrowDiameter;
    const int radius = diameter / 2;
    const int margin = FConstants::FCarousel::ArrowMargin + radius;
    const QPoint center = rect().center();
    const int y = center.y();

    _leftArrowRect = QRect(margin - radius, y - radius, diameter, diameter);
    _rightArrowRect = QRect(width() - margin - radius, y - radius, diameter, diameter);
}

void FCarousel::calcIndicatorPos()
{
    if (_indicatorPos == IndicatorPos::None || _images.isEmpty())
    {
        _indicatorRects.clear();
        return;
    }

    const int indicatorW = FConstants::FCarousel::IndicatorWidth;
    const int indicatorH = FConstants::FCarousel::IndicatorHeight;
    const int spacing = FConstants::FCarousel::IndicatorSpacing;
    const int totalW = _images.size() * indicatorW + (_images.size() - 1) * spacing;
    const int startX = (width() - totalW) / 2;
    const int y = height() - FConstants::FCarousel::IndicatorBottomMargin - indicatorH / 2;

    _indicatorRects.clear();
    _indicatorRects.reserve(_images.size());

    for (int i = 0; i < _images.size(); ++i)
    {
        QRect rect(startX + i * (indicatorW + spacing),
                y - indicatorH / 2,
                indicatorW,
                indicatorH);
        _indicatorRects.append(rect);
    }
}


