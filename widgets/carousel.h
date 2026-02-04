#pragma once

#include "image.h"

#include <QWidget>
#include <QSvgRenderer>

class FCarousel : public QWidget
{
    Q_OBJECT
public:
    enum class Trigger
    {
        Hover,
        Click,
    };

    enum class IndicatorPos
    {
        Inside,
        Outside,
        None,
    };

    enum class Arrow
    {
        Always,
        Hover,
        Never,
    };

    enum class Type
    {
        Default,
        Card,
    };

    enum class Direction
    {
        Horizontal,
        Vertical,
    };

public:
    FCarousel& setTigger(Trigger trigger);
    FCarousel& setIndicatorPos(IndicatorPos pos);
    FCarousel& setArrow(Arrow arrow);
    FCarousel& setAutoplay(bool autoplay);
    FCarousel& setInterval(int interval);
    FCarousel& setType(Type type);
    FCarousel& setCardScale(double scale);
    FCarousel& setLoop(bool loop);
    FCarousel& setDirection(Direction direction);
    FCarousel& setPauseOnHover(bool pauseOnHover);
    FCarousel& addImage(const QPixmap& image);

public:
    FCarousel(QWidget* parent = nullptr);
    FCarousel(const QList<QPixmap>& images, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void showEvent(QShowEvent* event) override;

private:
    void showPrevious();
    void showNext();
    void calcArrowPos();
    void calcIndicatorPos();

private:
    Trigger _trigger = Trigger::Click;
    IndicatorPos _indicatorPos = IndicatorPos::Inside;
    Arrow _arrow = Arrow::Hover;
    bool _autoplay = true;
    int _interval = 3000;
    Type _type = Type::Default;
    double _cardScale = 0.83;
    bool _loop = true;
    Direction _direction = Direction::Horizontal;
    bool _pauseOnHover = true;

private:
    QList<QPixmap> _images;
    int _index = 0;

    bool _leftArrowHovered = false;
    bool _rightArrowHovered = false;
    QSvgRenderer* _leftArrowRenderer = nullptr;
    QSvgRenderer* _rightArrowRenderer = nullptr;
    QRect _leftArrowRect;
    QRect _rightArrowRect;

    QList<QRect> _indicatorRects;
    int _hoveredIndicatorIndex = -1;
};


