#-------------------------------------------------
#
# Project created by QtCreator 2013-05-17T21:03:28
#
#-------------------------------------------------

QT += core gui multimediawidgets multimedia

unix,!mac {
    QT += x11extras
    LIBS += -lX11 -lxcb
    SOURCES += src/shortcut/qglobalshortcut_x11.cc
    QMAKE_LFLAGS += -static-libgcc
}

win32 {
    SOURCES += src/shortcut/qglobalshortcut_win.cc
    QMAKE_LFLAGS += -static-libgcc
}

mac,!unix {
    SOURCES += src/shortcut/qglobalshortcut_mac.cc
}

TARGET = player2
TEMPLATE = app

QMAKE_LFLAGS += -Wall \
                -Wpedantic

CONFIG += static \
          c++11

TRANSLATIONS += resources/translate/uk_UA.ts resources/translate/en_US.ts

SOURCES += main.cpp \
           src/settings/Settings.cpp \
           src/widget.cpp \
           src/shortcut/qglobalshortcut.cc

HEADERS += src/widget.h \
            src/plugins/PluginDir.h \
            src/plugins/PluginHelp.h \
            src/plugins/PluginMediaInfo.h \
            src/plugins/PluginPlaylist.h \
            src/plugins/PluginReadme.h \
            src/plugins/PluginUrl.h \
            src/settings/Settings.h \
            src/settings/SettingsKey.h \
            src/defines.h \
            src/shortcut/qglobalshortcut.h

FORMS += ui/widget.ui

RESOURCES += resources/resource.qrc
