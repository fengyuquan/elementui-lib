#pragma once

#include <QScrollBar>
#include <QTimer>
#include <QWheelEvent>

class FScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    FScrollBar(Qt::Orientation orientation, QWidget* parent = nullptr);

protected:
    void wheelEvent(QWheelEvent* e) override;

private:
    QPointF subDelta(QPoint delta, int stepsLeft) const;
    void slotSmoothMove();

private:
    QTimer* smoothMoveTimer;
    QWheelEvent* lastWheelEvent;
    int stepsTotal;
QList<QPair<QPoint, int>> stepsLeftQueue;
};
