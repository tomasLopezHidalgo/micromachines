#ifndef MICROMACHINES_PLUGINSMANAGER_H
#define MICROMACHINES_PLUGINSMANAGER_H

#include <dirent.h>
#include <cstdio>
#include <dlfcn.h>
#include <mutex>
#include <unordered_map>
#include <atomic>
#include <vector>
#include <nlohmann/json.hpp>
#include "Plugin.h"
#include "Thread.h"
#include "PluginHandler.h"

class PluginsManager : public Thread {
private:
    std::mutex mutex;
    std::unordered_map<std::string, Plugin*> plugins;
    std::vector<PluginHandler*> handlers;
    std::atomic<bool> finished;
    void readPluginsDirectory();
public:
    PluginsManager();
    void run() override;
    void stop();
    nlohmann::json applyRandomPlugin(nlohmann::json& model);
    ~PluginsManager();
};


#endif //MICROMACHINES_PLUGINSMANAGER_H
