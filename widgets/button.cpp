#include "button.h"
#include "color.h"
#include "icon.h"
#include "private/utils.h"
#include "constants.h"

#include <QApplication>
#include <QPair>

FButton::FButton(QWidget* parent)
        : QPushButton(parent)
    {
        QPalette palette = this->palette();
        palette.setColor(QPalette::ButtonText, FColor::regularText());

        _qsshelper = QString(R"(
             QPushButton {
                 padding: )" + QString::number(FConstants::FButton::DefaultPaddingVertical) + "px " + 
                 QString::number(FConstants::FButton::DefaultPaddingHorizontal) + R"(px;
                 font-size: )" + QString::number(FConstants::FButton::DefaultFontSize) + R"(px;
                 font-weight: bold;
             }
         )");
        _qsshelper.setProperty("QPushButton", "font-family", Comm::fontFmaily);
        setStyleSheet(_qsshelper.generate());

        setStyle(FButton::Style::Default);
        setType(FButton::Type::Default);
        setSize(FButton::Size::Default);

        setCursor(Qt::PointingHandCursor);
    }

FButton::FButton(const QString& text, QWidget* parent)
        : FButton(parent)
    {
        QPushButton::setText(text);
    }

FButton::Style FButton::getStyle()
    {
        return _style;
    }

FButton& FButton::setStyle(Style style)
    {
        _style = style;

        if (style == Style::Default)
        {
            _qsshelper.setProperty("QPushButton", "border-radius", QString::number(FConstants::FButton::DefaultBorderRadius) + "px");
            _qsshelper.setProperty("QPushButton", "border", "1px solid");
            _qsshelper.setProperty("QPushButton", "color", FColor::regularText());
        }
        else if (style == Style::Plain)
        {
            ;
        }
        else if (style == Style::Round)
        {
            _qsshelper.setProperty("QPushButton", "border-radius", QString::number(FConstants::FButton::RoundBorderRadius) + "px");
        }
        else if (style == Style::Circle)
        {
            _qsshelper.setProperty("QPushButton", "border-radius", QString::number(FConstants::FButton::RoundBorderRadius) + "px");
            _qsshelper.setProperty("QPushButton", "padding", QString::number(FConstants::FButton::CirclePadding) + "px");

            setMinimumSize(FConstants::FButton::CircleSize, FConstants::FButton::CircleSize);
            setMaximumSize(FConstants::FButton::CircleSize, FConstants::FButton::CircleSize);
        }
        else if (style == Style::Link)
        {
            _qsshelper.setProperty("QPushButton", "padding", "0px");
            _qsshelper.setProperty("QPushButton", "border", "none");
            _qsshelper.setProperty("QPushButton", "background", "transparent");
            _qsshelper.setProperty("QPushButton:hover", "border", "none");
            _qsshelper.setProperty("QPushButton:hover", "background", "transparent");
            _qsshelper.setProperty("QPushButton:hover", "text-decoration", "underline");
        }
        else if (style == Style::Text)
        {
            _qsshelper.setProperty("QPushButton", "border", "none");
            _qsshelper.setProperty("QPushButton:hover", "background", FColor::lightFill());
            _qsshelper.setProperty("QPushButton:pressed", "background", FColor::pageBackground());
        }

        QPushButton::setStyleSheet(_qsshelper.generate());
        return *this;
    }

FButton::Type FButton::getType()
    {
        return _type;
    }

