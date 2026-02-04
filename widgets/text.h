#pragma once

#include "private/utils.h"
#include "color.h"

#include <QString>
#include <QLabel>
#include <QEnterEvent>

class FText : public QLabel
{
    Q_OBJECT

public:
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
        Large = 0, // 12
        Default, // 10
        Small, // 8
    };

    enum class Tag
    {
        Default = 0,
        Paragraph,
        Bold,
        Italic,
        Subscript,
        Superscript,
        Inserted,
        Deleted,
        Marked,
    };

public:
    FText(QWidget* parent = nullptr);
    FText(const QString &text, QWidget* parent = nullptr);
    FText(const QString &text, Type type, QWidget* parent = nullptr);

    Type getType();
    FText& setType(Type type);

    Size getSize();
    FText& setSize(Size size);

    Tag getTag();
    FText& setTag(Tag tag);

    bool getTruncated();
    FText& setTruncated(bool truncated);

public:
    FText& setColor(const QString& color);
    FText& setFontSize(int size);

signals:
    void clicked();
    void rightClicked();
    void hovered(bool isHovered);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    Type _type = Type::Default;
    Size _size = Size::Default;
    Tag _tag = Tag::Default;
    bool _truncated = false;

private:
    void setFontColor(int color);
    void setSubscript();
    void setSupscript();
};

inline FText* h1(const QString& text, QWidget* parent)
{
    FText* h1 = new FText(text, parent);
    h1->setFontSize(25);
    return h1;
}

inline FText* h2(const QString& text, QWidget* parent)
{
    FText* h2 = new FText(text, parent);
    h2->setColor(FColor::primaryText());
    h2->setFontSize(20);
    return h2;
}

inline FText* h3(const QString& text, QWidget* parent)
{
    FText* h3 = new FText(text, parent);
    h3->setColor(FColor::primaryText());
    h3->setFontSize(16);
    return h3;
}

inline FText* p(const QString& text, QWidget* parent)
{
    FText* p = new FText(text, parent);
    p->setColor(FColor::primaryText());
    p->setFontSize(11);
    return p;
}

