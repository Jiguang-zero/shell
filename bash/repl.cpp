//
// Created by 86158 on 2024/6/2.
//

#include "repl.h"
#include "prompt.h"

#ifndef ZEARO_BASH_INCLUDE_C_STDLIB
#include <cstdlib>
#endif // ZEARO_BASH_INCLUDE_C_STDLIB

#include "prompt.h"

void zbash_repl() {
    char *line;
    char **args;
    int status;

    do {
        printPrompt();
        line = zbash_read_line();
        char* line_copy = strdup(line);
        args = zbash_parse_line(line);
        status = zbash_execute(line_copy, args);

        free(line);
        free(line_copy);
        free(args);
    } while (status);
}