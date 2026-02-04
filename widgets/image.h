#pragma once

#include <QLabel>

class FImage : public QWidget
{
    Q_OBJECT
public:
    enum class Fit
    {
        Fill,
        Contain,
        Cover,
        None,
        ScaleDown,
    };

public:
    FImage& setFit(Fit fit);
    FImage& setImage(const QImage& image);
    FImage& setPixmap(const QPixmap& pixmap);

public:
    FImage(QWidget* parent = nullptr);
    FImage(const QPixmap& pixmap, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    void updateGeometry();

private:
    Fit _fit = Fit::Fill;
    QPixmap _pixmap;
    QSize _originalSize;
    QRect _imageRect;
    QRect _viewportRect;
};


