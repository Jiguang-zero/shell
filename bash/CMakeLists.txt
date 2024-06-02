cmake_minimum_required(VERSION 3.16)
project(ZearoBash)

set(CMAKE_CXX_STANDARD 17)

add_executable(bash shell.cpp
        prompt.cpp
        repl.h
        repl.cpp
        read.h
        parser.h
        execute.h
        execute.cpp
        builtins/builtins.h
        builtins/cd_command.h
        parser.cpp
        read.cpp
)