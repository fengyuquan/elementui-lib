TEMPLATE = lib
CONFIG += qt warn_on c++17 dll
QT += widgets svg

TARGET = elementui

DESTDIR = $$PWD/build
OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR = $$DESTDIR/moc
RCC_DIR = $$DESTDIR/rcc
UI_DIR = $$DESTDIR/ui

INCLUDEPATH += $$PWD/widgets \
                $$PWD/widgets/private

SOURCES += \
    $$files($$PWD/widgets/*.cpp) \
    $$files($$PWD/widgets/private/*.cpp)

HEADERS += \
    $$files($$PWD/widgets/*.h) \
    $$files($$PWD/widgets/private/*.h)

RESOURCES += $$PWD/resources/icons.qrc \
             $$PWD/resources/fonts.qrc \

# Link Windows GDI library for GetDeviceCaps (used in widgets/private/utils.cpp)
win32:LIBS += -lgdi32

