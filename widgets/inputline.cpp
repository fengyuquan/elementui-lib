#include "inputline.h"
#include "color.h"
#include "private/utils.h"
#include "constants.h"

#include <QApplication>
#include <QMargins>
#include <QAction>
#include <QMouseEvent>

FInputLine::FInputLine(QWidget* parent)
    : FInputLine("Please input", parent)
{}

FInputLine::FInputLine(const QString& placeholder, QWidget* parent)
    : QLineEdit(parent)
{
    setPlaceholderText(placeholder);
    setSize(Size::Default);

    setMinimumWidth(sc(FConstants::FInputLine::DefaultMinWidth));
    connect(this, &QLineEdit::textChanged, this, &FInputLine::onTextChanged);
}

QString FInputLine::getPlaceholder()
{
    return placeholderText();
}

FInputLine& FInputLine::setPlaceholder(const QString& placeholder)
{
    QLineEdit::setPlaceholderText(placeholder);
    return *this;
}

int FInputLine::getWidth()
{
    return QLineEdit::width();
}

FInputLine& FInputLine::setWidth(int width)
{
    QLineEdit::setFixedWidth(width);
    return *this;
}

bool FInputLine::isDisabled()
{
    return !QLineEdit::isEnabled();
}

FInputLine& FInputLine::setDisabled(bool disabled)
{
    QLineEdit::setDisabled(disabled);
    return *this;
}

FInputLine::Size FInputLine::getSize()
{
    return _size;
}

FInputLine& FInputLine::setSize(Size size)
{
    _size = size;

    QString fontSize = size == Size::Large ? QString::number(FConstants::FInputLine::LargeFontSize) + "px"
                    : size == Size::Default ? QString::number(FConstants::FInputLine::DefaultFontSize) + "px" 
                    : QString::number(FConstants::FInputLine::SmallFontSize) + "px";
    int height = size == Size::Large ? sc(FConstants::FInputLine::LargeHeight)
                : size == Size::Default ? sc(FConstants::FInputLine::DefaultHeight) 
                : sc(FConstants::FInputLine::SmallHeight);

    _qssHelper.setProperty("QLineEdit", "font-family", Comm::fontFmaily)
            .setProperty("QLineEdit", "font-size", fontSize)
            .setProperty("QLineEdit", "color", FColor::regularText())
            .setProperty("QLineEdit", "background", FColor::baseBackground())
            .setProperty("QLineEdit", "border-radius", QString::number(FConstants::FInputLine::BorderRadius) + "px")
            .setProperty("QLineEdit", "border", "1px solid " + FColor::baseBorder())
            .setProperty("QLineEdit", "padding", QString::number(FConstants::FInputLine::PaddingVertical) + "px " + QString::number(FConstants::FInputLine::PaddingHorizontal) + "px")
            .setProperty("QLineEdit:hover", "border", "1px solid " + FColor::disabledText())
            .setProperty("QLineEdit:focus", "border", "1px solid " + FColor::primary())
            .setProperty("QLineEdit:disabled", "border", "1px solid " + FColor::lightBorder())
            .setProperty("QLineEdit:disabled", "background", FColor::lightFill())
            .setProperty("QLineEdit:disabled", "color", FColor::placeholderText());
    setStyleSheet(_qssHelper.generate());

    setFixedHeight(height);
    adjustSize();

    return *this;
}

FIcon::Name FInputLine::getSuffixIcon()
{
    return _suffixIcon;
}

FInputLine& FInputLine::setSuffixIcon(FIcon::Name icon)
{
    if (!_suffixAction)
        return setSuffixIcon(icon, []{});

    _suffixAction->setIcon(
        FIcon::instance().getIcon(icon, FColor::placeholderText(), FConstants::FInputLine::IconSize));
    _suffixIcon = icon;

    return *this;
}

FInputLine& FInputLine::setSuffixIcon(FIcon::Name icon, const std::function<void()>& callback)
{
    if (FIcon::isNone(icon))
    {
        if (_suffixAction)
        {
            removeAction(_suffixAction);
            _suffixAction->deleteLater();
            _suffixAction = nullptr;
        }
    }
    else
    {
        if (_suffixAction)
            setSuffixIcon(FIcon::None);

        _suffixAction = new QAction(
            FIcon::instance().getIcon(icon, FColor::placeholderText(), FConstants::FInputLine::IconSize),
            "", this);
        connect(_suffixAction, &QAction::triggered, callback);
        addAction(_suffixAction, QLineEdit::TrailingPosition);
    }

    _suffixIcon = icon;
    return *this;
}

