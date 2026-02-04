#include "rate.h"

#include "private/utils.h"
#include "color.h"
#include "icon.h"
#include "constants.h"

#include <QtMath>

FRate::FRate(QWidget* parent)
    : FRate(0.0, parent)
{}

FRate::FRate(float value, QWidget* parent)
    : QWidget(parent)
    , _layout(new QHBoxLayout(this))
    , _text(new FText(this))
{
    installEventFilter(this);
    _layout->setContentsMargins(0, FConstants::FRate::LayoutMarginVertical, 0, FConstants::FRate::LayoutMarginVertical);
    _layout->setSpacing(FConstants::FRate::LayoutSpacing);

    for (int i = 0; i < FConstants::FRate::StarCount; i++)
    {
        QSvgWidget* star = new QSvgWidget(this);
        star->load(FIcon::instance().getCodeArray(FIcon::Star, FColor::darkBorder()));
        star->setFixedSize(FConstants::FRate::DefaultIconSize, FConstants::FRate::DefaultIconSize);
        star->installEventFilter(this);
        star->setMouseTracking(true);

        _stars.append(star);
        _layout->addWidget(star);
    }

    setCursor(Qt::PointingHandCursor);

    setSize(_size);
    setScore(value);
}

FRate& FRate::setScore(qreal value)
{
    _value = qFloor(value * 10.0);
    _value = qBound(0, _value, FConstants::FRate::StarCount * 10);

    update(_value);
    return *this;
}

qreal FRate::getScore()
{
    return (_value / 10.0) * (_max / 50);
}

FRate& FRate::setMax(int max)
{
    if (max >= 5 && max % 5 == 0)
        _max = max * 10;
    return *this;
}

int FRate::getMax()
{
    return _max / 10;
}

FRate& FRate::setSize(Size size)
{
    _size = size;

    int totalHeight = _size == Size::Large ? FConstants::FRate::LargeHeight : _size == Size::Default ? FConstants::FRate::DefaultHeight : FConstants::FRate::SmallHeight;
    int iconSize = _size == Size::Large ? FConstants::FRate::LargeIconSize : _size == Size::Default ? FConstants::FRate::DefaultIconSize : FConstants::FRate::SmallIconSize;

    for (auto* star : _stars)
        star->setFixedSize(iconSize, iconSize);

    setFixedHeight(totalHeight);
    adjustSize();
    return *this;
}

FRate::Size FRate::getSize()
{
    return _size;
}

FRate& FRate::setAllowHalf(bool allowHalf)
{
    _allowHalf = allowHalf;
    return *this;
}

bool FRate::getAllowHalf()
{
    return _allowHalf;
}

FRate& FRate::setLowThreshold(int lowThreshold)
{
    if (lowThreshold % (_max / 50) == 0 && lowThreshold > 0 && lowThreshold < _max)
        _lowThreshold = lowThreshold / (_max / 50) * 10;
    return *this;
}

int FRate::getLowThreshold()
{
    return _lowThreshold / 10;
}

FRate& FRate::setHighThreshold(int highThreshold)
{
    if (highThreshold % (_max / 50) == 0 && highThreshold > 0 && highThreshold < _max)
        _highThreshold = highThreshold / (_max / 50) * 10;
    return *this;
}

int FRate::setHighThreshold()
{
    return _highThreshold / 10;
}

FRate& FRate::setShowText(bool showText)
{
    _showText = showText;

    if (showText)
        _showScore = false;

    if (showText)
    {
        _layout->addWidget(_text);
    }
    else
    {
        _layout->removeWidget(_text);
        _text->hide();
    }

    adjustSize();
    return *this;
}

bool FRate::getShowText()
{
    return _showText;
}

FRate& FRate::setShowScore(bool showScore)
{
    _showScore = showScore;

    if (showScore)
        _showText = false;

    if (showScore)
    {
        _layout->addWidget(_text);
    }
    else
    {
        _layout->removeWidget(_text);
        _text->hide();
    }

    adjustSize();
    return *this;
}

