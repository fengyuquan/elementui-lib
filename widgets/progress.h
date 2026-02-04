#pragma once

#include <QWidget>
#include <functional>

class FProgress : public QWidget
{
    Q_OBJECT

public:
    enum class Type
    {
        Line,
        Circle,
        Dashboard,
    };

    enum class Status
    {
        None,
        Success,
        Exception,
        Warning,
    };

    enum class StrokeLinecap
    {
        Butt,
        Round,
        Square,
    };

public:
    FProgress& setPercentage(int percentage);
    FProgress& setType(Type type);
    FProgress& setStrokeWidth(int width);
    FProgress& setTextInside(bool textInside);
    FProgress& setStatus(Status status);
    FProgress& setIndeterminate(bool indeterminate);
    FProgress& setDuration(int duration);
    FProgress& setColor(const std::function<QString(int)>& precent2Color);
    FProgress& setShowText(bool showText);
    FProgress& setStrokeLinecap(StrokeLinecap linecap);
    FProgress& setFormat(const std::function<QString(int)>& format);

public:
    FProgress(QWidget* parent = nullptr);
    FProgress(int percentage, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QString getColor();
    void paintLine(QPainter& painter);
    void paintCircle(QPainter& painter);
    void paintDashboard(QPainter& painter);

private:
    int _precentage = 0;
    Type _type = Type::Line;
    int _strokeWidth = 6;
    bool _textInside = false;
    Status _status = Status::None;
    bool _indeterminate = false;
    int _duration = 3;
    std::function<QString(int)> _color = nullptr;
    bool _showText = true;
    StrokeLinecap _strokeLinecap = StrokeLinecap::Round;
    std::function<QString(int)> _format = nullptr;
};


