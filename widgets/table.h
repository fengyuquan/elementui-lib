#pragma once

#include "private/utils.h"

#include <QTableWidget>
#include <QHeaderView>

class FTable : public QTableWidget
{
    Q_OBJECT

public:
    enum class Highlight
    {
        Primary,
        Success,
        Info,
        Warning,
        Danger,
    };

public:
    FTable& setWidth(const QList<int>& widths = QList<int>());
    FTable& setStripe(bool stripe);
    FTable& setBorder(bool border);
    FTable& setHightlight(int row, Highlight type);

//        FTable& setHeight(int height);
//        FTable& setMaxHeight(int maxHeight);


public:
   FTable(QWidget* parent = nullptr);
   FTable(const QStringList& headers, QWidget* parent = nullptr);
   FTable(const QStringList& headers, const QList<int>& widths, QWidget* parent = nullptr);
   FTable(const QStringList& headers, const QList<QStringList>& content, QWidget* parent = nullptr);

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    void highlightRow(int row);
    void clearHighlight();

    int _currentHoverRow = -1;

private:
   QSSHelper _qsshelper;
};

//    class CustomHeaderView : public QHeaderView
//    {
//    public:
//        CustomHeaderView(Qt::Orientation orientation, QWidget* parent = nullptr);
//    protected:
//        void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const override;
//    };


