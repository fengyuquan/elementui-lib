#include "progress.h"
#include "private/utils.h"
#include "color.h"
#include "icon.h"
#include "constants.h"

#include <QPainter>

FProgress::FProgress(QWidget* parent)
    : FProgress(0, parent)
{}

FProgress::FProgress(int percentage, QWidget* parent)
    : QWidget(parent)
    , _precentage(percentage)
{
    setFont(FontHelper().setPointSize(sc(FConstants::FProgress::DefaultFontSize)).getFont());
}

FProgress& FProgress::setPercentage(int percentage)
{
    _precentage = percentage;
    update();
    return *this;
}

FProgress& FProgress::setType(Type type)
{
    _type = type;
    switch (_type)
    {
    case Type::Line: {
            setFixedHeight(qMax(_strokeWidth, FontHelper(font()).getTextHeight()));
        }
        break;
    case Type::Circle: {
            setMinimumSize(sc(FConstants::FProgress::CircleMinSize, FConstants::FProgress::CircleMinSize));
        }
        break;
    case Type::Dashboard: {
            setMinimumSize(sc(FConstants::FProgress::DashboardMinWidth, FConstants::FProgress::DashboardMinHeight));
        }
        break;
    }
    update();
    return *this;
}

FProgress& FProgress::setStrokeWidth(int width)
{
    _strokeWidth = width;
    int height = qMax(width, FontHelper(font()).getTextHeight());
    setFixedHeight(height);
    update();
    return *this;
}

FProgress& FProgress::setTextInside(bool textInside)
{
    _textInside = textInside;
    setStrokeWidth(FontHelper(font()).getTextHeight());
    update();
    return *this;
}

FProgress& FProgress::setStatus(Status status)
{
    _status = status;
    update();
    return *this;
}

FProgress& FProgress::setIndeterminate(bool indeterminate)
{
    _indeterminate = indeterminate;
    update();
    return *this;
}

FProgress& FProgress::setDuration(int duration)
{
    _duration = duration;
    update();
    return *this;
}

FProgress& FProgress::setColor(const std::function<QString(int)>& precent2Color)
{
    _color = precent2Color;
    update();
    return *this;
}

FProgress& FProgress::setShowText(bool showText)
{
    _showText = showText;
    update();
    return *this;
}

FProgress& FProgress::setStrokeLinecap(StrokeLinecap linecap)
{
    _strokeLinecap = linecap;
    update();
    return *this;
}

FProgress& FProgress::setFormat(const std::function<QString(int)>& precent2Text)
{
    _format = precent2Text;
    update();
    return *this;
}

void FProgress::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    switch (_type)
    {
    case Type::Line: paintLine(painter); break;
    case Type::Circle: paintCircle(painter); break;
    case Type::Dashboard: paintDashboard(painter); break;
    }
}

QString FProgress::getColor()
{
    switch (_status)
    {
    case Status::Success:
        return FColor::success();
    case Status::Exception:
        return FColor::danger();
    case Status::Warning:
        return FColor::warning();
    case Status::None:
    default:
        break;
    }

    if (_color)
    {
        QString color = _color(_precentage);
        if (!color.isEmpty())
            return color;
    }
    return FColor::primary();
}

void FProgress::paintLine(QPainter& painter)
{
    QRect rect = this->rect();

    QString text = _format ? _format(_precentage) : QString::number(_precentage) + '%';
    QFontMetrics fm(font());
    int textWidth = fm.horizontalAdvance(text);

    int radius = _strokeWidth / 2;

    // 绘制背景
    QRect bgRect = rect;
    bgRect.setTop(rect.top() + ((rect.height() - _strokeWidth) / 2));
    bgRect.setHeight(_strokeWidth);
    if (!_textInside)
        bgRect.adjust(0, 0, -textWidth - FConstants::FProgress::TextSpacing, 0);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(FColor::lighterBorder()));
    painter.drawRoundedRect(bgRect, radius, radius);

    // 绘制前景
    QRect fgRect = bgRect;
    fgRect.setWidth(bgRect.width() * _precentage / 100);

    painter.setBrush(QColor(getColor()));
    painter.drawRoundedRect(fgRect, radius, radius);

    // 绘制文字/图标
    if (_showText)
    {
        QRect textRect(rect.right() - textWidth, rect.top(), textWidth, rect.height());

        if (_status != Status::None)
        {
            QPixmap pixmap = FIcon::instance().getPixmap(
                _status == Status::Success ? FIcon::CircleCheck
              : _status == Status::Exception ? FIcon::CircleClose
                                             : FIcon::WarningFilled,
                getColor(), sc(FConstants::FProgress::IconSize));
            QRect iconRect = QRect(0, 0, pixmap.width(), pixmap.height());
            iconRect.moveCenter(textRect.center());
            painter.drawPixmap(iconRect, pixmap);
        }
        else
        {
            if (_textInside)
                textRect.moveLeft(fgRect.width() - textWidth - FConstants::FProgress::TextSpacing);
            painter.setPen(_textInside ? Qt::white : QColor(FColor::regularText()));
            painter.drawText(textRect, Qt::AlignCenter, text);
        }
    }
}

