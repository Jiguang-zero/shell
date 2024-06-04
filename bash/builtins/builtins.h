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

/**
 * @brief help command. Show how to use this shell. Show the number of builtins we provided.
 * @return 1. code status. REPL will keep on.
 */
extern int zbash_help_command(char**);

#ifndef ZEARO_BASH_BUILTINS_FUNCTIONS_ARRAY
#define ZEARO_BASH_BUILTINS_FUNCTIONS_ARRAY

#include "cd_command.h"
#include "history_command.h"
#include "echo_command.h"

extern const char* builtin_command[];

extern int (*builtin_command_function[]) (char**);

#endif //ZEARO_BASH_BUILTINS_FUNCTIONS_ARRAY

extern int builtin_command_numbers();

#endif //ZEARO_BASH_BUILTINS_H
