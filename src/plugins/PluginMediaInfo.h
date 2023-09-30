#pragma once

#include <QString>
#include <QTextEdit>
#include <QMediaPlayer>

struct PluginMediaInfo
{
    virtual ~PluginMediaInfo() {}

    virtual void writeMeta(QTextEdit *, QMediaPlayer *) = 0;
    virtual void writeMediaInfo(QTextEdit *, QMediaPlayer *) = 0;
    virtual void writeMediaError(QTextEdit *, QMediaPlayer *) = 0;
    virtual QString getItem(int, QMediaPlayer *) = 0;
};
