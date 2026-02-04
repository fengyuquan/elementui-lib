#include "dialog.h"

#include <QBoxLayout>
#include "constants.h"

FDialog::FDialog(QWidget* parent)
    : FDialog("", "", parent)
{}

FDialog::FDialog(const QString& title, const QString& content, QWidget* parent)
    : QDialog(parent)
    , _title(new FText(title, this))
    , _content(new FText(content, this))
    , _cancel(new FButton("Cancel", this))
    , _confirm(new FButton("Confirm", this))
{
    setWindowFlags(windowFlags()
                   & ~Qt::WindowContextHelpButtonHint
                   & ~Qt::WindowCloseButtonHint);
    setWindowTitle("Dialog");
    setFixedSize(FConstants::FDialog::Width, FConstants::FDialog::Height);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setStyleSheet("background-color: white;");

    _title->setSize(FText::Size::Large);
    _confirm->setType(FButton::Type::Primary);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(FConstants::FDialog::Margin, FConstants::FDialog::Margin, FConstants::FDialog::Margin, FConstants::FDialog::Margin);
    mainLayout->setSpacing(FConstants::FDialog::Spacing);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(FConstants::FDialog::ButtonSpacing);
    buttonLayout->addStretch();
    buttonLayout->addWidget(_cancel);
    buttonLayout->addWidget(_confirm);

    mainLayout->addWidget(_title);
    mainLayout->addWidget(_content);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(_cancel, &QPushButton::clicked, this, &QDialog::reject);
    connect(_confirm, &QPushButton::clicked, this, &QDialog::accept);
}

FDialog& FDialog::setTitle(const QString &title)
{
    _title->setText(title);
    return *this;
}

FDialog& FDialog::setContent(const QString &content)
{
    _content->setText(content);
    return *this;
}

// FDialog::Accepted / FDialog::Rejected
int FDialog::show()
{
    return exec();
}

void FDialog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    if (parentWidget())
    {
        int parentHeight = parentWidget()->height();
        int targetY = parentWidget()->pos().y() + parentHeight * FConstants::FDialog::PositionRatio;

        move(parentWidget()->pos().x() + (parentWidget()->width() - width()) / 2,
             targetY);
    }
}

