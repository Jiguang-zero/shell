//
// Created by 86158 on 2024/6/4.
//

#include "alias.h"
#include "configs.h"

#include "utils/file.h"
#include "utils/string_dealing.h"

using zearo_bash_shell::utils::File;
using zearo_bash_shell::utils::string_dealing;

alias* alias::instance = nullptr;

alias *alias::getInstance() {
    if (instance == nullptr) {
        instance = new alias;
    }
    return instance;
}

void alias::initFromTheFile(const char *fileName) {
#ifdef ZEARO_BASH_CONFIGS_ALIAS
    auto prefix = ZEARO_BASH_CONFIGS_ALIAS;

    auto string = File::getSubstringAfterPrefix(fileName, prefix);
    string_dealing::transferStringToMap(aliasMap, string);
#endif
}

int alias::addAlias(const std::string &originName, const std::string &aliasName) {
    if (aliasMap.find(aliasName) != aliasMap.end()) {
        return 0;
    }
    aliasMap[aliasName] = originName;
    writeTheMapIntoFile();
    return 1;
}

int alias::removeAlias(const std::string &aliasName) {
    auto it = aliasMap.find(aliasName);
    if (it != aliasMap.end()) {
        aliasMap.erase(it);
        writeTheMapIntoFile();
        return 1;
    }
    else {
        return 0;
    }
}

void alias::writeTheMapIntoFile() {
    char* homeDir = getenv("HOME");
    if (homeDir == nullptr) {
        fprintf(stderr, "zbash configs load error: cannot get user home.\n");
        exit(EXIT_FAILURE);
    }

    std::string filePath = std::string(homeDir) + "/" + ZEARO_BASH_CONFIGS_FILE;

    File::replaceLineInFileWithPrefix(
            filePath,
            ZEARO_BASH_CONFIGS_ALIAS,
            string_dealing::transferMapToString(aliasMap)
            );
}

void alias::printTheMap() {
    for (const auto & pair : aliasMap) {
        printf("%s: %s\n", pair.first.c_str(), pair.second.c_str());
    }
}


