//
// Created by 86158 on 2024/6/4.
//

#include "history.h"

//#ifdef ZEARO_BASH_HISTORY_FILE

void printLastNCommand(int n) {
    auto lines =  zearo_bash_shell::utils::File::getLastNLines(ZEARO_BASH_HISTORY_FILE, n);

    for (const auto & line : lines) {
        puts(line.c_str());
        putchar('\n');
    }
}

void addCommandToHistory(char *command) {
    zearo_bash_shell::utils::File::addStringToTheEnd(
            ZEARO_BASH_HISTORY_FILE, command
            );
}

//#endif