FIcon::Name FInputLine::getPrefixIcon()
{
    return _prefixIcon;
}

FInputLine& FInputLine::setPrefixIcon(FIcon::Name icon)
{
    if (!_prefixAction)
        return setPrefixIcon(icon, []{});

    _prefixAction->setIcon(
        FIcon::instance().getIcon(icon, FColor::placeholderText(), FConstants::FInputLine::IconSize));
    _prefixIcon = icon;

    return *this;
}

FInputLine& FInputLine::setPrefixIcon(FIcon::Name icon, const std::function<void()>& callback)
{
    if (FIcon::isNone(icon))
    {
        if (_prefixAction)
        {
            removeAction(_prefixAction);
            _prefixAction->deleteLater();
            _prefixAction = nullptr;
        }
    }
    else
    {
        if (_prefixAction)
            setPrefixIcon(FIcon::None);

        _prefixAction = new QAction(
                    FIcon::instance().getIcon(icon, FColor::placeholderText(), FConstants::FInputLine::IconSize),
                    "", this);
        connect(_prefixAction, &QAction::triggered, callback);
        addAction(_prefixAction, QLineEdit::LeadingPosition);
    }

    _prefixIcon = icon;
    return *this;
}

int FInputLine::getMaxLength()
{
    return _maxLength;
}

FInputLine& FInputLine::setMaxLength(int maxLength)
{
    _maxLength = maxLength;
    QLineEdit::setMaxLength(_maxLength);

    if (maxLength <= 0)
    {
        if (_maxLengthLabel)
        {
            _maxLengthLabel->deleteLater();
            _maxLengthLabel = nullptr;
        }
    }
    else
    {
        if (!_maxLengthLabel)
        {
            _maxLengthLabel = new QLabel(this);
            QSSHelper qssHelper;
            qssHelper.setProperty("QLabel", "font-family", Comm::fontFmaily)
                    .setProperty("QLabel", "font-size", "14px")
                    .setProperty("QLabel", "color", FColor::secondaryText())
                    .setProperty("QLabel", "background", FColor::baseBackground());
            _maxLengthLabel->setStyleSheet(qssHelper.generate());
        }

        QString labelText = QString(FConstants::FCommon::MaxLengthLabelPrefix) + QString::number(_maxLength);
        _maxLengthLabel->setText(labelText);

        int textWidth = FontHelper(_maxLengthLabel->font()).getTextWidth(labelText);
        int textHeight = FontHelper(_maxLengthLabel->font()).getTextHeight();

        int inputWidth = width();
        int inputHeight = height();

        int labelWidth = textWidth + FConstants::FInputLine::MaxLengthLabelExtraWidth;
        int labelHeight = textHeight;
        int rightMargin = FConstants::FInputLine::MaxLengthLabelRightMargin;
        int x = inputWidth - labelWidth - rightMargin;
        int y = static_cast<int>((inputHeight - labelHeight) / FConstants::FCommon::VerticalCenterDivisor);

        _maxLengthLabel->setGeometry(x, y, labelWidth, labelHeight);
        _maxLengthLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        QMargins margins = textMargins();
        margins.setRight(inputWidth - x);
        setTextMargins(margins);
    }

    return *this;
}

bool FInputLine::getClearable()
{
    return _clearable;
}

FInputLine& FInputLine::setClearable(bool clearable)
{
    _clearable = clearable;
    clearableChecker();
    return *this;
}

bool FInputLine::getShowPassword()
{
    return _showPassword;
}

FInputLine& FInputLine::setShowPassword(bool showPassword)
{
    _showPassword = showPassword;
    showPasswordChecker();
    return *this;
}

bool FInputLine::getReadOnly()
{
    return QLineEdit::isReadOnly();
}

FInputLine& FInputLine::setReadOnly(bool readOnly)
{
    QLineEdit::setReadOnly(readOnly);
    return *this;
}

FInputLine& FInputLine::setAutoFocus()
{
    setFocus();
    return *this;
}

void FInputLine::onTextChanged(const QString&)
{
    if (_maxLength > 0)
        maxLengthChecker();
}

