cmake_minimum_required(VERSION 3.16)
project(ZearoBash)

set(CMAKE_CXX_STANDARD 17)

add_executable(zearoBash shell.cpp
        prompt.cpp
        parser.cpp
        read.cpp
        builtins/builtins.cpp
        execute.cpp
        repl.cpp
        CommandCompleter.cpp
        configs.cpp
        history.cpp
        utils/file.cpp
        utils/string_dealing.cpp
        pipeline.cpp
        alias.cpp
        highlighter.cpp
)