FButton& FButton::setType(Type type)
    {
        _type = type;

        if (_style == Style::Default)
        {
            if (_type == Type::Default)
            {
                _qsshelper.setProperty("QPushButton", "background-color", FColor::baseBackground());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + FColor::baseBorder());
                _qsshelper.setProperty("QPushButton", "color", FColor::regularText());
                _qsshelper.setProperty("QPushButton:hover", "background-color", FColor::primaryL5());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + FColor::primaryL3());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::primary());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + FColor::primary());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", FColor::baseBackground());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + FColor::lightBorder());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::placeholderText());
            }
            else if (_type == Type::Primary)
            {
                _qsshelper.setProperty("QPushButton", "background-color", FColor::primary());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + FColor::primary());
                _qsshelper.setProperty("QPushButton", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", FColor::primaryL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + FColor::primaryL1());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", FColor::primaryD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + FColor::primaryD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", FColor::primaryL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + FColor::primaryL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::blankFill());
            }
            else if (_type == Type::Success)
            {
                _qsshelper.setProperty("QPushButton", "background-color", FColor::success());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + FColor::success());
                _qsshelper.setProperty("QPushButton", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", FColor::successL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + FColor::successL1());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", FColor::successD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + FColor::successD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", FColor::successL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + FColor::successL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::blankFill());
            }
            else if (_type == Type::Info)
            {
                _qsshelper.setProperty("QPushButton", "background-color", FColor::info());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + FColor::info());
                _qsshelper.setProperty("QPushButton", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", FColor::infoL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + FColor::infoL1());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", FColor::infoD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + FColor::infoD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", FColor::infoL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + FColor::infoL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::blankFill());
            }
            else if (_type == Type::Warning)
            {
                _qsshelper.setProperty("QPushButton", "background-color", FColor::warning());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + FColor::warning());
                _qsshelper.setProperty("QPushButton", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", FColor::warningL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + FColor::warningL1());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", FColor::warningD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + FColor::warningD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", FColor::warningL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + FColor::warningL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::blankFill());
            }
            else if (_type == Type::Danger)
            {
                _qsshelper.setProperty("QPushButton", "background-color", FColor::danger());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + FColor::danger());
                _qsshelper.setProperty("QPushButton", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", FColor::dangerL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + FColor::dangerL1());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", FColor::dangerD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + FColor::dangerD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", FColor::dangerL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + FColor::dangerL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::blankFill());
            }
        }
        else if (_style == Style::Plain)
        {
            if (_type == Type::Default)
            {
                _qsshelper.setProperty("QPushButton", "background-color", FColor::baseBackground());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + FColor::baseBorder());
                _qsshelper.setProperty("QPushButton", "color", FColor::regularText());
                _qsshelper.setProperty("QPushButton:hover", "background-color", FColor::baseBackground());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + FColor::primary());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::primary());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", FColor::baseBackground());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + FColor::primary());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::primary());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", FColor::baseBackground());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + FColor::lightBorder());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::placeholderText());
            }
            else if (_type == Type::Primary)
            {
                _qsshelper.setProperty("QPushButton", "background-color", FColor::primaryL5());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + FColor::primaryL2());
                _qsshelper.setProperty("QPushButton", "color", FColor::primary());
                _qsshelper.setProperty("QPushButton:hover", "background-color", FColor::primary());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + FColor::primary());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", FColor::primaryD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + FColor::primaryD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", FColor::primaryL5());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + FColor::primaryL4());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::primaryL2());
            }
            else if (_type == Type::Success)
            {
                _qsshelper.setProperty("QPushButton", "background-color", FColor::successL5());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + FColor::successL2());
                _qsshelper.setProperty("QPushButton", "color", FColor::success());
                _qsshelper.setProperty("QPushButton:hover", "background-color", FColor::success());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + FColor::success());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", FColor::successD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + FColor::successD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", FColor::successL5());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + FColor::successL4());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::successL2());
            }
            else if (_type == Type::Info)
            {
                _qsshelper.setProperty("QPushButton", "background-color", FColor::infoL5());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + FColor::infoL2());
                _qsshelper.setProperty("QPushButton", "color", FColor::info());
                _qsshelper.setProperty("QPushButton:hover", "background-color", FColor::info());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + FColor::info());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", FColor::infoD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + FColor::infoD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", FColor::infoL5());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + FColor::infoL4());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::infoL2());
            }
            else if (_type == Type::Warning)
            {
                _qsshelper.setProperty("QPushButton", "background-color", FColor::warningL5());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + FColor::warningL2());
                _qsshelper.setProperty("QPushButton", "color", FColor::warning());
                _qsshelper.setProperty("QPushButton:hover", "background-color", FColor::warning());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + FColor::warning());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", FColor::warningD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + FColor::warningD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", FColor::warningL5());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + FColor::warningL4());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::warningL2());
            }
            else if (_type == Type::Danger)
            {
                _qsshelper.setProperty("QPushButton", "background-color", FColor::dangerL5());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + FColor::dangerL2());
                _qsshelper.setProperty("QPushButton", "color", FColor::danger());
                _qsshelper.setProperty("QPushButton:hover", "background-color", FColor::danger());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + FColor::danger());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", FColor::dangerD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + FColor::dangerD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", FColor::dangerL5());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + FColor::dangerL4());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::dangerL2());
            }
        }
        else if (_style == Style::Round || _style == Style::Circle)
        {
            if (_type == Type::Default)
            {
                _qsshelper.setProperty("QPushButton", "background-color", FColor::baseBackground());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + FColor::baseBorder());
                _qsshelper.setProperty("QPushButton", "color", FColor::regularText());
                _qsshelper.setProperty("QPushButton:hover", "background-color", FColor::primaryL5());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + FColor::primaryL3());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::primary());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", FColor::primaryL5());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + FColor::primary());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::primary());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", FColor::baseBackground());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + FColor::lightBorder());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::placeholderText());
            }
            else if (_type == Type::Primary)
            {
                _qsshelper.setProperty("QPushButton", "background-color", FColor::primary());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + FColor::primary());
                _qsshelper.setProperty("QPushButton", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", FColor::primaryL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + FColor::primaryL1());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", FColor::primaryD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + FColor::primaryD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", FColor::primaryL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + FColor::primaryL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::blankFill());
            }
            else if (_type == Type::Success)
            {
                _qsshelper.setProperty("QPushButton", "background-color", FColor::success());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + FColor::success());
                _qsshelper.setProperty("QPushButton", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", FColor::successL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + FColor::successL1());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", FColor::successD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + FColor::successD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", FColor::successL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + FColor::successL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::blankFill());
            }
            else if (_type == Type::Info)
            {
                _qsshelper.setProperty("QPushButton", "background-color", FColor::info());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + FColor::info());
                _qsshelper.setProperty("QPushButton", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", FColor::infoL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + FColor::infoL1());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", FColor::infoD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + FColor::infoD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", FColor::infoL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + FColor::infoL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::blankFill());
            }
            else if (_type == Type::Warning)
            {
                _qsshelper.setProperty("QPushButton", "background-color", FColor::warning());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + FColor::warning());
                _qsshelper.setProperty("QPushButton", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", FColor::warningL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + FColor::warningL1());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", FColor::warningD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + FColor::warningD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", FColor::warningL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + FColor::warningL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::blankFill());
            }
            else if (_type == Type::Danger)
            {
                _qsshelper.setProperty("QPushButton", "background-color", FColor::danger());
                _qsshelper.setProperty("QPushButton", "border", "1px solid " + FColor::danger());
                _qsshelper.setProperty("QPushButton", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:hover", "background-color", FColor::dangerL1());
                _qsshelper.setProperty("QPushButton:hover", "border", "1px solid " + FColor::dangerL1());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:pressed", "background-color", FColor::dangerD1());
                _qsshelper.setProperty("QPushButton:pressed", "border", "1px solid " + FColor::dangerD1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::blankFill());
                _qsshelper.setProperty("QPushButton:disabled", "background-color", FColor::dangerL2());
                _qsshelper.setProperty("QPushButton:disabled", "border", "1px solid " + FColor::dangerL2());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::blankFill());
            }
        }
        else if (_style == Style::Link)
        {
            _qsshelper.clearGroup("QPushButton:pressed");

            if (_type == Type::Default)
            {
                _qsshelper.setProperty("QPushButton", "color", FColor::regularText());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::secondaryText());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::primaryText());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::placeholderText());
            }
            else if (_type == Type::Primary)
            {
                _qsshelper.setProperty("QPushButton", "color", FColor::primary());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::primaryL1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::primaryD1());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::primaryL2());
            }
            else if (_type == Type::Success)
            {
                _qsshelper.setProperty("QPushButton", "color", FColor::success());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::successL1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::successD1());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::successL2());
            }
            else if (_type == Type::Info)
            {
                _qsshelper.setProperty("QPushButton", "color", FColor::info());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::infoL1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::infoD1());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::infoL2());
            }
            else if (_type == Type::Warning)
            {
                _qsshelper.setProperty("QPushButton", "color", FColor::warning());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::warningL1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::warningD1());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::warningL2());
            }
            else if (_type == Type::Danger)
            {
                _qsshelper.setProperty("QPushButton", "color", FColor::danger());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::dangerL1());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::dangerD1());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::dangerL2());
            }
        }
        else if (_style == Style::Text)
        {
            _qsshelper.setProperty("QPushButton:hover", "border", "none");
            _qsshelper.setProperty("QPushButton:pressed", "border", "none");

            if (_type == Type::Default)
            {
                _qsshelper.setProperty("QPushButton", "color", FColor::regularText());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::regularText());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::regularText());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::placeholderText());
            }
            else if (_type == Type::Primary)
            {
                _qsshelper.setProperty("QPushButton", "color", FColor::primary());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::primary());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::primary());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::primaryL2());
            }
            else if (_type == Type::Success)
            {
                _qsshelper.setProperty("QPushButton", "color", FColor::success());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::success());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::success());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::successL2());
            }
            else if (_type == Type::Info)
            {
                _qsshelper.setProperty("QPushButton", "color", FColor::info());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::info());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::info());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::infoL2());
            }
            else if (_type == Type::Warning)
            {
                _qsshelper.setProperty("QPushButton", "color", FColor::warning());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::warning());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::warning());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::warningL2());
            }
            else if (_type == Type::Danger)
            {
                _qsshelper.setProperty("QPushButton", "color", FColor::danger());
                _qsshelper.setProperty("QPushButton:hover", "color", FColor::danger());
                _qsshelper.setProperty("QPushButton:pressed", "color", FColor::danger());
                _qsshelper.setProperty("QPushButton:disabled", "color", FColor::dangerL2());
            }
        }

        QPushButton::setStyleSheet(_qsshelper.generate());
        return *this;
    }

