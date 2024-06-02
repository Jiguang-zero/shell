//
// Created by Lenovo on 2024/6/2.
//
#include <cstdlib>
#include <cstdio>
#include "read.h"

char *zbash_read_line() {
#ifdef ZBASH_USE_STD_GETLINE
    char *line = NULL;
  ssize_t bufsize = 0; // have getline allocate a buffer for us
  if (getline(&line, &bufsize, stdin) == -1) {
    if (feof(stdin)) {
      exit(EXIT_SUCCESS);  // We received an EOF
    } else  {
      perror("zbash: getline\n");
      exit(EXIT_FAILURE);
    }
  }
  return line;
#else
#define ZBASH_RL_BUFSIZE 1024
    int bufsize = ZBASH_RL_BUFSIZE;
    int position = 0;
    char *buffer = (char *) malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "zbash: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (true) {
        // Read a character
        c = getchar();

        if (c == EOF) {
            exit(EXIT_SUCCESS);
        } else if (c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = (char)c;
        }
        position++;

        // If we have exceeded the buffer, reallocate.
        if (position >= bufsize) {
            bufsize += ZBASH_RL_BUFSIZE;
            buffer = (char *) realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "zbash: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
#endif
}