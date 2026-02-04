#pragma once

#include "icon.h"
#include "private/utils.h"

#include <QString>
#include <QPushButton>

class FButton : public QPushButton
{
    Q_OBJECT

public:
    enum class Style
    {
        Default = 0,
        Plain,
        Round,
        Circle,
        Link,
        Text,
    };

    enum class Type
    {
        Default = 0,
        Primary,
        Success,
        Info,
        Warning,
        Danger,
    };

    enum class Size
    {
        Large = 0,
        Default,
        Small,
    };

    enum class IconPosition
    {
        Only = 0,
        Left,
        Right,
    };

private:
    using Self = FButton;

public:
    Style getStyle();
    FButton& setStyle(Style style);

    Type getType();
    FButton& setType(Type type);

    Size getSize();
    FButton& setSize(Size size);


    bool isDisabled();
    FButton& setDisabled(bool disabled);

    bool isLoading();
    FButton& setLoading(bool loading);

    QPair<FIcon::Name, IconPosition> getIcon();
    FButton& setIcon(FIcon::Name name, IconPosition pos = IconPosition::Only);

    FButton& setText(const QString& text);

public:
    FButton(QWidget* parent = nullptr);
    FButton(const QString& text, QWidget* parent = nullptr);

private:
    Style _style = Style::Default;
    Type _type = Type::Default;
    Size _size = Size::Default;

    bool _loading = false;

    FIcon::Name _icon;
    IconPosition _iconPostion = IconPosition::Left;

    QString _color; // TODO

    QSSHelper _qsshelper;


protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
};