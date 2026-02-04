#include "card.h"
#include "shadow.h"
#include "color.h"
#include "private/utils.h"
#include "constants.h"

#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QPainterPath>

FCard::FCard(QWidget* parent)
    : FCard("", nullptr, "", parent)
{}
FCard::FCard(const QString& header, QWidget* widget, QWidget* parent)
    : FCard(header, widget, "", parent)
{}
FCard::FCard(const QString& header, QWidget* widget, const QString& footer, QWidget* parent)
    : QWidget(parent)
    , _header(new QLabel(this))
    , _footer(new QLabel(this))
    , _body(new QWidget(this))
    , _mainLayout(new QVBoxLayout(this))
{
    setupUI();
    setHeader(header);
    setFooter(footer);
    setBody(widget);

    setMinimumSize(sc(FConstants::FCard::MinWidth, FConstants::FCard::MinHeight));
    setMaximumSize(sc(FConstants::FCard::MaxWidth, FConstants::FCard::MaxHeight));
}

void FCard::setupUI()
{
    int paddingh = sc(FConstants::FCard::PaddingHorizontal);
    int paddingv = sc(FConstants::FCard::PaddingVertical);
    _header->setStyleSheet(QString("padding: %1px %2px; border: none; border-bottom: 1px solid %3; color: %4;")
                           .arg(paddingh).arg(paddingv)
                           .arg(FColor::lightBorder())
                           .arg(FColor::primaryText()));
    _footer->setStyleSheet(QString("padding: %1px %2px; border: none; border-top: 1px solid %3; color: %4; ")
                           .arg(paddingh).arg(paddingv)
                           .arg(FColor::lightBorder())
                           .arg(FColor::primaryText()));
    _body->setStyleSheet("border: none; color: " + FColor::primaryText() + "; ");

    _header->setWordWrap(true);
    _footer->setWordWrap(true);

    _header->setFont(FontHelper(_header->font())
            .setPointSize(Comm::defaultFontSize)
            .getFont());

    _footer->setFont(FontHelper(_footer->font())
            .setPointSize(Comm::defaultFontSize)
            .getFont());

    _mainLayout->setContentsMargins(0, 0, 0, 0);
    _mainLayout->setSpacing(0);
    _mainLayout->addWidget(_header);
    _mainLayout->addWidget(_body, 1);
    _mainLayout->addWidget(_footer);

    FShadowEf::setShadow(this, FShadowEf::Type::Basic);
    setShadow(_shadow);

    setMouseTracking(true);
}

FCard& FCard::setHeader(const QString& header)
{
    _header->setText(header);
    _header->setVisible(!header.isEmpty());
    return *this;
}

FCard& FCard::setFooter(const QString& footer)
{
    _footer->setText(footer);
    _footer->setVisible(!footer.isEmpty());
    return *this;
}

FCard& FCard::setBody(QWidget* widget)
{
    if (widget)
    {
        cleanLayout(_body);
        QVBoxLayout* layout = new QVBoxLayout(_body);
        layout->setContentsMargins(FConstants::FCard::BodyMarginLeft, 0, FConstants::FCard::BodyMarginRight, FConstants::FCard::BodyMarginBottom);
        layout->addWidget(widget);
    }
    return *this;
}

FCard& FCard::setShadow(Shadow shadow)
{
    _shadow = shadow;
    graphicsEffect()->setEnabled(_shadow == Shadow::Always);
    return *this;
}

void FCard::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制圆角背景
    QPainterPath path;
    path.addRoundedRect(rect().adjusted(0, 0, 0, 0), FConstants::FCard::BorderRadius, FConstants::FCard::BorderRadius, Qt::AbsoluteSize);
    painter.setClipPath(path);

    // 填充背景
    painter.fillPath(path, Qt::white);

    // 绘制边框
    painter.setPen(QPen(QColor(FColor::lightBorder()), 1));
    painter.drawRoundedRect(rect().adjusted(0, 0, 0, 0), FConstants::FCard::BorderRadius, FConstants::FCard::BorderRadius, Qt::AbsoluteSize);

    QWidget::paintEvent(event);
}

void FCard::enterEvent(QEvent* event)
{
    if (_shadow == Shadow::Hover)
        graphicsEffect()->setEnabled(true);
    QWidget::enterEvent(event);
}

void FCard::leaveEvent(QEvent* event)
{
    if (_shadow == Shadow::Hover)
        graphicsEffect()->setEnabled(false);
    QWidget::leaveEvent(event);
}

void FCard::cleanLayout(QWidget* widget)
{
    if (widget->layout())
    {
        QLayout* oldLayout = widget->layout();
        QLayoutItem* item;

        while ((item = oldLayout->takeAt(0)) != nullptr)
        {
            if (item->widget())
                delete item->widget();
            delete item;
        }
        delete oldLayout;
    }
}


