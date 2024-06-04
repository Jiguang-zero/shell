//
// Created by 86158 on 2024/6/2.
//

#ifndef ZEARO_BASH_CD_COMMAND_H
#define ZEARO_BASH_CD_COMMAND_H

#include <cstdio>

#include <cstring>

#include <sys/unistd.h>

/**
 * Type help instruction of cd command.
 */
static void cd_command_type_help() {

}

/**
 * cd command: cd [path] || cd [option]. There should only be one argument of cd command.
 * And this command will return 1 as repl will keep on.
 * @brief builtin function. cd [path]
 * @param args char**. There can only be two string_dealing in args.
 * @return int. code status, The command will return 1 whatever results. The repl will keep on.
 */
static int zbash_cd_command(char** args) {
    if (args[1] == nullptr) {
        fprintf(stderr, "zbash: expected argument to \"cd\"\n");
    }
    else if (args[2] != nullptr) {
        fprintf(stderr, "zbash: there should only be one argument to \"cd\" command\n");
    }
    else if (strcmp(args[1], "-H") == 0 || strcmp(args[1], "--help") == 0) {
        cd_command_type_help();
    }
    else {
        if (chdir(args[1]) != 0) {
            perror("zbash builtin");
        }
    }
    return 1;
}



#endif //ZEARO_BASH_CD_COMMAND_H
