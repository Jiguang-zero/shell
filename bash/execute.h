//
// Created by 86158 on 2024/6/2.
//

#ifndef ZEARO_BASH_EXECUTE_H
#define ZEARO_BASH_EXECUTE_H

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#ifndef ZEARO_BASH_INCLUDE_C_STDIO
#define ZEARO_BASH_INCLUDE_C_STDIO
#include "cstdio"
#endif //ZEARO_BASH_INCLUDE_C_STDIO



/**
 * @brief execute the command
 * @param args char**, we parse a command into an args array.
 * @return int. The status code.
 * @instruction args[0] should not be nullptr. So we should make a judgment before we call the function.
 */
extern int zbash_execute(char** args);



/**
 * @brief execute the disk commands.
 * @param args char**. The args of the commands.
 * @return int. The statue code. 0: REPL program will be terminated.
 */
extern int zbash_execute_disk_command(char** args);

#endif //ZEARO_BASH_EXECUTE_H