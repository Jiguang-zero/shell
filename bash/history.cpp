//
// Created by 86158 on 2024/6/4.
//

#include "history.h"

#ifdef ZEARO_BASH_HISTORY_FILE

void printLastNCommand(int n) {
    // When this function is called, it means that we use history command.
    // And history command is also a command which will be recorded into file.
    // But obviously we don't want to print it.
    // So we should get more one history.
    auto lines =  zearo_bash_shell::utils::File::getLastNLines(
            getHistoryFilePath(), n + 1);

    for (auto it = lines.begin(); it != lines.end(); it ++ ) {
        if (it + 1 == lines.end()) {
            break;
        }
        puts((*it).c_str());
    }
}

void addCommandToHistory(char *command) {
    zearo_bash_shell::utils::File::addStringToTheEnd(
            getHistoryFilePath(), command
            );
}

std::string getHistoryFilePath() {
    char* homeDir = getenv("HOME");
    if (homeDir == nullptr) {
        fprintf(stderr, "zbash configs load error: cannot get user home.\n");
        exit(EXIT_FAILURE);
    }

    std::string filePath = std::string(homeDir) + "/" + ZEARO_BASH_HISTORY_FILE;

    return filePath;
}

#endif

