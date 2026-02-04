#include "drawer.h"
#include "text.h"
#include "icon.h"
#include "color.h"
#include "private/utils.h"
#include "shadow.h"
#include "mask.h"
#include "constants.h"

#include <QtMath>
#include <QEvent>

FDrawer::FDrawer(QWidget* topWidget)
    : QWidget(topWidget)
    , _layout(new QVBoxLayout(this))
{
    setupHeader();
    setupBody();
    setupFooter();

    _layout->addWidget(_header);
    _layout->addLayout(_bodyLayout);
    _layout->addStretch();
    _layout->addWidget(_footer);

    setVisible(false);

    FShadowEf::setShadow(this, FShadowEf::Type::Dark);
    FMask* mask = FMaskEf::setMask(this, topWidget);

    connect(mask, &FMask::clicked, this, &FDrawer::hide);
}

FDrawer& FDrawer::setBody(QWidget* body)
{
    _bodyLayout->replaceWidget(_body, body);
    _body = body;
    return *this;
}

void FDrawer::setupHeader()
{
    _header = new QWidget(this);

    QLabel* text = new QLabel(_title, _header);
    text->setFont(FontHelper().setPointSize(FConstants::FDrawer::HeaderFontSize).getFont());

    QPalette palette = text->palette();
    palette.setColor(QPalette::WindowText, FColor::primaryText());
    text->setPalette(palette);

    _closeIcon = new QLabel(_header);
    _closeIcon->setAttribute(Qt::WA_Hover);
    _closeIcon->installEventFilter(this);
    _closeIcon->setPixmap(FIcon::instance().getPixmap(FIcon::Close, FColor::primaryText(), FConstants::FDrawer::CloseIconSize));
    connect(_closeIcon, &QLabel::linkActivated, this, &FDrawer::close);

    QHBoxLayout* layout = new QHBoxLayout(_header);
    layout->setContentsMargins(FConstants::FDrawer::HeaderMargin, FConstants::FDrawer::HeaderMargin, FConstants::FDrawer::HeaderMargin, FConstants::FDrawer::HeaderMargin);
    layout->setSpacing(0);
    layout->addWidget(text);
    layout->addStretch();
    layout->addWidget(_closeIcon);
}

void FDrawer::setupBody()
{
    _bodyLayout = new QVBoxLayout;
    _bodyLayout->setContentsMargins(FConstants::FDrawer::BodyMargin, FConstants::FDrawer::BodyMargin, FConstants::FDrawer::BodyMargin, FConstants::FDrawer::BodyMargin);
    _bodyLayout->addWidget(new FText("Hi there!", this));
}

void FDrawer::setupFooter()
{
    _footer = new QWidget(this);

    _cancelBtn = new FButton("cancel", _footer);

    _confirmBtn = new FButton("confirm", _footer);
    _confirmBtn->setType(FButton::Type::Primary);

    QHBoxLayout* layout = new QHBoxLayout(_footer);
    layout->setContentsMargins(FConstants::FDrawer::FooterMarginHorizontal, FConstants::FDrawer::FooterMarginTop, FConstants::FDrawer::FooterMarginHorizontal, FConstants::FDrawer::FooterMarginBottom);
    layout->setSpacing(FConstants::FDrawer::FooterButtonSpacing);
    layout->addStretch();
    layout->addWidget(_cancelBtn);
    layout->addWidget(_confirmBtn);

    connect(_cancelBtn, &FButton::clicked, this, &FDrawer::close);
    connect(_confirmBtn, &FButton::clicked, this, &FDrawer::confirm);
}

void FDrawer::resizeEvent(QResizeEvent* event)
{
    QWidget* topWidget = parentWidget();
    QRect rect = topWidget->rect();

    rect.setLeft(qRound(topWidget->rect().width() * FConstants::FDrawer::DefaultWidthRatio));
    rect.setWidth(qRound(topWidget->rect().width() * FConstants::FDrawer::DefaultWidthRatio));
    setGeometry(rect);

    QWidget::resizeEvent(event);
}

bool FDrawer::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == _closeIcon)
    {
        if (event->type() == QEvent::HoverEnter)
        {
            _closeIcon->setPixmap(FIcon::instance().getPixmap(FIcon::Close, FColor::primary(), FConstants::FDrawer::CloseIconSize));
            _closeIcon->setCursor(Qt::PointingHandCursor);
            return true;
        }
        else if (event->type() == QEvent::HoverLeave)
        {
            _closeIcon->setPixmap(FIcon::instance().getPixmap(FIcon::Close, FColor::primaryText(), FConstants::FDrawer::CloseIconSize));
            _closeIcon->setCursor(Qt::ArrowCursor);
            return true;
        }
        else if (event->type() == QEvent::MouseButtonPress)
        {
            emit _closeIcon->linkActivated("");
        }
    }
    return QWidget::eventFilter(watched, event);
}

