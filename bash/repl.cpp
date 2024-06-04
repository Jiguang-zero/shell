//
// Created by 86158 on 2024/6/2.
//

#include "repl.h"
#include "prompt.h"

#ifndef ZEARO_BASH_INCLUDE_C_STDLIB
#include <cstdlib>
#endif // ZEARO_BASH_INCLUDE_C_STDLIB

#ifndef ZEARO_BASH_HISTORY_H
#include "history.h"
#endif

void zbash_repl() {
    char *line;
    char **args;
    int status;
    char *prompt;

    do {
        printPrompt();
        line = zbash_read_line();

        // Add any command to the history, else if line is nullptr;
        addCommandToHistory(line);
        args = zbash_parse_line(line);
        status = zbash_execute(args);

        free(line);
        free(args);
    } while (status);
}