#pragma once

#include <QWidget>

class FShadowEf
{
public:
    enum class Type
    {
        Basic,
        Light,
        Lighter,
        Dark,
    };

public:
    static void setShadow(QWidget* widget, Type type);
};
