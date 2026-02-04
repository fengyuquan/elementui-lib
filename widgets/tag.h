#pragma once

#include "private/utils.h"

#include <QLabel>
#include <QBoxLayout>

class FTag : public QLabel
{
    Q_OBJECT

public:
    enum class Effect
    {
        Dark,
        Light,
        Plain,
    };

    enum class Type
    {
        Primary,
        Success,
        Info,
        Warning,
        Danger,
    };

    enum class Size
    {
        Large,
        Default,
        Small,
    };

public:
    FTag& setEffect(Effect effect);
    FTag& setType(Type type);
    FTag& setSize(Size size);

    FTag& setCloseable(bool closeable);
    FTag& setRound(bool round);

    FTag& setText(const QString& text);

public:
    FTag(QWidget* parent = nullptr);
    FTag(const QString& text, QWidget* parent = nullptr);
    FTag(const QString& text, Type type, QWidget* parent = nullptr);

private:
    QString getColor();
    QString getBorderColor();
    QString getBackgroundColor();

    bool eventFilter(QObject* obj, QEvent* event);

private:
    Effect _effect = Effect::Light;
    Type _type = Type::Info;
    Size _size = Size::Default;

    bool _closeable;
    bool _round;

    QLabel* _textLabel = nullptr;
    QLabel* _closeIcon = nullptr;
    QHBoxLayout* _layout = nullptr;

private:
    QSSHelper _qsshelper;
    QSSHelper _internalQsshelper;
};

