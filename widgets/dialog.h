#pragma once

#include "text.h"
#include "button.h"

#include <QDialog>

class FDialog : public QDialog
{
    Q_OBJECT

public:
    FDialog& setTitle(const QString& title);
    FDialog& setContent(const QString& content);
    int show();

public:
    FDialog(QWidget* parent = nullptr);
    FDialog(const QString& title, const QString& content, QWidget* parent = nullptr);

protected:
    void showEvent(QShowEvent *event) override;

private:
    FText* _title;
    FText* _content;
    FButton* _cancel;
    FButton* _confirm;
};

