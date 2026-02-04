#pragma once

#include "private/utils.h"

#include <QSpinBox>

class FInputNumber : public QSpinBox
{
    Q_OBJECT

public:
    enum class Size
    {
        Large = 0,
        Default,
        Small,
    };

    enum class ControlsPosition
    {
        Default = 0,
        Right,
    };

public:
    Size getSize();
    FInputNumber& setSize(Size size);

    bool isDisabled();
    FInputNumber& setDisabled(bool disabled);

    bool getReadOnly();
    FInputNumber& setReadOnly(bool readonly);

    ControlsPosition getControlsPosition();
    FInputNumber& setControlsPosition(ControlsPosition size);

    int getValue();
    FInputNumber& setValue(int value);

    QString getPrefix();
    FInputNumber& setPrefix(const QString &prefix);

    QString getSuffix();
    FInputNumber& setSuffix(const QString &suffix);

    int getStep();
    FInputNumber& setStep(int val);

    int getMin();
    FInputNumber& setMin(int min);

    int getMax();
    FInputNumber& setMax(int max);

    FInputNumber& setRange(int min, int max);

public:
    FInputNumber(QWidget* parent = nullptr);
    FInputNumber(int value, QWidget* parent = nullptr);

    void onvalueChanged(int);

private:
    Size _size = Size::Default;
    ControlsPosition _controlsPosition = ControlsPosition::Default;

private:
    QSSHelper _qssHelper;
};


