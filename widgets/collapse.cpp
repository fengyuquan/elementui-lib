#include "collapse.h"

#include "icon.h"
#include "color.h"
#include "private/utils.h"
#include "constants.h"

#include <QPainter>
#include <QMouseEvent>

FCollapseItem::FCollapseItem(QWidget* parent)
    : FCollapseItem("", "", Status::Collapse, parent)
{}

FCollapseItem::FCollapseItem(const QString& title, const QString& content, QWidget* parent)
    : FCollapseItem(title, content, Status::Collapse, parent)
{}

FCollapseItem::FCollapseItem(const QString& title, const QString& content, Status status, QWidget* parent)
    : QWidget(parent)
    , _status(status)
    , _title(new QLabel(title, this))
    , _content(new QLabel(content, this))
    , _icon(new QLabel(this))
{
    _title->setFont(FontHelper(_title->font())
            .setPointSize(FConstants::FCollapse::TitleFontSize)
            .setBold()
            .getFont());

    _content->setFont(FontHelper(_content->font())
            .setPointSize(FConstants::FCollapse::ContentFontSize)
            .getFont());

    _title->setFixedHeight(FConstants::FCollapse::TitleHeight);
    _icon->setFixedHeight(FConstants::FCollapse::TitleHeight);

    _content->setWordWrap(true);
    _icon->setPixmap(FIcon::instance().getPixmap(_collapsedIcon, FColor::primaryText(), FConstants::FCollapse::IconSize));

    _title->setStyleSheet("color: " + FColor::primaryText() + "; ");
    _content->setStyleSheet("color: " + FColor::primaryText() + "; ");

    _titleLayout = new QHBoxLayout;
    _titleLayout->setContentsMargins(0, 0, 0, 0);
    _titleLayout->setSpacing(0);
    _titleLayout->addWidget(_title);
    _titleLayout->addStretch();
    _titleLayout->addWidget(_icon);
    _titleLayout->addSpacing(FConstants::FCollapse::IconSpacing);

    _mainlayout = new QVBoxLayout(this);
    _mainlayout->setContentsMargins(0, 0, 0, 0);
    _mainlayout->setSpacing(0);
    _mainlayout->addLayout(_titleLayout);
    _mainlayout->addWidget(_content);

    setMouseTracking(true);
    _title->setMouseTracking(true);
    _icon->setMouseTracking(true);
    _content->setMouseTracking(true);

    if (_status == Status::Collapse)
        setCollapse();
    else
        setExpand();

    setFixedWidth(FConstants::FCollapse::DefaultWidth);
    adjustSize();
}

FCollapseItem& FCollapseItem::setIconPosition(IconPosition position)
{
    _iconPosition = position;

    if (_titleLayout)
    {
        QLayoutItem* item;
        while ((item = _titleLayout->takeAt(0)) != nullptr)
            delete item;

        if (_iconPosition == IconPosition::Left)
        {
            _titleLayout->addWidget(_icon);
            _titleLayout->addSpacing(FConstants::FCollapse::IconSpacing);
            _titleLayout->addWidget(_title);
            _titleLayout->addStretch();
        }
        else
        {
            _titleLayout->addWidget(_title);
            _titleLayout->addStretch();
            _titleLayout->addWidget(_icon);
            _titleLayout->addSpacing(FConstants::FCollapse::IconSpacing);
        }
    }

    return *this;
}

FCollapseItem& FCollapseItem::setAllowCollapse(bool allow)
{
    _allowCollapse = allow;
    return *this;
}

FCollapseItem& FCollapseItem::setCollapse()
{
    _status = Status::Collapse;

    _content->hide();
    _icon->setPixmap(FIcon::instance().getPixmap(_collapsedIcon, FColor::primaryText(), FConstants::FCollapse::IconSize));
    _mainlayout->setContentsMargins(0, 0, 0, 0);

    adjustSize();

    if (parentWidget())
        parentWidget()->adjustSize();

    return *this;
}

FCollapseItem& FCollapseItem::setExpand()
{
    _status = Status::Expand;

    _content->show();
    _icon->setPixmap(FIcon::instance().getPixmap(_expandIcon, FColor::primaryText(), FConstants::FCollapse::IconSize));
    _mainlayout->setContentsMargins(0, 0, 0, FConstants::FCollapse::ExpandMarginBottom);

    adjustSize();

    if (parentWidget())
        parentWidget()->adjustSize();

    return *this;
}

