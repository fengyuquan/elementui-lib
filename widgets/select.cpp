#include "select.h"

#include "private/utils.h"
#include "color.h"
#include "shadow.h"
#include "scrollbar.h"
#include "constants.h"

#include <QBoxLayout>
#include <QMouseEvent>
#include <QApplication>
#include <QResizeEvent>
#include <QEvent>

FOptionListItemWidget::FOptionListItemWidget(const QString& text, QWidget* parent)
    : QWidget(parent)
    , _label(new QLabel(text, this))
{
        QHBoxLayout* layout = new QHBoxLayout(this);
        layout->setContentsMargins(FConstants::FCommon::LayoutMargin, FConstants::FCommon::LayoutMargin, 
                                  FConstants::FCommon::LayoutMargin, FConstants::FCommon::LayoutMargin);
        layout->setSpacing(FConstants::FCommon::LayoutSpacing);
        layout->addWidget(_label);

        _label->setFont(FontHelper().setPixelSize(FConstants::FSelect::ItemFontSize).getFont());

        _qsshelper.setProperty("QWidget", "color", FColor::regularText());
        _qsshelper.setProperty("QWidget", "font-size", QString::number(FConstants::FSelect::ItemFontSize) + "px");
        _qsshelper.setProperty("QWidget", "background-color", "transparent");
        _qsshelper.setProperty("QWidget", "padding-left", QString::number(FConstants::FSelect::ItemPaddingLeft) + "px");
        _qsshelper.setProperty("QWidget:hover", "background-color", FColor::lightFill());
        _qsshelper.setProperty("QLabel", "color", FColor::regularText());
        _qsshelper.setProperty("QLabel", "font-size", QString::number(FConstants::FSelect::ItemFontSize) + "px");
        _qsshelper.setProperty("QLabel", "background-color", "transparent");
        setStyleSheet(_qsshelper.generate());

        setFixedHeight(FConstants::FSelect::ItemHeight);
    }

QLabel* FOptionListItemWidget::getLabel()
{
    return _label;
}

void FOptionListItemWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked(_label->text());
    QWidget::mousePressEvent(event);
}


FOptionList::FOptionList(Placement placement, FSelect* input, QWidget* parent)
    : FOptionList(FConstants::FSelect::DefaultWidth, placement, {}, input, parent)
{}

FOptionList::FOptionList(int width, Placement placement, FSelect* input, QWidget* parent)
    : FOptionList(width, placement, {}, input, parent)
{}

FOptionList::FOptionList(int width, Placement placement, const QStringList& data, FSelect* input, QWidget* parent)
    : QListWidget(parent)
    , _placement(placement)
    , _input(input)
{
        _qsshelper.setProperty("QListWidget", "background-color", "white");
        _qsshelper.setProperty("QListWidget", "border", "1px solid " + FColor::darkBorder());
        _qsshelper.setProperty("QListWidget", "border-radius", QString::number(FConstants::FSelect::BorderRadius) + "px");
        _qsshelper.setProperty("QListWidget", "padding", QString::number(FConstants::FSelect::Padding) + "px 0px");
        _qsshelper.setProperty("QListWidget", "font-size", QString::number(FConstants::FSelect::ItemFontSize) + "px");
        _qsshelper.setProperty("QListWidget", "color", FColor::regularText());
        setStyleSheet(_qsshelper.generate());

        setMouseTracking(true);
        setFocusPolicy(Qt::NoFocus);
        setVerticalScrollBar(new FScrollBar(Qt::Vertical, this));

        setSelectionMode(QAbstractItemView::NoSelection);
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        FShadowEf::setShadow(this, FShadowEf::Type::Basic);

        setFixedSize(width, FConstants::FSelect::Padding * 2 + FConstants::FSelect::BorderWidth);
        
        addItems(data);
    }

void FOptionList::addItem(const QString& text)
{
    QListWidgetItem* item = new QListWidgetItem(this);
    FOptionListItemWidget* widget = new FOptionListItemWidget(text, this);

    item->setSizeHint(widget->size());
    setItemWidget(item, widget);

    connect(widget, &FOptionListItemWidget::clicked, this, [&](const QString& text) {
        hide();
        emit itemClicked(text);
    });

    updateHeight(count());
}

void FOptionList::addItems(const QStringList& texts)
{
    for (const QString& text : texts)
        addItem(text);
}

void FOptionList::setItems(const QStringList& texts)
{
    clear();
    addItems(texts);
}

void FOptionList::filterItems(const QString& text)
{
    int visibleCount = 0;

    for (int i = 0; i < count(); ++i)
    {
        QListWidgetItem* item = this->item(i);
        FOptionListItemWidget* widget = qobject_cast<FOptionListItemWidget*>(itemWidget(item));

        if (!widget) return;

        bool matches =
                text.isEmpty() ||
                widget->getLabel()->text().startsWith(text, Qt::CaseInsensitive);
        item->setHidden(!matches);
        if (matches)
            visibleCount++;
    }

    updateHeight(visibleCount);
}

