//
// Created by 86158 on 2024/6/3.
//

#include "configs.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <unistd.h>

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

void loadConfigs() {
    createHistoryFileIfNotExists();
}
