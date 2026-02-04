#include "scrollbar.h"
#include "constants.h"

#include <QtMath>
#include <QApplication>
#include <QQueue>
#include <QDateTime>
#include <QDebug>

FScrollBar::FScrollBar(Qt::Orientation orientation, QWidget* parent)
    : QScrollBar(orientation, parent)
    , lastWheelEvent(nullptr)
    , stepsTotal(0)
{
    setMouseTracking(true);
    QString styleSheet = QString(R"(
        QScrollBar { background-color: transparent; border: none; }
        QScrollBar:vertical { width: %1px; }
        QScrollBar:horizontal { height: %1px; }
        QScrollBar::handle { background: rgba(144, 147, 153, %2); border-radius: %3px; }
        QScrollBar::handle:hover { background: rgba(144, 147, 153, %4); }
        QScrollBar::handle:pressed { background: rgba(144, 147, 153, %4); }
        QScrollBar::add-page, QScrollBar::sub-page { background: none; }
        QScrollBar::add-line:vertical { height: 0px; subcontrol-position: bottom; subcontrol-origin: margin; }
        QScrollBar::sub-line:vertical { height: 0px; subcontrol-position: top; subcontrol-origin: margin; }
        QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical { height: 0px; width: 0px; }
        QScrollBar::add-line:horizontal { width: 0px; subcontrol-position: right; subcontrol-origin: margin; }
        QScrollBar::sub-line:horizontal { width: 0px; subcontrol-position: left; subcontrol-origin: margin; }
        QScrollBar::left-arrow:horizontal, QScrollBar::right-arrow:horizontal { width: 0px; height: 0px; } )")
        .arg(FConstants::FScrollBar::VerticalWidth)
        .arg(FConstants::FScrollBar::HandleBackgroundAlpha / 255.0)
        .arg(FConstants::FScrollBar::HandleBorderRadius)
        .arg(FConstants::FScrollBar::HandleHoverAlpha / 255.0);
    setStyleSheet(styleSheet);

    smoothMoveTimer = new QTimer(this);
    connect(smoothMoveTimer, &QTimer::timeout, this, &FScrollBar::slotSmoothMove);
}

void FScrollBar::wheelEvent(QWheelEvent* e)
{
    static QQueue<qint64> scrollStamps;
    qint64 now = QDateTime::currentDateTime().toMSecsSinceEpoch();
    scrollStamps.enqueue(now);
    while (now - scrollStamps.front() > FConstants::FScrollBar::ScrollTimeWindow)
        scrollStamps.dequeue();
    double accRatio = qMin(scrollStamps.size() / static_cast<double>(FConstants::FScrollBar::ScrollAccelerationThreshold), 1.0);

    if (!lastWheelEvent)
        lastWheelEvent = new QWheelEvent(*e);
    else
        *lastWheelEvent = *e;

    stepsTotal = FConstants::FScrollBar::SmoothScrollTotalSteps;
    double multiplier = 1.0;
    if (QApplication::keyboardModifiers() & Qt::ALT)
        multiplier *= FConstants::FScrollBar::AltKeyMultiplier;
    auto delta = e->angleDelta() * multiplier;
    delta += delta * FConstants::FScrollBar::ScrollAccelerationRatio * accRatio;

    stepsLeftQueue.push_back(qMakePair(delta, stepsTotal));
    smoothMoveTimer->start(1000 / FConstants::FScrollBar::SmoothScrollFPS);

    bool isTop = delta.y() > 0 && value() == minimum();
    bool isBottom = delta.y() < 0 && value() == maximum();
    if (!isTop && !isBottom) {
        e->accept();
    }
}

QPointF FScrollBar::subDelta(QPoint delta, int stepsLeft) const
{
    double m = stepsTotal / FConstants::FScrollBar::SmoothScrollDivisor;
    double x = abs(stepsTotal - stepsLeft - m);
    return (cos(x * M_PI / m) + 1.0) / (2.0 * m) * delta;
}

void FScrollBar::slotSmoothMove()
{
    QPointF totalDelta;

    for (auto & it : stepsLeftQueue) {
        totalDelta += subDelta(it.first, it.second);
        --(it.second);
    }
    while (!stepsLeftQueue.empty() && stepsLeftQueue.begin()->second == 0)
        stepsLeftQueue.pop_front();

    QWheelEvent e(
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
        lastWheelEvent->position(),
        lastWheelEvent->globalPosition(),
#else
        lastWheelEvent->pos(),
        lastWheelEvent->globalPos(),
#endif
        QPoint(),
        totalDelta.toPoint(),
        lastWheelEvent->buttons(),
        lastWheelEvent->modifiers(),
        lastWheelEvent->phase(),
        lastWheelEvent->inverted()
    );
    QScrollBar::wheelEvent(&e);
    if (stepsLeftQueue.empty()) {
        smoothMoveTimer->stop();
    }
}
