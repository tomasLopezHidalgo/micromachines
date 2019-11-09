//
// Created by eliana on 7/11/19.
//

#include "PluginsReader.h"

#define DIRECTORY "plugins"
#define EXTENSION "so"

typedef void (*func_pointer)(void);

PluginsReader::PluginsReader() {
    DIR* dir;
    struct dirent *file;

    dir = opendir(DIRECTORY);
    if (dir != NULL) {
        while ((file = readdir(dir)) != NULL) {
            std::string name = std::string(file->d_name);
            if(name.substr(name.find_last_of(".") + 1) == EXTENSION) {
                void* shared_lib = dlopen(file->d_name, RTLD_NOW);
                name = name.substr(0, name.size() - 3); // remove .so
                if (!shared_lib) {
                    continue;
                }
                files[name] = shared_lib;
            }
        }
    }
    closedir(dir);
}

void PluginsReader::applyPlugin() {
    func_pointer plugin;
    for (auto it = files.begin(); it != files.end(); ++it) {
        *(void **) (&plugin) = dlsym(it->second, it->first);
    }
}

PluginsReader::~PluginsReader() {
    for (auto it = files.begin(); it != files.end(); ++it) {
        dlclose(it->second);
    }
}
