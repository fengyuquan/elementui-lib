#pragma once

#include "private/utils.h"

#include <QLabel>
#include <QBoxLayout>
#include <QTimer>

// Two objects need to set: partner and target.
// Partner is the pop-up widget, target is the pointing widget.
// eg. the pop-up widget is the tooltip, the pointing widget is the button.
// +--------------+
// |   Tooltip    | <=> parnter
// +------\/------+
//
//   +----------+
//   |  Button  |  <=> target
//   +----------+
class FArrow : public QWidget
{
    Q_OBJECT

public:
    enum class Direction { Up, Down, Left, Right };
    enum class AlignMode { FollowPointing, FollowPopup };

public:
    void setAlignMode(AlignMode mode);
    AlignMode getAlignMode();

    void setColor(const QString& color);
    void setDirection(Direction direction);

    // Due to anti-aliasing,
    // the actual border color will appear lighter.
    // Therefore, please set a darker color.​
    void setBorder(const QString& color);

    void updatePosition();

public:
    FArrow(QWidget* partner, QWidget* target);
    FArrow(const QString& color, Direction dir, QWidget* partner, QWidget* target);

protected:
    void paintEvent(QPaintEvent* event) override;
    void showEvent(QShowEvent* event) override;

private:
    QWidget* _partner = nullptr;
    QWidget* _target = nullptr;

    Direction _direction = Direction::Down;
    AlignMode _mode = AlignMode::FollowPointing;

    QString _color;
    QString _borderColor;
};

class FTooltip : public QWidget
{

    Q_OBJECT

public:
    enum class Placement
    {
        Top, TopStart, TopEnd,
        Left, LeftStart, LeftEnd,
        Right, RightStart, RightEnd,
        Bottom, BottomStart, BottomEnd,
    };

    enum class Effect { Dark, Light, };

    enum class Trigger { Hover, Click, Focus, ContextMenu };

public:
    FTooltip& setPlacement(Placement placement);
    FTooltip& setEffect(Effect effect);
    FTooltip& setTrigger(Trigger trigger);
    FTooltip& setText(const QString& text);
    FTooltip& setDisabled(bool disabled);
    FTooltip& setOffset(int offset);
    FTooltip& setShowAfter(int msec);
    FTooltip& setHideAfter(int msec);
    FTooltip& setShowArrow(bool showArrow);
    FTooltip& setAutoClose(int duration);
    FTooltip& setEnterable(bool enterable);

    Placement getPlacement();

    bool isDisabled();

    FTooltip& setMoveable(bool moveable);
    FTooltip& setPosition(const QPoint& start);

public:
    void show();
    void hide();
    void setVisible(bool visible) override;

public:
    FTooltip(const QString& text, QWidget* target);
    FTooltip(const QString& text, Effect effect, QWidget* target);
    FTooltip(const QString& text, Placement placement, QWidget* target);
    FTooltip(const QString& text, Placement placement, Effect effect, QWidget* target);

protected:
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    void updatePosition();
    Placement checkPlacement();

private:
    Placement _placement = Placement::Top;
    Effect _effect = Effect::Dark;
    Trigger _trigger = Trigger::Hover;

    int _offset = 15;
    int _showAfter = 0;
    int _hideAfter = 200;
    bool _showArrow = true;
    bool _duration = 0;
    bool _enterable = true;

    bool _moveable = false;

private:
    QWidget* _target = nullptr;
    QLabel* _label = nullptr;
    FArrow* _arrow = nullptr;

    QTimer* _showTimer = nullptr;
    QTimer* _hideTimer = nullptr;
    QTimer* _autoCloseTimer = nullptr;

    QSSHelper _qsshelper;
};

