#pragma once

struct PluginHelp
{
    virtual ~PluginHelp() {}

    virtual void show() = 0;
};
