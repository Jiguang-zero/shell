//
// Created by 86158 on 2024/5/29.
//
#include "repl.h"
#include "configs.h"

/**
 * @brief The entry of the program, ZearoBash.
 * @return status code
 */
int main() {
    // Load configs.
    loadConfigs();

    // Run command loop;
    zbash_repl();

    return EXIT_SUCCESS;
}