#pragma once

#include "private/utils.h"
#include "color.h"

#include <QString>
#include <QLabel>
#include <QHash>

class FMessage : public QWidget
{
    Q_OBJECT

public:
    enum class Type
    {
        Primary,
        Success,
        Warning,
        Info,
        Error
    };

    enum class Place
    {
        Top,
        TopLeft,
        TopRight,
        Bottom,
        BottomLeft,
        BottomRight
    };

public:
    FMessage& setMessage(const QString& message);
    FMessage& setParamater(const QString& paramater);

    FMessage& setType(Type type);
    FMessage& setPlain(bool plain);
    FMessage& setShowClose(bool showClose, bool autoClose = true);
    FMessage& setPlacement(Place place);
    FMessage& setDuration(int msec);

public:
    FMessage(const QString& message, QWidget* parent = nullptr);
    FMessage(const QString& message, const QString& paramater, QWidget* parent = nullptr);
    FMessage(const QString& message, Type type = Type::Info, QWidget* parent = nullptr);
    FMessage(const QString& message, const QString& paramater, Type type = Type::Info, QWidget* parent = nullptr);

    void show();

private:
    void updateTextAndIcon();
    void updatePosition();

    QString getColor();
    QString getBorderColor();
    QString getBackgroundColor();
    QPixmap getIcon();

    void onTimeout();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString _message;
    QString _paramater;

private:
    Type _type = Type::Info;
    Place _placement = Place::Top;
    bool _plain = false;
    bool _showClose = false;
    int _duration = 3000;

private:
    QSSHelper _qsshelper;
    QLabel* _icon;
    QLabel* _text;
    QTimer* _timer;
    static QHash<Place, int> _count;
};

inline uint qHash(FMessage::Place key, uint seed = 0) noexcept {
    return static_cast<uint>(std::hash<int>{}(static_cast<int>(key))) ^ seed;
}

inline QHash<FMessage::Place, int> FMessage::_count;

