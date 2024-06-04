//
// Created by 86158 on 2024/6/2.
//

#ifndef ZEARO_BASH_INCLUDE_BUILTINS
#define ZEARO_BASH_INCLUDE_BUILTINS
#include "builtins.h"
#endif //ZEARO_BASH_INCLUDE_BUILTINS


const char* builtin_command[] = {
#ifdef ZEARO_BASH_CD_COMMAND_H
        "cd",
#endif
#ifdef ZEARO_BASH_HISTORY_COMMAND_H
        "history",
#endif
#ifdef ZEARO_BASH_ECHO_COMMAND_H
        "echo",
#endif
        "help",
        "exit"
};


int (*builtin_command_function[]) (char**) = {
#ifdef ZEARO_BASH_CD_COMMAND_H
        &zbash_cd_command,
#endif
#ifdef ZEARO_BASH_HISTORY_COMMAND_H
        &zbash_history_command,
#endif
#ifdef ZEARO_BASH_ECHO_COMMAND_H
        &zbash_echo_command,
#endif
        &zbash_help_command,
        &zbash_exit_command,
};

int builtin_command_numbers() {
#ifndef ZEARO_BASH_BUILTINS_FUNCTIONS_ARRAY
//    return 0;
#else
    return sizeof (builtin_command) / sizeof (char *);
#endif
}

// exit
int zbash_exit_command(char**) {
    return 0;
}

//no args we need
int zbash_help_command(char**) {
    printf("We have provided the following built-in commands:\n");

    for (int i = 0; i < builtin_command_numbers(); i ++ ) {
        printf("%10s\n", builtin_command[i]);
    }

    printf("For disk programs, please use [man] command.\n");

    // The program will keep on.
    return 1;
}