bool FRate::getShowScore()
{
    return _showScore;
}

FRate& FRate::setClearable(bool clearable)
{
    _clearable = clearable;
    return *this;
}

bool FRate::getClearable()
{
    return _clearable;
}

FRate& FRate::setDisabled(bool disabled)
{
    QWidget::setDisabled(disabled);
    setCursor(disabled ? Qt::ArrowCursor : Qt::PointingHandCursor);
    return *this;
}

bool FRate::isDisabled()
{
    return !QWidget::isEnabled();
}

FRate& FRate::setColors(const QString& lowColor, const QString& midColor, const QString& highColor)
{
    _lowColor = lowColor, _midColor = midColor, _highColor = highColor;
    return *this;
}

FRate& FRate::setTexts(const QString& first, const QString& second, const QString& third,
                     const QString& fourth, const QString& fifth)
{
    _texts = QStringList{first, second, third, fourth, fifth};
    return *this;
}

bool FRate::eventFilter(QObject* obj, QEvent* event)
{
    if (isDisabled())
        return QWidget::eventFilter(obj, event);

    if (event->type() != QEvent::MouseMove
     && event->type() != QEvent::MouseButtonPress
     && event->type() != QEvent::Leave)
        return QWidget::eventFilter(obj, event);

    for (int i = 0; i < _stars.size(); ++i)
    {
        if (obj == _stars[i])
        {
            int pcent = qRound(static_cast<QMouseEvent*>(event)->x() * 10.0
                             / _stars[i]->width());
            int frac = 0;

            if (pcent <= 0) frac = 0;
            else if (_allowHalf && pcent <= 5) frac = 5;
            else frac = 10;

            int tmpval = (i * 10 + frac);

            if (event->type() == QEvent::MouseMove)
            {
                update(tmpval);
            }
            else if (event->type() == QEvent::MouseButtonPress)
            {
                if (_clearable && _value == tmpval)
                    setValue(0);
                else
                    setValue(tmpval);
            }
        }
    }

    if (obj == this && event->type() == QEvent::Leave)
    {
        update(_value);
    }

    return QWidget::eventFilter(obj, event);
}

void FRate::update(int value)
{
    int full = value / 10;
    int part = value % 10;

    QString color = getColor(value);

    for (int i = 0; i < _stars.size(); ++i)
    {
        if (i < full)
        {
            _stars[i]->load(FIcon::instance().getCodeArray(FIcon::StarFilled, color));
        }
        else if (i == full && part > 0)
        {
            // 半星暫不做裁切，先用滿星顯示（避免出現空白）
            _stars[i]->load(FIcon::instance().getCodeArray(FIcon::StarFilled, color));
        }
        else
        {
            if (isDisabled())
                _stars[i]->load(FIcon::instance().getCodeArray(FIcon::StarFilled, FColor::baseFill()));
            else
                _stars[i]->load(FIcon::instance().getCodeArray(FIcon::Star, FColor::darkBorder()));
        }
    }

    if (_showText)
    {
        if (full == 0 && part == 0)
        {
            _text->hide();
        }
        else if (part != 0)
        {
            _text->setText(_texts[full]);
            _text->show();
        }
        else
        {
            _text->setText(_texts[full - 1]);
            _text->show();
        }
    }
    else if (_showScore)
    {
        _text->setText(QString::number((value / 10.0) * (_max / 50)) + " points");
        _text->setColor(color);
        _text->show();
    }

    adjustSize();
}

QString FRate::getColor(int value)
{
    if (value <= _lowThreshold)
        return _lowColor;
    else if (value < _highThreshold)
        return _midColor;
    else
        return _highColor;
}

void FRate::setValue(int value)
{
    _value = value;
}

QByteArray FRate::partialStar(int percent, const QString& fillColor, const QString& borderColor)
{
    Q_UNUSED(percent);
    Q_UNUSED(fillColor);
    Q_UNUSED(borderColor);

    return "";
}


