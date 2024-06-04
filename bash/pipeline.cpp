//
// Created by Lenovo on 2024/6/4.
//
#include "pipeline.h"

int pipe_command(char *buf) {
    // Find the position of the pipe character
    int pos = 0;
    for (int i = 0; i < strlen(buf); i++) {
        if (buf[i] == '|') { // && buf[i + 1] == ' '
            pos = i;
            break;
        }
    }

    int fd[2];
    pid_t pid;

    char writepipe[buffsize];
    char readpipe[buffsize];
    memset(writepipe, 0, buffsize);
    memset(readpipe, 0, buffsize);


    // Split the command into writepipe and readpipe
    for (int i = 0; i < strlen(buf); i++) {
        if (i < pos) {
            writepipe[i] = buf[i];
        } else if (i > pos) {
            readpipe[i - pos - 1] = buf[i];
        }
    }

    writepipe[pos] = '\0';
    readpipe[strlen(buf) - pos - 1] = '\0';

    auto p = writepipe;
    while (*p) {
        std::cout << *p;
        p++;
    }
    p = readpipe;
    while (*p) {
        std::cout << *p;
        p++;
    }


    if (pipe(fd) < 0) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        close(fd[0]);
        close(1);
        dup(fd[1]);
        close(fd[1]);
        auto args = zbash_parse_line(writepipe);
        execvp(args[0], args);
        return 0;
    } else {
        int status;
        waitpid(pid, &status, 0);
        int err = WEXITSTATUS(status);
        if (err) {
            printf("Error: %s\n", strerror(err));
        }
        close(fd[1]);
        close(0);
        dup(fd[0]);
        close(fd[0]);
        auto args = zbash_parse_line(readpipe);
        execvp(args[0], args);
        return 0;
    }
}
