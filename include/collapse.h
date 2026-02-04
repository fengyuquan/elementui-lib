#pragma once

#include "icon.h"
#include "private/utils.h"

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>

class FCollapseItem : public QWidget
{
    Q_OBJECT

public:
    enum class IconPosition { Left, Right };
    enum class Status { Collapse, Expand };

public:
    FCollapseItem& setIconPosition(IconPosition position);
    FCollapseItem& setAllowCollapse(bool allow);
    FCollapseItem& setCollapse();
    FCollapseItem& setExpand();
    FCollapseItem& toggleStatus();

    FCollapseItem& setTitle(const QString& title);
    FCollapseItem& setContent(const QString& content);
    FCollapseItem& setIcon(FIcon::Name collapsedIcon, FIcon::Name expandIcon);
    FCollapseItem& setDisabled(bool disabled);

    FCollapseItem& setWidth(int width);
    FCollapseItem& setLast(bool isLast);

public:
    FCollapseItem(QWidget* parent = nullptr);
    FCollapseItem(const QString& title, const QString& content, QWidget* parent = nullptr);
    FCollapseItem(const QString& title, const QString& content, Status status = Status::Collapse, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    IconPosition _iconPosition = IconPosition::Right;
    Status _status = Status::Collapse;
    FIcon::Name _collapsedIcon = FIcon::ArrowRight;
    FIcon::Name _expandIcon = FIcon::ArrowDown;
    bool _allowCollapse = true;

private:
    QLabel* _title = nullptr;
    QLabel* _content = nullptr;
    QLabel* _icon = nullptr;
    QHBoxLayout* _titleLayout = nullptr;
    QVBoxLayout* _mainlayout = nullptr;

private:
    bool _last = false;
};

class FCollapse : public QWidget
{
    Q_OBJECT

public:
    using Item = FCollapseItem;

public:
    FCollapse& setAccordion(bool accordion);
    FCollapse& setIcon(FIcon::Name collapsedIcon, FIcon::Name expandIcon);
    FCollapse& setCollapse(int index);
    FCollapse& setExpand(int index);
    FCollapse& setIconPosition(Item::IconPosition position);
    FCollapse& toggleStatus(int index);

    FCollapse& addItem(FCollapseItem* item);
    FCollapse& delItem(int index);

    FCollapse& setWidth(int width);

public:
    FCollapse(QWidget* parent = nullptr);

private:
    bool _accordion = false;

private:
    QList<FCollapseItem*> _items;
};


