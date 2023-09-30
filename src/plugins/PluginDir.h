#pragma once

#include <QStringList>
#include <QUrl>
#include <QObject>

struct PluginDir
{
    virtual ~PluginDir() {};

    virtual QStringList scan(QString) = 0;
    virtual QStringList scanUrl(QUrl) = 0;
    virtual QString openChooseDialog(QString, int) = 0;
    virtual QString openSaveDialog(QString) = 0;
};
