//
// Created by 86158 on 2024/6/2.
//

#ifndef ZEARO_BASH_EXECUTE_H
#define ZEARO_BASH_EXECUTE_H

/**
 * @brief execute the command
 * @param args char**, we parse a command into an args array.
 * @return int. The status code.
 */
extern int zbash_execute(char** args);

#endif //ZEARO_BASH_EXECUTE_H