#pragma once

#include <QString>

struct PluginReadme
{
    virtual ~PluginReadme() {}

    virtual void create(QString) = 0;
};