void FProgress::paintCircle(QPainter& painter)
{
    int& sw = _strokeWidth;
    int size = qMin(width(), height());
    QRect rect(0, 0, size, size);
    rect.moveCenter(this->rect().center());

    // 绘制背景
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(FColor::lightFill()));
    painter.drawEllipse(rect);

    // 绘制留白
    painter.setBrush(Qt::white);
    painter.drawEllipse(rect.adjusted(sw, sw, -sw, -sw));

    // 绘制前景
    QPen pen;
    pen.setColor(QColor(getColor()));
    pen.setWidth(sw);
    pen.setCapStyle(_strokeLinecap == StrokeLinecap::Butt ? Qt::FlatCap
                : _strokeLinecap == StrokeLinecap::Square ? Qt::SquareCap : Qt::RoundCap);

    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    int startAngle = FConstants::FProgress::CircleStartAngle * 16;
    int spanAngle = -FConstants::FProgress::CircleSpanAngle * _precentage / 100.0 * 16;
    painter.drawArc(rect.adjusted(sw/2, sw/2, -sw/2, -sw/2), startAngle, spanAngle);

    // 绘制文字/图标
    if (_showText)
    {
        QString text = _format ? _format(_precentage) : QString::number(_precentage) + '%';

        if (_status != Status::None)
        {
            QPixmap pixmap = FIcon::instance().getPixmap(
                _status == Status::Success ? FIcon::CircleCheck
              : _status == Status::Exception ? FIcon::CircleClose
                                             : FIcon::WarningFilled,
                getColor(), sc(FConstants::FProgress::IconSize));
            QRect iconRect(0, 0, pixmap.width(), pixmap.height());
            iconRect.moveCenter(rect.center());
            painter.drawPixmap(iconRect, pixmap);
        }
        else
        {
            painter.setPen(QColor(FColor::regularText()));
            QFontMetrics fm(font());
            int textWidth = fm.horizontalAdvance(text);
            int textHeight = fm.height();

            QRect textRect(0, 0, textWidth, textHeight);
            textRect.moveCenter(rect.center());

            painter.drawText(textRect, Qt::AlignCenter, text);
        }
    }
}

void FProgress::paintDashboard(QPainter& painter)
{
    int& sw = _strokeWidth;
    int w = width() < height() ? width() : height() * FConstants::FProgress::DashboardWidthRatio;

    QRect rect(0, 0, w, w);
    rect.moveCenter(this->rect().center());
    rect.moveTop(this->rect().top());

    // 绘制背景
    QPen pen;
    pen.setColor(QColor(FColor::lightFill()));
    pen.setWidth(sw);
    pen.setCapStyle(_strokeLinecap == StrokeLinecap::Butt ? Qt::FlatCap
                : _strokeLinecap == StrokeLinecap::Square ? Qt::SquareCap : Qt::RoundCap);

    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    int startAngle = FConstants::FProgress::DashboardStartAngle * 16;
    int spanAngle = -FConstants::FProgress::DashboardSpanAngle * 16;
    painter.drawArc(rect.adjusted(sw/2, sw/2, -sw/2, -sw/2), startAngle, spanAngle);

    // 绘制前景
    pen.setColor(QColor(getColor()));
    pen.setWidth(sw);
    pen.setCapStyle(_strokeLinecap == StrokeLinecap::Butt ? Qt::FlatCap
                : _strokeLinecap == StrokeLinecap::Square ? Qt::SquareCap : Qt::RoundCap);

    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    startAngle = FConstants::FProgress::DashboardStartAngle * 16;
    spanAngle = -FConstants::FProgress::DashboardSpanAngle * _precentage / 100.0 * 16;
    painter.drawArc(rect.adjusted(sw/2, sw/2, -sw/2, -sw/2), startAngle, spanAngle);

    // 绘制文字/图标
    if (_showText)
    {
        QString text = _format ? _format(_precentage) : QString::number(_precentage) + '%';

        if (_status != Status::None)
        {
            QPixmap pixmap = FIcon::instance().getPixmap(
                _status == Status::Success ? FIcon::CircleCheck
              : _status == Status::Exception ? FIcon::CircleClose
                                             : FIcon::WarningFilled,
                getColor(), sc(FConstants::FProgress::IconSize));
            QRect iconRect(0, 0, pixmap.width(), pixmap.height());
            iconRect.moveCenter(rect.center());
            painter.drawPixmap(iconRect, pixmap);
        }
        else
        {
            painter.setPen(QColor(FColor::regularText()));
            QFontMetrics fm(font());
            int textWidth = fm.horizontalAdvance(text);
            int textHeight = fm.height();

            QRect textRect(0, 0, textWidth, textHeight);
            textRect.moveCenter(rect.center());

            painter.drawText(textRect, Qt::AlignCenter, text);
        }
    }
}


