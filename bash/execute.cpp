//
// Created by 86158 on 2024/6/2.
//

#include "execute.h"

#ifndef ZEARO_BASH_INCLUDE_C_STDLIB
#define ZEARO_BASH_INCLUDE_C_STDLIB
#include "cstdlib"
#endif // ZEARO_BASH_INCLUDE_C_STDLIB


#ifndef ZEARO_BASH_INCLUDE_BUILTINS
#include "builtins/builtins.h"
#endif //ZEARO_BASH_INCLUDE_BUILTINS


int zbash_execute(char** args) {
    if (args == nullptr || args[0] == nullptr) {
        return 1;
    }

    for (int i = 0; i < builtin_command_numbers(); i ++ ) {
        if (strcmp(args[0], builtin_command[i]) == 0) {
            return (*builtin_command_function[i])(args);
        }
    }

    return zbash_execute_disk_command(args);
}

int zbash_execute_disk_command(char** args) {
    pid_t pid;
    int status;

    pid = fork();
    // Child process.
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            // Here we use "perror" to show the error details of the function.
            perror("zbash execute error");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) {
        // Fork error.
        perror("zbash execute error");
    }
    // Parent process
    else {
        do {
            // WUNTRACED: If the child process enters a situation where execution is suspended,
            // it returns immediately
            waitpid(pid, &status, WUNTRACED);
        }
        // check the child process exited successfully or is terminated by signal or not.
        while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    // The program will continue.
    return 1;
}
