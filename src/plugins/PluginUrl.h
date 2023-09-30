#pragma once

#include <QUrl>
#include <QString>
#include <QFileInfo>

struct PluginUrl
{
    virtual ~PluginUrl() {}

    virtual QUrl parce(QString) = 0;
    virtual QFileInfo info(QString) = 0;
};
