//
// REPL: read, eval, print and loop. We take this concept from the interpreter.
// Created by 86158 on 2024/6/2.
//

#ifndef ZEARO_BASH_REPL_H
#define ZEARO_BASH_REPL_H

#ifndef ZEARO_BASH_INCLUDE_C_STDIO
#include "cstdio"
#endif //ZEARO_BASH_INCLUDE_C_STDIO

#ifndef ZEARO_BASH_INCLUDE_C_STDLIB
#include "cstdlib"
#endif // ZEARO_BASH_INCLUDE_C_STDLIB

#include "read.h"
#include "parser.h"
#include "execute.h"

/**
 * @brief ZearoBash repl, the loop function of the ZearoBash.
 */
extern void zbash_repl();

#endif //ZEARO_BASH_REPL_H
