//
// Created by 86158 on 2024/6/3.
//

#include "configs.h"

#include <cstdlib>
#include <fstream>

#include "utils/file.h"
#include "alias.h"

using zearo_bash_shell::utils::File;

static void createHistoryFileIfNotExists() {
#ifdef ZEARO_BASH_HISTORY_FILE
    char* homeDir = getenv("HOME");
    if (homeDir == nullptr) {
        fprintf(stderr, "zbash configs load error: cannot get user home.\n");
        exit(EXIT_FAILURE);
    }

    std::string filePath = std::string(homeDir) + "/" + ZEARO_BASH_HISTORY_FILE;
    std::ofstream file(filePath.c_str());
    if (file.is_open()) {
        file.close();
    } else {
        fprintf(stderr, "zbash configs load error: cannot create history file.");
    }

#endif
}

static void createConfigsFileIfNotExist() {
#ifdef ZEARO_BASH_CONFIGS_FILE
    char* homeDir = getenv("HOME");
    if (homeDir == nullptr) {
        fprintf(stderr, "zbash configs load error: cannot get user home.\n");
        exit(EXIT_FAILURE);
    }

    std::string filePath = std::string(homeDir) + "/" + ZEARO_BASH_CONFIGS_FILE;
    File::createFileIfNotExists(filePath);

#endif
}

/**
 * @brief read alias config from the file
 */
static void readAliasConfig() {
    char* homeDir = getenv("HOME");
    if (homeDir == nullptr) {
        fprintf(stderr, "zbash configs load error: cannot get user home.\n");
        exit(EXIT_FAILURE);
    }

    std::string filePath = std::string(homeDir) + "/" + ZEARO_BASH_CONFIGS_FILE;
    alias::getInstance()->initFromTheFile(filePath.c_str());
}


void loadConfigs() {
    createHistoryFileIfNotExists();
    createConfigsFileIfNotExist();

    readAliasConfig();
}
