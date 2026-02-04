#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>

class FCard : public QWidget
{
    Q_OBJECT

public:
    enum class Shadow { Always, Hover, Never };

public:
    FCard& setHeader(const QString& header);
    FCard& setFooter(const QString& footer);

    FCard& setBody(QWidget* widget);

    FCard& setShadow(Shadow shadow);

public:
    FCard(QWidget* parent = nullptr);
    FCard(const QString& header, QWidget* widget, QWidget* parent = nullptr);
    FCard(const QString& header, QWidget* widget, const QString& footer, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    void setupUI();
    void cleanLayout(QWidget* widget);

private:
    Shadow _shadow = Shadow::Hover;

private:
    QLabel* _header = nullptr;
    QLabel* _footer = nullptr;
    QWidget* _body = nullptr;

    QVBoxLayout* _mainLayout = nullptr;
};


