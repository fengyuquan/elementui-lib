#include "shadow.h"
#include "constants.h"

#include <QGraphicsDropShadowEffect>

void FShadowEf::setShadow(QWidget* widget, Type type)
{
    if (!widget) return;

    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(widget);

    if (type == Type::Basic)
    {
        shadow->setBlurRadius(FConstants::FShadow::BasicBlurRadius);
        shadow->setOffset(FConstants::FShadow::BasicOffsetX, FConstants::FShadow::BasicOffsetY);
        shadow->setColor(QColor(0, 0, 0, static_cast<int>(FConstants::FShadow::BasicColorAlpha * FConstants::FCommon::ColorAlphaMax)));
    }
    else if (type == Type::Light)
    {
        shadow->setBlurRadius(FConstants::FShadow::LightBlurRadius);
        shadow->setOffset(FConstants::FShadow::LightOffsetX, FConstants::FShadow::LightOffsetY);
        shadow->setColor(QColor(0, 0, 0, static_cast<int>(FConstants::FShadow::LightColorAlpha * FConstants::FCommon::ColorAlphaMax)));
    }
    else if (type == Type::Lighter)
    {
        shadow->setBlurRadius(FConstants::FShadow::LighterBlurRadius);
        shadow->setOffset(FConstants::FShadow::LighterOffsetX, FConstants::FShadow::LighterOffsetY);
        shadow->setColor(QColor(0, 0, 0, static_cast<int>(FConstants::FShadow::LighterColorAlpha * FConstants::FCommon::ColorAlphaMax)));
    }
    else if (type == Type::Dark)
    {
        shadow->setBlurRadius(FConstants::FShadow::DarkBlurRadius);
        shadow->setOffset(FConstants::FShadow::DarkOffsetX, FConstants::FShadow::DarkOffsetY);
        shadow->setColor(QColor(0, 0, 0, static_cast<int>(FConstants::FShadow::DarkColorAlpha * FConstants::FCommon::ColorAlphaMax)));
    }

    if (!widget->autoFillBackground())
    {
        QPalette pal = widget->palette();
        pal.setColor(QPalette::Window, Qt::white);
        widget->setPalette(pal);
        widget->setAutoFillBackground(true);
    }
    widget->setGraphicsEffect(shadow);
}

