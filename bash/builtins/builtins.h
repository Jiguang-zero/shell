//
// Created by 86158 on 2024/6/2.
//

#ifndef ZEARO_BASH_BUILTINS_H
#define ZEARO_BASH_BUILTINS_H

/**
 * @brief exit zearo bash
 * @return 0. code status.
 */
extern int zbash_exit_command(char**);

#ifndef ZEARO_BASH_BUILTINS_FUNCTIONS_ARRAY
#define ZEARO_BASH_BUILTINS_FUNCTIONS_ARRAY

#include "cd_command.h"

static const char* builtin_command[] = {
#ifdef ZEARO_BASH_CD_COMMAND_H
        "cd",
#endif
        "exit"
};

static int (*builtin_command_function[]) (char**) = {
#ifdef ZEARO_BASH_CD_COMMAND_H
        &zbash_cd_command,
#endif
        &zbash_exit_command,
};

#endif //ZEARO_BASH_BUILTINS_FUNCTIONS_ARRAY

extern int builtin_command_numbers();

#endif //ZEARO_BASH_BUILTINS_H