FCollapseItem& FCollapseItem::toggleStatus()
{
    if (_status == Status::Collapse)
        setExpand();
    else
        setCollapse();

    return *this;
}

FCollapseItem& FCollapseItem::setTitle(const QString& title)
{
    _title->setText(title);
    return *this;
}

FCollapseItem& FCollapseItem::setContent(const QString& content)
{
    _content->setText(content);
    return *this;
}

FCollapseItem& FCollapseItem::setIcon(FIcon::Name collapsedIcon, FIcon::Name expandIcon)
{
    _collapsedIcon = collapsedIcon;
    _expandIcon = expandIcon;
    return *this;
}

FCollapseItem& FCollapseItem::setDisabled(bool disabled)
{
    QWidget::setDisabled(disabled);
    return *this;
}

void FCollapseItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(FColor::lighterBorder());
    pen.setWidth(1);
    painter.setPen(pen);

    painter.drawLine(QPointF(0, 0), QPointF(width(), 0));

    if (_last)
        painter.drawLine(QPointF(0, height()), QPointF(width(), height()));

    QWidget::paintEvent(event);
}

void FCollapseItem::mousePressEvent(QMouseEvent* event)
{
    if (!_allowCollapse || !isEnabled())
        return;

    if (_titleLayout && event->y() <= _titleLayout->geometry().height())
        toggleStatus();

    QWidget::mousePressEvent(event);
}

void FCollapseItem::mouseMoveEvent(QMouseEvent* event)
{
    if (!isEnabled())
        setCursor(Qt::ForbiddenCursor);
    else if (_titleLayout
          && _titleLayout->geometry().contains(event->pos())
          && _allowCollapse)
        setCursor(Qt::PointingHandCursor);
   else
        unsetCursor();

    QWidget::mouseMoveEvent(event);
}

FCollapseItem& FCollapseItem::setWidth(int width)
{
    setFixedWidth(width);
    return *this;
}

FCollapseItem& FCollapseItem::setLast(bool isLast)
{
    _last = isLast;
    return *this;
}

FCollapse::FCollapse(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
}

FCollapse& FCollapse::setAccordion(bool accordion)
{
    _accordion = accordion;
    return *this;
}

FCollapse& FCollapse::setIcon(FIcon::Name collapsedIcon, FIcon::Name expandIcon)
{
    for (auto& item : _items)
        item->setIcon(collapsedIcon, expandIcon);
    return *this;
}

FCollapse& FCollapse::setCollapse(int index)
{
    if (index >= 0 && index < _items.size())
        _items[index]->setCollapse();
    return *this;
}

FCollapse& FCollapse::setExpand(int index)
{
    if (index >= 0 && index < _items.size())
        _items[index]->setExpand();
    return *this;
}

FCollapse& FCollapse::setIconPosition(Item::IconPosition position)
{
    for (auto& item : _items)
        item->setIconPosition(position);
    return *this;
}

FCollapse& FCollapse::toggleStatus(int index)
{
    if (index >= 0 && index < _items.size())
    {
        if (_accordion)
        {
            for (int i = 0; i < _items.size(); ++i)
            {
                if (i == index)
                    _items[i]->toggleStatus();
                else
                    _items[i]->setCollapse();
            }
        }
        else
        {
            _items[index]->toggleStatus();
        }

        adjustSize();
    }
    return *this;
}

FCollapse& FCollapse::addItem(FCollapseItem* item)
{
    if (!item)
        return *this;

    if (!_items.isEmpty())
        _items.back()->setLast(false);
    item->setLast(true);

    item->setParent(this);
    _items.append(item);
    layout()->addWidget(item);
    adjustSize();

    return *this;
}

FCollapse& FCollapse::delItem(int index)
{
    if (index >= 0 && index < _items.size())
    {
        if (index == _items.size() - 1)
        {
            _items[index]->setLast(false);
            if (index != 0) _items[index - 1]->setLast(true);
        }

        layout()->removeWidget(_items[index]);
        _items[index]->deleteLater();
        _items.removeAt(index);
    }
    return *this;
}

FCollapse& FCollapse::setWidth(int width)
{
    setFixedWidth(width);
    for (auto& item : _items)
        item->setWidth(width);
    return *this;
}


