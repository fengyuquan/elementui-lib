#pragma once

#include "private/utils.h"
#include "icon.h"
#include "constants.h"

#include <QLineEdit>
#include <QLabel>

#include <functional>

class FInputLine : public QLineEdit
{
Q_OBJECT

public:
    enum class Size
    {
        Large = 0,
        Default,
        Small,
    };

public:
    QString getPlaceholder();
    FInputLine& setPlaceholder(const QString& placeholder);

    int getWidth();
    FInputLine& setWidth(int width);

    bool isDisabled();
    FInputLine& setDisabled(bool disabled);

    Size getSize();
    FInputLine& setSize(Size size);

    FIcon::Name getSuffixIcon();
    FInputLine& setSuffixIcon(FIcon::Name icon);
    FInputLine& setSuffixIcon(FIcon::Name icon, const std::function<void()>& callback);

    FIcon::Name getPrefixIcon();
    FInputLine& setPrefixIcon(FIcon::Name icon);
    FInputLine& setPrefixIcon(FIcon::Name icon, const std::function<void()>& callback);

    int getMaxLength();
    FInputLine& setMaxLength(int maxLength);

    bool getClearable();
    FInputLine& setClearable(bool clearable);

    bool getShowPassword();
    FInputLine& setShowPassword(bool showPassword);

    bool getReadOnly();
    FInputLine& setReadOnly(bool readonly);

    FInputLine& setAutoFocus();

public:
    FInputLine(QWidget* parent = nullptr);
    FInputLine(const QString& placeholder, QWidget* parent = nullptr);

protected:
    void onTextChanged(const QString &text);

    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    void clearableChecker();
    void showPasswordChecker();
    void maxLengthChecker();
    QString placeholderText();

private:
    Size _size = Size::Default;

    FIcon::Name _suffixIcon = FIcon::None;
    FIcon::Name _prefixIcon = FIcon::None;

    bool _clearable = false;
    bool _showPassword = false;

    int _maxLength = 0;

private:
    QSSHelper _qssHelper;

    QAction* _prefixAction = nullptr;
    QAction* _suffixAction = nullptr;

    QLabel* _maxLengthLabel = nullptr;

    bool _isPrefixHovered = false;
bool _isSuffixHovered = false;
};
