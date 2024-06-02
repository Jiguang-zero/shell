//
// Created by 86158 on 2024/6/2.
//

#include "execute.h"

#ifndef ZEARO_BASH_INCLUDE_C_STDLIB
#define ZEARO_BASH_INCLUDE_C_STDLIB
#include "cstdlib"
#endif // ZEARO_BASH_INCLUDE_C_STDLIB

int zbash_execute(char** args) {
    if (args == nullptr || args[0] == nullptr) {
        return 1;
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
            waitpid(pid, &status, WUNTRACED);
        }
    }
}
