#pragma once

#include <QWidget>

class FMask;

class FMaskEf
{
public:
    static FMask* setMask(QWidget* partner, QWidget* covered);
};

class FMask : public QWidget
{
    Q_OBJECT
public:
    FMask(QWidget* partner, QWidget* covered);

signals:
    void clicked();

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    QWidget* _partner = nullptr;
    QWidget* _covered = nullptr;
};

