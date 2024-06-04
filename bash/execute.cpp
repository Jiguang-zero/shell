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

#include "pipeline.h"

bool isPipeCommand(char *line) {
    for (int i = 0; i < strlen(line); i++) {
        if (line[i] == '|') {
            return true;
        }
    }
    return false;
}

bool isBackgroundCommand(char *line) {
    for (int i = 0; i < strlen(line); i++) {
        if (line[i] == '&') {
            return true;
        }
    }
    return false;
}

bool isRedirectCommand(char *line) {
    for (int i = 0; i < strlen(line); i++) {
        if (line[i] == '<' || line[i] == '>') {
            return true;
        }
    }
    return false;
}


int zbash_execute(char *line, char **args) {
    if (args == nullptr || args[0] == nullptr) {
        return 1;
    }

    // 外部命令执行的模式
    int mode = 0;

    if (isPipeCommand(line)) {
        pid_t pid = fork();
        if (pid == 0) {
            return pipe_command(line);
        } else {
            int status;
            waitpid(pid, &status, WUNTRACED);
        }
    } else if (isBackgroundCommand(line)) {
        // 在后台运行程序
        mode = 1;
    }
    /*
     // We just implemented the redirection of the echo function
    else if (isRedirectCommand(line)) {
        // 执行重定向命令
    }
    */
    else {
        // 执行内置命令
        for (int i = 0; i < builtin_command_numbers(); i++) {
            if (strcmp(args[0], builtin_command[i]) == 0) {
                return (*builtin_command_function[i])(args);
            }
        }
    }
    // 执行外部命令, mode为 0表示前台执行，mode为 1表示后台执行
    return zbash_execute_disk_command(args, mode);
}

int zbash_execute_disk_command(char **args, int mode) {
    pid_t pid;
    int status;

    pid = fork();
    // Child process.
    if (pid == 0) {
        if (mode == 1) {
            setsid();
            fclose(stdin);
            fclose(stdout);
            fclose(stderr);
        }

        if (execvp(args[0], args) == -1) {
            // Here we use "perror" to show the error details of the function.
            perror("zbash execute error");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Fork error.
        perror("zbash execute error");
    }
        // Parent process
    else {
        if (mode == 1) {
            // 打印子进程的PID
            printf("PID: %d\n", pid);
        } else {
            do {
                // WUNTRACED: If the child process enters a situation where execution is suspended,
                // it returns immediately
                waitpid(pid, &status, WUNTRACED);
            }
                // check the child process exited successfully or is terminated by signal or not.
            while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }

    // The program will continue.
    return 1;
}