FButton::Size FButton::getSize()
    {
        return _size;
    }

FButton& FButton::setSize(FButton::Size size)
    {
        _size = size;

        if (_size == Size::Large)
        {
            _qsshelper.setProperty("QPushButton", "padding", 
                QString::number(FConstants::FButton::LargePaddingVertical) + "px " + 
                QString::number(FConstants::FButton::LargePaddingHorizontal) + "px");

            setMinimumHeight(sc(FConstants::FButton::LargeHeight));
        }
        else if (_size == Size::Small)
        {
            _qsshelper.setProperty("QPushButton", "border-radius", QString::number(FConstants::FButton::SmallBorderRadius) + "px");
            _qsshelper.setProperty("QPushButton", "padding", 
                QString::number(FConstants::FButton::SmallPaddingVertical) + "px " + 
                QString::number(FConstants::FButton::SmallPaddingHorizontal) + "px");
            _qsshelper.setProperty("QPushButton", "font-size", QString::number(FConstants::FButton::SmallFontSize) + "px");

            if (!FIcon::isNone(_icon))
                QPushButton::setIconSize(QSize(FConstants::FButton::SmallIconSize, FConstants::FButton::SmallIconSize));

            setMinimumHeight(sc(FConstants::FButton::SmallHeight));
        }
        else if (_size == Size::Default)
        {
            setMinimumHeight(sc(FConstants::FButton::DefaultHeight));
        }

        QPushButton::setStyleSheet(_qsshelper.generate());
        return *this;
    }


