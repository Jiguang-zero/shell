//
// Created by 86158 on 2024/6/2.
//

#include "builtins.h"

int builtin_command_numbers() {
#ifndef ZEARO_BASH_BUILTINS_FUNCTIONS_ARRAY
    return 0;
#else
    return sizeof (builtin_command) / sizeof (char *);
#endif
}

// exit
int zbash_exit_command(char**) {
    return 0;
}