void FInputLine::clearableChecker()
{
    if (!_clearable)
    {
        // 如果目前 suffix 是清除按鈕，移除它（避免覆蓋其他 suffix）
        if (_suffixIcon == FIcon::CircleClose)
            setSuffixIcon(FIcon::None);
        return;
    }

    // 需要有文字才顯示清除
    if (text().isEmpty())
    {
        if (_suffixIcon == FIcon::CircleClose)
            setSuffixIcon(FIcon::None);
        return;
    }

    setSuffixIcon(FIcon::CircleClose, [&]{
        setText("");
        clearableChecker();
    });
}

void FInputLine::showPasswordChecker()
{
    if (!_showPassword)
    {
        if (_suffixIcon == FIcon::View || _suffixIcon == FIcon::Hide)
            setSuffixIcon(FIcon::None);
        setEchoMode(EchoMode::Normal);
        return;
    }

    // 開啟密碼模式，並提供顯示/隱藏切換
    setEchoMode(EchoMode::Password);
    setSuffixIcon(FIcon::View, [&]{
        if (echoMode() == EchoMode::Password)
        {
            setEchoMode(EchoMode::Normal);
            setSuffixIcon(FIcon::Hide, [&]{
                setEchoMode(EchoMode::Password);
                showPasswordChecker();
            });
        }
        else
        {
            setEchoMode(EchoMode::Password);
            showPasswordChecker();
        }
    });
}

void FInputLine::maxLengthChecker()
{
    if (!_maxLengthLabel)
        return;

    QString tips;
    tips.reserve(FConstants::FInputLine::MaxLengthTipReserve);
    tips.append(QString::number(text().length()))
            .append(" / ")
            .append(QString::number(_maxLength));

    _maxLengthLabel->setText(tips);
}

void FInputLine::focusInEvent(QFocusEvent* event)
{
    QLineEdit::focusInEvent(event);
}

void FInputLine::focusOutEvent(QFocusEvent* event)
{
    QLineEdit::focusOutEvent(event);
}

void FInputLine::enterEvent(QEvent* event)
{
    if (!isEnabled())
        QApplication::setOverrideCursor(Qt::ForbiddenCursor);
    QLineEdit::enterEvent(event);
}

void FInputLine::leaveEvent(QEvent* event)
{
    if (!isEnabled())
        QApplication::restoreOverrideCursor();
    QLineEdit::leaveEvent(event);
}

void FInputLine::mouseMoveEvent(QMouseEvent* event)
{
    int w = width();
    int h = height();
    QRect prefixRect(FConstants::FInputLine::IconAreaMargin, FConstants::FInputLine::IconAreaMargin, 
                    h - FConstants::FInputLine::IconAreaMarginFromHeight, h - FConstants::FInputLine::IconAreaMarginFromHeight);
    QRect suffixRect(w - h + FConstants::FInputLine::IconAreaMargin, FConstants::FInputLine::IconAreaMargin, 
                    h - FConstants::FInputLine::IconAreaMarginFromHeight, h - FConstants::FInputLine::IconAreaMarginFromHeight);

    QPoint pos = event->pos();

    bool isPrefixVisible = _prefixAction && _prefixAction->isVisible();
    bool isSuffixVisible = _suffixAction && _suffixAction->isVisible();

    bool isPrefixHovered = prefixRect.contains(pos);
    bool isSuffixHovered = suffixRect.contains(pos);

    if (isPrefixVisible && isPrefixHovered != _isPrefixHovered)
    {
        _isPrefixHovered = isPrefixHovered;
        _prefixAction->setIcon(FIcon::instance().getIcon(
            _prefixIcon,
            isPrefixHovered ? FColor::secondaryText() : FColor::placeholderText(),
            FConstants::FInputLine::IconSize));

        if (isPrefixHovered)
            QApplication::setOverrideCursor(Qt::PointingHandCursor);
        else
            QApplication::restoreOverrideCursor();
    }

    if (isSuffixVisible && isSuffixHovered != _isSuffixHovered)
    {
        _isSuffixHovered = isSuffixHovered;
        _suffixAction->setIcon(FIcon::instance().getIcon(
            _suffixIcon,
            isSuffixHovered ? FColor::secondaryText() : FColor::placeholderText(),
            FConstants::FInputLine::IconSize));

        if (isSuffixHovered)
            QApplication::setOverrideCursor(Qt::PointingHandCursor);
        else
            QApplication::restoreOverrideCursor();
    }

    QLineEdit::mouseMoveEvent(event);
}

QString FInputLine::placeholderText()
{
    return QLineEdit::placeholderText();
}