void FOptionList::show()
{
    QWidget::raise();
    QWidget::show();
}

void FOptionList::updateWidth()
{
    if (_input)
    {
        setFixedWidth(_input->width());
    }
}

void FOptionList::showEvent(QShowEvent* event)
{
    updateWidth();
    
    const int interval = FConstants::FSelect::InputSpacing;

    if (_input)
    {
        QWidget* parent = parentWidget();
        if (parent)
        {
            // 使用parent的坐标系
            QPoint inputPos = _input->pos();
            if (_placement == Placement::Bottom)
                move(inputPos.x(), inputPos.y() + _input->height() + interval);
            else
                move(inputPos.x(), inputPos.y() - height() - interval);
        }
        else
        {
            // 如果没有parent，使用全局坐标
            QPoint globalPos = _input->mapToGlobal(QPoint(0, 0));
            if (_placement == Placement::Bottom)
                move(globalPos.x(), globalPos.y() + _input->height() + interval);
            else
                move(globalPos.x(), globalPos.y() - height() - interval);
        }
    }

    QWidget::showEvent(event);
}

void FOptionList::updateHeight(int count)
{
    int totalHeight = FConstants::FSelect::ItemHeight * count + FConstants::FSelect::Padding * 2 + FConstants::FSelect::BorderWidth;
    int newHeight = qMin(totalHeight, FConstants::FSelect::MaxHeight);
    setFixedHeight(newHeight);
}


FSelect::FSelect(QWidget* parent)
    : FSelect({}, parent)
{}

FSelect::FSelect(const QStringList& data, QWidget* parent)
    : FInputLine(parent)
    , _popList(new FOptionList(width(),
        (FOptionList::Placement)_placement, data, this, parent))
{
    setPlaceholder("Select");
    setReadOnly(true);
    setSuffixIcon(FIcon::ArrowDown);

    _popList->hide();
    
    // 安装事件过滤器以监听全局鼠标点击
    QApplication::instance()->installEventFilter(this);

    connect(_popList, &FOptionList::itemClicked, this, [this](const QString& text) {
        setText(text);
        setSuffixIcon(FIcon::ArrowDown);  // 立即还原箭头
        setFocus();
        _popList->hide();
    });
}

FSelect& FSelect::setOptions(const QStringList& options)
{
    _options = options;
    _popList->setItems(options);
    return *this;
}

FSelect& FSelect::setPlacement(Placement placement)
{
    _placement = placement;
    return *this;
}

FSelect& FSelect::addItem(const QString& text)
{
    _popList->addItem(text);
    return *this;
}

FSelect& FSelect::addItems(const QStringList& texts)
{
    _popList->addItems(texts);
    return *this;
}

void FSelect::focusOutEvent(QFocusEvent* event)
{
    FInputLine::focusOutEvent(event);
    setSuffixIcon(FIcon::ArrowDown);
    _popList->hide();
}

void FSelect::mousePressEvent(QMouseEvent* event)
{
    FInputLine::mousePressEvent(event);
    if (event->button() == Qt::LeftButton)
    {
        if (_popList->isVisible())
        {
            setSuffixIcon(FIcon::ArrowDown);
            _popList->hide();
        }
        else
        {
            setSuffixIcon(FIcon::ArrowUp);
            _popList->show();
        }
    }
}

void FSelect::mouseDoubleClickEvent(QMouseEvent* e)
{
    FSelect::mousePressEvent(e);
    e->accept();
}

void FSelect::resizeEvent(QResizeEvent* event)
{
    FInputLine::resizeEvent(event);
    if (_popList && _popList->isVisible())
    {
        // 当Select大小改变时，更新OptionList的宽度和位置
        _popList->updateWidth();
        QWidget* parent = parentWidget();
        if (parent)
        {
            // 使用相对于parent的位置
            QPoint pos = this->pos();
            const int interval = FConstants::FSelect::InputSpacing;
            if (_placement == Placement::Bottom)
                _popList->move(pos.x(), pos.y() + height() + interval);
            else
                _popList->move(pos.x(), pos.y() - _popList->height() - interval);
        }
    }
}

bool FSelect::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress && _popList && _popList->isVisible())
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        QPoint globalPos = mouseEvent->globalPos();
        
        // 检查点击是否在Select输入框或OptionList内
        QRect selectRect = QRect(mapToGlobal(QPoint(0, 0)), size());
        QRect listRect = QRect(_popList->mapToGlobal(QPoint(0, 0)), _popList->size());
        
        if (!selectRect.contains(globalPos) && !listRect.contains(globalPos))
        {
            // 点击在空白区域，隐藏弹出栏并还原箭头
            setSuffixIcon(FIcon::ArrowDown);
            _popList->hide();
        }
    }
    
    return FInputLine::eventFilter(obj, event);
}

