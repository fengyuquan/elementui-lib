#pragma once

#include "inputline.h"
#include "private/utils.h"
#include "constants.h"

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QTimer>

// Forward declarations
class FOptionList;

class FSelect : public FInputLine
{
        Q_OBJECT

public:
    enum class Placement { Top, Bottom };

public:
    FSelect& setOptions(const QStringList& options);
    FSelect& setPlacement(Placement placement);

    FSelect& addItem(const QString& text);
    FSelect& addItems(const QStringList& texts);

public:
    FSelect(QWidget* parent = nullptr);
    FSelect(const QStringList& data, QWidget* parent = nullptr);

protected:
    void focusOutEvent(QFocusEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* e) override;
    void resizeEvent(QResizeEvent* event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QStringList _options;
    Placement _placement = Placement::Bottom;

private:
    FOptionList* _popList = nullptr;
};

class FOptionListItemWidget : public QWidget
{
        Q_OBJECT

public:
    FOptionListItemWidget(const QString& text, QWidget* parent = nullptr);
    QLabel* getLabel();

signals:
    void clicked(const QString& text);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    QLabel* _label = nullptr;
    QSSHelper _qsshelper;
};

class FOptionList : public QListWidget
{
        Q_OBJECT
public:
    enum class Placement { Top, Bottom };

public:
    void addItem(const QString& text);
    void addItems(const QStringList& texts);
    void setItems(const QStringList& texts);
    void filterItems(const QString& text);

public:
    void show();

public:
    FOptionList(Placement placement,
               FSelect* input = nullptr,
               QWidget* parent = nullptr);
    FOptionList(int width,
               Placement placement,
               FSelect* input = nullptr,
               QWidget* parent = nullptr);
    FOptionList(int width,
               Placement placement,
               const QStringList& data,
               FSelect* input = nullptr,
               QWidget* parent = nullptr);
signals:
    void itemClicked(const QString& text);

protected:
    void showEvent(QShowEvent* event) override;

public:
    void updateHeight(int count);
    void updateWidth();

private:
    Placement _placement;
    FSelect* _input = nullptr;

    QSSHelper _qsshelper;
};
