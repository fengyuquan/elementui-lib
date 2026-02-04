#pragma once

#include "button.h"

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>

class FDrawer : public QWidget
{
    Q_OBJECT

public:
    enum class Direction
    {
        RightToLeft,
        LeftToRight,
        TopToBottom,
        BottomToTop,
    };

public:
    FDrawer& setModal(bool modal);
    FDrawer& setDirection(Direction direction);
    FDrawer& setShowClose(bool showClose);
    FDrawer& setSize(int percent);
    FDrawer& setTitle(const QString& title);
    FDrawer& setWithHeader(bool withHeader);
    FDrawer& setWithFooter(bool withFooter);
    FDrawer& setBody(QWidget* body);

signals:
    void confirm();

public:
    FDrawer(QWidget* topWidget);

protected:
    void resizeEvent(QResizeEvent* event) override;
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    void setupHeader();
    void setupBody();
    void setupFooter();

private:
    bool _modal = false;
    Direction _direction = Direction::RightToLeft;
    bool _showClose = true;
    int _percent = 30;
    QString _title = "I am the title";
    bool _withHeader = true;
    bool _withFooter = true;

private:
    QWidget* _header = nullptr;
    QWidget* _body = nullptr;
    QWidget* _footer = nullptr;
    QVBoxLayout* _layout = nullptr;
    QVBoxLayout* _bodyLayout = nullptr;

private:
    QLabel* _closeIcon = nullptr;
    FButton* _cancelBtn = nullptr;
    FButton* _confirmBtn = nullptr;
};

