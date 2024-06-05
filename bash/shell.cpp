//
// Created by 86158 on 2024/5/29.
//
#include "repl.h"
#include "configs.h"

static void printHello();

/**
 * @brief The entry of the program, ZearoBash.
 * @return status code
 */
int main() {
    // greeting
    printHello();

    // Load configs.
    loadConfigs();

    // Run command loop;
    zbash_repl();

    return EXIT_SUCCESS;
}

static void printHello() {
    std::string greeting = "\tWelcome to ZEARO BASH, please feel free to use.";
    printf("%s\n", greeting.c_str());
}