bool FButton::isDisabled()
    {
        return !QPushButton::isEnabled();
    }

FButton& FButton::setDisabled(bool disabled)
    {
        QPushButton::setDisabled(disabled);
        return *this;
    }

bool FButton::isLoading()
    {
        return _loading;
    }

FButton& FButton::setLoading(bool loading)
    {
        _loading = loading;
        return *this;
    }

QPair<FIcon::Name, FButton::IconPosition> FButton::getIcon()
    {
        return QPair<FIcon::Name, IconPosition>(_icon, _iconPostion);
    }

FButton& FButton::setIcon(FIcon::Name name, IconPosition pos)
    {
        _icon = name;
        _iconPostion = pos;

        int iconSize = (_size == Size::Small) ? FConstants::FButton::SmallIconSize : FConstants::FButton::DefaultIconSize;
        
        if (_type == Type::Default)
        {
            QIcon icon = FIcon::instance().getIcon(name, FColor::regularText(), iconSize);
            QPushButton::setIcon(icon);
            QPushButton::setIconSize(QSize(iconSize, iconSize));
        }
        else
        {
            QIcon icon = FIcon::instance().getIcon(name, FColor::blankFill(), iconSize);
            QPushButton::setIcon(icon);
            QPushButton::setIconSize(QSize(iconSize, iconSize));
        }

        if (pos == IconPosition::Only)
        {
            QPushButton::setText("");
        }
        else if (pos == IconPosition::Left)
        {
            ;
        }
        else if (pos == IconPosition::Right)
        {
            QPushButton::setLayoutDirection(Qt::RightToLeft);
        }

        adjustSize();
        return *this;
    }

FButton& FButton::setText(const QString& text)
    {
        QPushButton::setText(text);

        adjustSize();
        return *this;
    }


void FButton::enterEvent(QEvent *event)
    {
        if (!isEnabled())
            QApplication::setOverrideCursor(Qt::ForbiddenCursor);
        QPushButton::enterEvent(event);
    }

void FButton::leaveEvent(QEvent *event)
    {
        QApplication::restoreOverrideCursor();
        QPushButton::leaveEvent(event);
    }
