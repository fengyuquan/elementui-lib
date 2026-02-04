#pragma once

#include "icon.h"

#include <QString>
#include <QLabel>
#include <QFile>
#include <QSvgRenderer>

class FAvatar : public QLabel
{
    Q_OBJECT

public:
    enum class Shape { Circle, Square };
    enum class Size { Large, Default, Small  };
    enum class Type { Icon, Image, Text };

public:
    FAvatar& setIcon(FIcon::Name icon = FIcon::UserFilled);
    FAvatar& setImage(const QImage& file = QImage(":/icons/other/example-avatar.png"));
    FAvatar& setText(const QString& text = "user");

    FAvatar& setSize(Size size);
    FAvatar& setShape(Shape shape);

public:
    FAvatar(QWidget* parent = nullptr);
    FAvatar(FIcon::Name icon, QWidget* parent = nullptr);
    FAvatar(const QImage& file, QWidget* parent = nullptr);
    FAvatar(const QString& text, QWidget* parent = nullptr);

    FAvatar(FIcon::Name icon, Shape shape = Shape::Circle, Size size = Size::Default, QWidget* parent = nullptr);
    FAvatar(const QImage& file, Shape shape = Shape::Circle, Size size = Size::Default, QWidget* parent = nullptr);
    FAvatar(const QString& text, Shape shape = Shape::Circle, Size size = Size::Default, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    int calcSize();

private:
    Shape _shape = Shape::Circle;
    Size _size = Size::Default;
    Type _type;

private:
    QSvgRenderer* _svgRenderer = nullptr;
    QString _text;
    QImage _image;
};


