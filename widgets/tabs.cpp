#include "tabs.h"
#include "color.h"
#include "private/utils.h"
#include "qcolor.h"
#include "qglobal.h"
#include "qline.h"
#include "qnamespace.h"
#include "qpaintdevice.h"
#include "qpainter.h"
#include "constants.h"

#include <QStylePainter>
#include <QStyleOptionTab>
#include <QPainterPath>

FTabs::FTabs(QWidget* parent)
    : FTabs(Type::Default, TabPosition::Top, parent)
{}

FTabs::FTabs(Type type, QWidget* parent)
    : FTabs(type, TabPosition::Top, parent)
{}

FTabs::FTabs(TabPosition position, QWidget* parent)
    : FTabs(Type::Default, position, parent)
{}

FTabs::FTabs(Type type, TabPosition position, QWidget* parent)
    : QTabWidget(parent)
    , _type(type)
    , _position(position)
    , _bar(new FTabBar(type, position, this))
{
    setType(_type);
    setTabPosition(_position);
    setTabBar(_bar);

    // setTabsClosable(_closable);
    // setMovable(_editable);
}

FTabs& FTabs::setType(Type type)
{
    _type = type;
    _bar->setType(type);
    return *this;
}

FTabs& FTabs::setTabPosition(TabPosition pos)
{
    _position = pos;
    QTabWidget::setTabPosition(
        pos == TabPosition::Top    ? QTabWidget::North :
        pos == TabPosition::Bottom ? QTabWidget::South :
        pos == TabPosition::Left   ? QTabWidget::West : QTabWidget::East);

    _bar->setTabPosition(pos);
    return *this;
}

FTabs& FTabs::setCloseable(bool closable)
{
    _closable = closable;
    setTabsClosable(closable);
    return *this;
}

FTabs& FTabs::setAddable(bool addable)
{
    _addable = addable;
    return *this;
}

FTabs& FTabs::setEditable(bool editable)
{
    _editable = editable;
    setMovable(editable);
    return *this;
}

FTabs& FTabs::setStretch(bool stretch)
{
    _stretch = stretch;
    _bar->setExpanding(_stretch);
    return *this;
}

QHash<int, int>& FTabs::getTabWidths()
{
    return _tabWidths;
}

void FTabs::paintEvent(QPaintEvent*)
{
    switch (_type)
    {
        case Type::Default: paintDefaultStyle(); break;
        case Type::Card: paintCardStyle(); break;
        case Type::BorderCard: paintBorderCardStyle(); break;
    }
}

void FTabs::paintDefaultStyle()
{
    QStylePainter painter(this);

    // 绘制分割线
    QRect lineRect = _position == TabPosition::Top    ? QRect(0, _bar->height(), width(), FConstants::FTabs::DividerHeight) :
                     _position == TabPosition::Bottom ? QRect(0, height() - _bar->height() - FConstants::FTabs::DividerHeight, width(), FConstants::FTabs::DividerHeight) :
                     _position == TabPosition::Left   ? QRect(_bar->width(), 0, FConstants::FTabs::DividerHeight, height()) :
                                                        QRect(width() - _bar->width() - FConstants::FTabs::DividerHeight, 0, FConstants::FTabs::DividerHeight, height());
    painter.fillRect(lineRect, FColor::lightBorder());

    // 绘制选中标签蓝色线段
    int cur = currentIndex();
    if (cur >= 0)
    {
        QRect tabR = _bar->tabRect(cur);
        QRect selLine = lineRect;

        if (_position == TabPosition::Top || _position == TabPosition::Bottom)
        {
            selLine.setLeft(tabR.left());
            selLine.setWidth(tabR.width() - FConstants::FTabs::SelectedLineOffset);
        }
        else
        {
            selLine.setTop(tabR.top());
            selLine.setHeight(tabR.height());
        }

        painter.fillRect(selLine, FColor::primary());
    }
}

void FTabs::paintCardStyle()
{
    QStylePainter painter(this);

    if (_position == TabPosition::Top)
    {
        QRect lineRect = QRect(0, _bar->height() - 1, width(), FConstants::FTabs::CardBorderHeight);
        painter.fillRect(lineRect, FColor::lightBorder());
    }
    else if (_position == TabPosition::Bottom)
    {
        QRect lineRect = QRect(0, height() - _bar->height() - 1, width(), FConstants::FTabs::CardBorderHeight);
        painter.fillRect(lineRect, FColor::lightBorder());
    }
}

void FTabs::paintBorderCardStyle()
{
    QStylePainter painter(this);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(FColor::baseBorder());
    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    if (_position == TabPosition::Top)
    {
        QRect tabRect = QRect(1, 1, width() - 2, _bar->height() - 2);
        painter.fillRect(tabRect, FColor::lightFill());
        QLine line = QLine(0, _bar->height() - 1, width(), _bar->height() - 1);
        painter.drawLine(line);
    }
    else if (_position == TabPosition::Bottom)
    {
        QLine line = QLine(0, height() - _bar->height() - 1, width(), height() - _bar->height() - 1);
        painter.drawLine(line);
    }
}


FTabBar::FTabBar(FTabs::Type type, FTabs::TabPosition pos, FTabs* tabs, QWidget* parent)
    : QTabBar(parent)
    , _tabs(tabs)
{
    setType(type);
    setTabPosition(pos);
    setFont(FontHelper().setPointSize(FConstants::FTabs::TabFontSize).getFont());
    setStyleSheet("QTabBar {background: transparent; border: none;}");

    setExpanding(false);
    setTabsClosable(false);
    setUsesScrollButtons(false);
}

