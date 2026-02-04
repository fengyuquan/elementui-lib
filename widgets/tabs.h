#pragma once

#include "qlist.h"
#include <QTabBar>
#include <QTabWidget>

class FTabBar;

class FTabs : public QTabWidget
{
    Q_OBJECT

public:
    enum class Type
    {
        Default,
        Card,
        BorderCard,
    };

    enum class TabPosition
    {
        Top,
        Bottom,
        Left,
        Right,
    };

public:
    FTabs& setType(Type type);
    FTabs& setTabPosition(TabPosition position);
    FTabs& setCloseable(bool closable);
    FTabs& setAddable(bool addable);
    FTabs& setEditable(bool editable);
    FTabs& setStretch(bool stretch);

public:
    QHash<int, int>& getTabWidths();

public:
    FTabs(QWidget* parent = nullptr);
    FTabs(Type type, QWidget* parent = nullptr);
    FTabs(TabPosition position, QWidget* parent = nullptr);
    FTabs(Type type, TabPosition position, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void paintDefaultStyle();
    void paintCardStyle();
    void paintBorderCardStyle();

private:
    Type _type = Type::Default;
    TabPosition _position = TabPosition::Top;

    bool _closable = false;
    bool _addable = false;
    bool _editable = false;
    bool _stretch = false;

private:
    FTabBar* _bar = nullptr;
    QHash<int, int> _tabWidths;
};

class FTabBar : public QTabBar
{
    Q_OBJECT

public:
    void setType(FTabs::Type type);
    void setTabPosition(FTabs::TabPosition pos);

public:
    FTabBar(FTabs::Type type, FTabs::TabPosition pos, FTabs* tabs, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    QSize tabSizeHint(int index) const override;

private:
    void paintDefaultStyle();
    void paintCardStyle();
    void paintBorderCardStyle();
    void drawTextDefaultStyle();
    void drawTextCardStyle();

private:
    FTabs::Type _type;
    FTabs::TabPosition _position;

private:
    FTabs* _tabs = nullptr;
};


