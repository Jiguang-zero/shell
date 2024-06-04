//
// Created by Lenovo on 2024/6/2.
//
#include <cstdlib>
#include <cstdio>
#include "read.h"

namespace zearo_bash_shell {
    myInput *myInput::getInstance() {
        if (instance == nullptr) {
            instance = new myInput();
        }
        return instance;
    }

    void myInput::getCursorPosition(int *row, int *col) {
        printf("\033[6n");
        scanf("\033[%d;%dR", row, col);
    }

    char *myInput::inputOneLine() {
        int currPosition = 0;
        string line;
        int ch;


        initTerminalInputWay();
        while (true) {
            // Read a character
            ch = getchar();

            if (ch == EOF) {
                recoverTerminalInputWay();
                exit(EXIT_SUCCESS);
            }
            else if (ch == '\n') {
                return inputEnter(line);
            }
            else if (ch == '\t') {
                continue;
            }

                // When input backspace or del
                // We test that when we enter backspace , it will print 127.
            else if (ch == 127 ) {
                if (line.empty()) {
                    continue;
                }

                inputBackSpace(line);
            }
            else {
                putchar(ch);
                line.push_back(static_cast<char>(ch));
                currPosition ++;
            }
        }

    }
    myInput* myInput::instance = nullptr;

    void myInput::initTerminalInputWay() {
        tcgetattr(STDIN_FILENO, &old_t);
        new_t = old_t;
        new_t.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_t);
    }

    void myInput::recoverTerminalInputWay() {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_t);
    }

    void myInput::inputBackSpace(string &line) {
        int row, col;
        getCursorPosition(&row, &col);
        if (col == 1) {
            printf("\033[1F\033[999C");
            putchar(' ');
        }
        else {
            printf("\b \b");
        }
        line.pop_back();
    }

    char* myInput::inputEnter(string &line) {
        char * res = new char[line.length() + 1];
        putchar('\n');
        strcpy(res, line.c_str());
        recoverTerminalInputWay();
        return res;
    }

    [[maybe_unused]] int myInput::getCursorColOnly() {
        int row, col;
        getCursorPosition(&row, &col);
        return col;
    }
}


#ifndef ZEARO_BASH_GET_LINE
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
        } else if (c == '\t') {
            // printf("****");
        } else {
            buffer[position] = (char) c;
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
#endif