//
// Created by 86158 on 2024/6/4.
//

#ifndef ZEARO_BASH_HISTORY_H
#define ZEARO_BASH_HISTORY_H

#include "configs.h"

//#ifdef ZEARO_BASH_HISTORY_FILE

#include "utils/file.h"

/**
 * @brief get the last n commands in history file
 * @param n int
 */
extern void printLastNCommand(int n);

/**
 * @brief add a command into history file
 * @param command char*
 */
extern void addCommandToHistory(char* command);

//#endif


#endif //ZEARO_BASH_HISTORY_H