void FTabBar::setType(FTabs::Type type)
{
    _type = type;
}

void FTabBar::setTabPosition(FTabs::TabPosition pos)
{
    _position = pos;
}

void FTabBar::paintEvent(QPaintEvent*)
{
    switch (_type)
    {
        case FTabs::Type::Default: paintDefaultStyle(); break;
        case FTabs::Type::Card:
            paintCardStyle();
            break;
        case FTabs::Type::BorderCard: paintBorderCardStyle(); break;
    }
}

QSize FTabBar::tabSizeHint(int i) const
{
    auto& tabWidths = _tabs->getTabWidths();

    if (!tabWidths.contains(i))
    {
        int textWidth = FontHelper(font()).getTextWidth(tabText(i));
        tabWidths[i] = qMax(FConstants::FTabs::MinTabWidth, textWidth + 2 * FConstants::FTabs::TabPaddingHorizontal);
    }

    return QSize(tabWidths[i], FConstants::FTabs::TabHeight);
}

void FTabBar::paintDefaultStyle()
{
    drawTextDefaultStyle();
}

void FTabBar::paintCardStyle()
{
    QStylePainter painter(this);

    for (int i = 0; i < count(); ++i)
    {
        QRect rect = tabRect(i);

        painter.setPen(QPen(QColor(FColor::lightBorder()), 1));
        painter.setBrush(Qt::NoBrush);

        const int radius = FConstants::FTabs::CardBorderRadius;
        if (i == 0)
        {
            QPainterPath path;
            path.moveTo(rect.left() + radius, rect.top());
            path.lineTo(rect.right() + 1, rect.top());
            path.lineTo(rect.right() + 1, rect.bottom() + 1);
            path.lineTo(rect.left(), rect.bottom());
            path.arcTo(rect.left(), rect.top(), radius * 2, radius * 2, 180, -90);
            path.closeSubpath();
            painter.drawPath(path);
        }
        else if (i == count() - 1)
        {
            QPainterPath path;
            path.moveTo(rect.left(), rect.top());
            path.lineTo(rect.right() - radius, rect.top());
            path.arcTo(rect.right() - radius * 2, rect.top(), radius * 2, radius * 2, 90, -90);
            path.lineTo(rect.right(), rect.bottom());
            path.lineTo(rect.left(), rect.bottom());
            path.closeSubpath();
            painter.drawPath(path);
        }
        else
        {
            painter.drawLine(rect.topLeft(), rect.topRight());
            painter.drawLine(rect.topLeft(), rect.bottomLeft());
            painter.drawLine(rect.bottomLeft(), rect.bottomRight());
        }

        if (i == currentIndex())
        {
            painter.setPen(FColor::blankFill());
            painter.drawLine(rect.bottomLeft(), rect.bottomRight());
        }
    }

    drawTextCardStyle();
}

void FTabBar::paintBorderCardStyle()
{
    QStylePainter painter(this);

    painter.setPen(QPen(QColor(FColor::baseBorder()), 1));
    painter.setBrush(Qt::NoBrush);

    for (int i = 0; i < count(); ++i)
    {
        if (i == currentIndex())
        {
            QRect rect = tabRect(i);

            painter.fillRect(rect.adjusted(1, 1, -1, 0), QColor(FColor::blankFill()));
            painter.drawLine(rect.topLeft(), rect.bottomLeft());
            painter.drawLine(rect.topRight(), rect.bottomRight());
        }
    }

    drawTextCardStyle();
}

void FTabBar::drawTextDefaultStyle()
{
    QStylePainter painter(this);

    for (int i = 0; i < count(); ++i)
    {
        QStyleOptionTab opt;
        initStyleOption(&opt, i);

        bool selected = i == currentIndex();
        bool hovered = i == tabAt(mapFromGlobal(QCursor::pos()));

        opt.palette.setColor(QPalette::ButtonText,
                selected || hovered ? FColor::primary() : FColor::primaryText());
        painter.setPen(opt.palette.buttonText().color());

        QRect rect = tabRect(i);
        QRect textRect = _position == FTabs::TabPosition::Top    ? rect.adjusted(0, 0, 0, 0) :
                         _position == FTabs::TabPosition::Bottom ? rect.adjusted(0, 0, 0, 0) :
                         _position == FTabs::TabPosition::Left   ? rect.adjusted(0, 0, -FConstants::FTabs::VerticalTabTextOffset, 0) : rect.adjusted(FConstants::FTabs::VerticalTabTextOffset, 0, 0, 0);

        int align = _position == FTabs::TabPosition::Top    ? Qt::AlignVCenter | Qt::AlignLeft :
                    _position == FTabs::TabPosition::Bottom ? Qt::AlignVCenter | Qt::AlignLeft :
                    _position == FTabs::TabPosition::Left   ? Qt::AlignVCenter | Qt::AlignRight : Qt::AlignVCenter | Qt::AlignLeft;

        painter.drawText(textRect, align, tabText(i));
    }
}

void FTabBar::drawTextCardStyle()
{
    QStylePainter painter(this);

    for (int i = 0; i < count(); ++i)
    {
        QStyleOptionTab opt;
        initStyleOption(&opt, i);

        bool selected = i == currentIndex();
        bool hovered = i == tabAt(mapFromGlobal(QCursor::pos()));

        opt.palette.setColor(QPalette::ButtonText,
                selected || hovered ? FColor::primary() : FColor::primaryText());
        painter.setPen(opt.palette.buttonText().color());

        painter.drawText(tabRect(i), Qt::AlignCenter, tabText(i));
    }
}


