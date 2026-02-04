#pragma once

#include "private/utils.h"

#include <QRadioButton>
#include <QGroupBox>
#include <QBoxLayout>

class FRadio : public QRadioButton
{
Q_OBJECT

public:
    enum class Size { Large, Default, Small };

public:
    FRadio& setValue(const QVariant& value);
    QVariant getValue();

    FRadio& setText(const QString& text);
    QString getText();

    FRadio& setDisabled(bool disabled);
    bool isDisabled();

    FRadio& setSize(Size size);
    Size getSize();

    FRadio& setChecked(bool checked);
    bool getChecked();

    FRadio& setBorder(bool border);
    bool getBorder();

public:
    FRadio(QWidget* parent = nullptr);
    FRadio(const QString& text, QWidget* parent = nullptr);
    FRadio(const QString& text, bool checked, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    QVariant _value;
    Size _size = Size::Default;
    bool _border = false;

private:
    QSSHelper _qsshelper;
};

class FRadioGroup : public QGroupBox
{
Q_OBJECT

public:
    enum class Size { Large, Default, Small };

public:
    FRadioGroup& setSize(Size size);
    Size getSize();

    FRadioGroup& setDisabled(bool disabled);
    bool isDisabled();

    FRadioGroup& addRadio(FRadio* radio);
    FRadioGroup& setTitle(const QString&);

public:
    FRadioGroup(QWidget* parent = nullptr);
    FRadioGroup(const QList<FRadio*>& radios, QWidget* parent = nullptr);

private:
    Size _size = Size::Default;

private:
    QList<FRadio*> _radios;
    QHBoxLayout* _layout = nullptr;
};
