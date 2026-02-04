#include "image.h"
#include "color.h"

#include <QPainter>

FImage::FImage(QWidget* parent)
    : FImage(QPixmap(), parent)
{}

FImage::FImage(const QPixmap& pixmap, QWidget* parent)
    : QWidget(parent)
{
    setPixmap(pixmap);
}


FImage& FImage::setFit(Fit fit)
{
    if (_fit != fit)
    {
        _fit = fit;
        updateGeometry();
        update();
    }
    return *this;
}

FImage& FImage::setImage(const QImage& image)
{
    return setPixmap(QPixmap::fromImage(image));
}

FImage& FImage::setPixmap(const QPixmap& pixmap)
{
    _pixmap = pixmap;
    _originalSize = pixmap.size();
    updateGeometry();
    update();
    return *this;
}

void FImage::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    painter.fillRect(rect(), QColor(FColor::basicWhite()));

    if (_pixmap.isNull())
    {
        painter.drawText(rect(), Qt::AlignCenter, "No Image");
        return;
    }

    switch (_fit)
    {
    case Fit::Fill:
    case Fit::Contain:
    case Fit::Cover:
    case Fit::ScaleDown:
        painter.drawPixmap(_imageRect, _pixmap);
        break;
    case Fit::None:
        if (!_imageRect.isEmpty())
            painter.drawPixmap(_imageRect, _pixmap,
                    QRect(0, 0, _originalSize.width(), _originalSize.height()));
        break;
    }
}

void FImage::resizeEvent(QResizeEvent*)
{
    updateGeometry();
}

void FImage::updateGeometry()
{
    if (_pixmap.isNull() || size().isEmpty()) {
        _imageRect = QRect();
        return;
    }

    QSize widgetSize = size();
    QSize imageSize = _originalSize;

    switch (_fit)
    {
    case Fit::Fill:
    {
        // 填充整个区域，可能变形
        _imageRect = rect();
        break;
    }
    case Fit::Contain:
    {
        // 保持宽高比，完整显示图片
        QSize scaledSize = imageSize.scaled(widgetSize, Qt::KeepAspectRatio);
        _imageRect = QRect(0, 0, scaledSize.width(), scaledSize.height());
        _imageRect.moveCenter(rect().center());
        break;
    }
    case Fit::Cover:
    {
        // 保持宽高比，填充整个区域，可能裁剪
        QSize scaledSize = imageSize.scaled(widgetSize, Qt::KeepAspectRatioByExpanding);
        _imageRect = QRect(0, 0, scaledSize.width(), scaledSize.height());
        _imageRect.moveCenter(rect().center());
        break;
    }
    case Fit::None:
    {
        // 不缩放，居中显示
        _imageRect = QRect(0, 0, imageSize.width(), imageSize.height());
        _imageRect.moveCenter(rect().center());
        break;
    }
    case Fit::ScaleDown:
    {
        // 类似contain，但只在图片大于控件时才缩放
        if (imageSize.width() > widgetSize.width()
         || imageSize.height() > widgetSize.height())
        {
            // 需要缩放，使用contain逻辑
            QSize scaledSize = imageSize.scaled(widgetSize, Qt::KeepAspectRatio);
            _imageRect = QRect(0, 0, scaledSize.width(), scaledSize.height());
            _imageRect.moveCenter(rect().center());
        }
        else
        {
            // 不需要缩放，使用none逻辑
            _imageRect = QRect(0, 0, imageSize.width(), imageSize.height());
            _imageRect.moveCenter(rect().center());
        }
        break;
    }
    }
}


