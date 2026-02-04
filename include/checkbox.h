#pragma once

#include "private/utils.h"

#include <QCheckBox>
#include <QGroupBox>
#include <QBoxLayout>

class FCheckboxGroup;

class FCheckbox : public QCheckBox
{
    Q_OBJECT

public:
    enum class Size { Large, Default, Small };

public:
    FCheckbox& setValue(const QVariant& value);
    QVariant getValue();

    FCheckbox& setText(const QString& text);
    QString getText();

    FCheckbox& setDisabled(bool disabled);
    bool isDisabled();

    FCheckbox& setSize(Size size);
    Size getSize();

    FCheckbox& setChecked(bool checked);
    bool getChecked();

    FCheckbox& setBorder(bool border);
    bool getBorder();

    FCheckbox& setIndeterminate(bool indeterminate);
    bool getIndeterminate();

public:
    FCheckbox(QWidget* parent = nullptr);
    FCheckbox(const QString& text, QWidget* parent = nullptr);
    FCheckbox(const QString& text, bool checked, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    QVariant _value;
    Size _size = Size::Default;
    bool _border = false;

private:
    FCheckboxGroup* _controlGroup = nullptr;
    QSSHelper _qsshelper;
};

class FCheckboxGroup : public QGroupBox
{
    Q_OBJECT

public:
    enum class Size { Large, Default, Small };

public:
    FCheckboxGroup& setSize(Size size);
    Size getSize();

    FCheckboxGroup& setDisabled(bool disabled);
    bool isDisabled();

    FCheckboxGroup& setMin(int min);
    int getMin();

    FCheckboxGroup& setMax(int max);
    int getMax();

    FCheckboxGroup& addCheckbox(FCheckbox* checkbox);
    FCheckboxGroup& setTitle(const QString& text);

public:
    FCheckboxGroup(QWidget* parent = nullptr);
    FCheckboxGroup(const QList<FCheckbox*>& checkboxs, QWidget* parent = nullptr);

private:
    void onStateChanged();
    int countChecked();

private:
    Size _size = Size::Default;
    int _min = 0, _max = 0;

private:
    QList<FCheckbox*> _checkboxs;
    QHBoxLayout* _layout = nullptr;
};
