//
// Created by 86158 on 2024/6/3.
//

#ifndef ZEARO_BASH_HISTORY_COMMAND_H
#define ZEARO_BASH_HISTORY_COMMAND_H

#include "../history.h"
#include "../utils/string_dealing.h"

static void history_command_type_help() {
    printf("%s\n", "When you use history, it will print the commands you input.");
    printf("%s\n", "When you use history -n, it will print the last n commands.");
    printf("%s\n", "When you use no option, it will print the last one command.");
    printf("%s\n", "There should only be one option or none.");
    printf("%s\n", "history [option]: option can be null");
}

/**
 * You can use history --help or history -H for help. \n
 * And when you use history, it will print the last command. \n
 * When you use history -n, it will print the last n commands. \n
 * There should only be 1 options and none. \n
 * history [option]: option can be null
 * @brief history. history command.
 * @param args char**
 * @return 1
 */
static int zbash_history_command(char** args) {
//#ifdef ZEARO_BASH_HISTORY_FILE
    if (args[1] == nullptr) {
        printLastNCommand(1);
    } else if (args[3] != nullptr) {
        fprintf(stderr, "zbash: there should only be one or zero argument to history\n");
    } else if (strcmp(args[1], "-H") == 0 || strcmp(args[1], "--help") == 0) {
        history_command_type_help();
    } else {
       auto option = zearo_bash_shell::utils::string_dealing::getNumberOfOption(args[1]);
       if (option == ERROR_NUMBER_OPTION) {
           fprintf(stderr, "zbash: history -n, n must be number.\n");
       }
       else {
           printLastNCommand(option);
       }
    }
//#endif
    // Builtin command will return 1 whatever results it generates.
    return 1;
}

#endif //ZEARO_BASH_HISTORY_COMMAND_H
