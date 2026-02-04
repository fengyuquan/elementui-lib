#pragma once

#include "private/utils.h"
#include "color.h"

#include <QLabel>

class FBadge : public QLabel
{
    Q_OBJECT

public:
    enum class Type
    {
        Primary,
        Success,
        Info,
        Warning,
        Danger,
    };

public:
    FBadge& setType(Type type);
    FBadge& setIsDot(bool isdot);
    FBadge& setValue(int value);
    FBadge& setValue(const QString& value);
    FBadge& setMax(int max);

public:
    FBadge(QWidget* parent = nullptr);
    FBadge(bool isDot, QWidget* parent = nullptr);
    FBadge(int value, QWidget* parent = nullptr);
    FBadge(int value, int max, QWidget* parent = nullptr);
    FBadge(const QString& value, QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event);

private:
    QString getColor();
    void updatePosition();

private:
    Type _type = Type::Danger;

private:
    QWidget* _partner;

    int _numValue;
    int _max;
    QString _strValue;
    bool _isDot;

private:
    QSSHelper _qsshelper;
};

