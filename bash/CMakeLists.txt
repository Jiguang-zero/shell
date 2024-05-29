cmake_minimum_required(VERSION 3.26)
project(bash-shell)

set(CMAKE_CXX_STANDARD 23)

add_executable(bash shell.cpp
)