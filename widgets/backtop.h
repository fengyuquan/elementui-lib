#pragma once

#include <QLabel>
#include <QScrollArea>
#include <QSvgRenderer>

class FBacktop : public QLabel
{
    Q_OBJECT

public:
    enum class Shape { Circle, Square };
    enum class Size { Large, Default, Small };
    enum class Type { Icon, Text };

public:
    FBacktop& setShape(Shape shape);
    FBacktop& setSize(Size size);
    FBacktop& setType(Type type);

    FBacktop& setTarget(QScrollArea* target);
    FBacktop& setVisibilityHeight(int visibilityHeight);
    FBacktop& setRight(int right);
    FBacktop& setBottom(int bottom);

public:
    FBacktop(QWidget* parent);
    FBacktop(QScrollArea* target, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private slots:
        void onScrollBarValueChanged(int value);

private:
    Shape _shape = Shape::Circle;
    Size _size = Size::Default;
    Type _type = Type::Icon;

private:
    QScrollArea* _target = nullptr;
    int _visibilityHeight;
    int _right;
    int _bottom;

private:
    QSvgRenderer* _svgRenderer = nullptr;
};


