//
// Created by 86158 on 2024/6/2.
//

#ifndef ZEARO_BASH_CD_COMMAND_H
#define ZEARO_BASH_CD_COMMAND_H

#ifndef ZEARO_BASH_INCLUDE_C_STDIO
#define ZEARO_BASH_INCLUDE_C_STDIO
#include <cstdio>
#endif //ZEARO_BASH_INCLUDE_C_STDIO

#include <sys/unistd.h>

/**
 * cd command: cd [path]. There should only be one argument of cd command.
 * And this command will return 1 as repl will keep on.
 * @brief builtin function. cd [path]
 * @param args char**. There can only be two string in args.
 * @return int code status, The command will return 1 whatever results. The repl will keep on.
 */
int zbash_cd_command(char** args) {
    if (args[1] == nullptr) {
        fprintf(stderr, "zbash: expected argument to \"cd\"\n");
    }
    if (args[2] != nullptr) {
        fprintf(stderr, "zbash: there should only be one argument to \"cd\" command\n");
    }
    else {
        if (chdir(args[1]) != 0) {
            perror("zbash builtin");
        }
    }
    return 1;
}

#endif //ZEARO_BASH_CD_COMMAND_H
