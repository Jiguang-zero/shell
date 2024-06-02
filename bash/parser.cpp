//
// Created by Lenovo on 2024/6/2.
//
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "parser.h"

#define ZBASH_TOK_BUFSIZE 64
#define ZBASH_TOK_DELIM " \t\r\n\a"

char** zbash_parse_line(char* line) {
    int bufsize = ZBASH_TOK_BUFSIZE, position = 0;
    char **tokens = (char **) malloc(bufsize * sizeof(char *));
    char *token, **tokens_backup;

    if (!tokens) {
        fprintf(stderr, "zbash: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, ZBASH_TOK_DELIM);
    while (token != nullptr) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += ZBASH_TOK_BUFSIZE;
            tokens_backup = tokens;
            tokens = (char **) realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                free(tokens_backup);
                fprintf(stderr, "zbash: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(nullptr, ZBASH_TOK_DELIM);
    }
    tokens[position] = nullptr;
    return tokens;
}