#-------------------------------------------------
#
# Project created by QtCreator 2013-05-17T21:03:28
#
#-------------------------------------------------

QT += core gui multimediawidgets multimedia

unix,!mac {
    QT += x11extras
    LIBS += -lX11 -lxcb
    SOURCES += src/qglobalshortcut_x11.cc
    QMAKE_LFLAGS += -static-libgcc
}

win32 {
    SOURCES += src/qglobalshortcut_win.cc
    QMAKE_LFLAGS += -static-libgcc
}

mac,!unix {
    SOURCES += src/qglobalshortcut_mac.cc
}

TARGET = player2
TEMPLATE = app

QMAKE_LFLAGS += -Wall \
                -Wpedantic

CONFIG += static \
          c++11

TRANSLATIONS += uk_UA.ts en_US.ts

SOURCES += main.cpp \
           src/qglobalshortcut_mac.cc \
           widget.cpp \
           class_settings.cpp \
           src/qglobalshortcut.cc

HEADERS += widget.h \
            settings_key.h \
            class_settings.h \
            defines.h \
            typedefs.h \
            debug.h \
            src/qglobalshortcut.h

FORMS += widget.ui

RESOURCES += resource.qrc
