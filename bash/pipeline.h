//
// Created by Lenovo on 2024/6/4.
//

#ifndef ZEAROBASH_PIPELINE_H
#define ZEAROBASH_PIPELINE_H

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include "parser.h"

#define buffsize 1024

extern int pipe_command(char *buf);

#endif //ZEAROBASH_PIPELINE_H
