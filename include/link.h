#pragma once

#include "private/utils.h"

#include <QLabel>

class FLink : public QLabel
{
    Q_OBJECT

public:
    enum class Type
    {
        Default = 0,
        Primary,
        Success,
        info,
        warning,
        Danger,
    };

    enum class Underline
    {
        Default = 0,
        Always,
        Hover,
        Never,
    };

public:
    Type getType();
    FLink& setType(Type type);

    Underline getUnderline();
    FLink& setUnderline(Underline underline);

    bool isDisabled();
    FLink& setDisabled(bool disabled);

    FLink& setText(const QString& text);

public:
    FLink(QWidget* parent = nullptr);
    FLink(const QString& text, QWidget* parent = nullptr);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    Type _type;
    Underline _underline;

 private:
    QSSHelper _qsshelper;
};

