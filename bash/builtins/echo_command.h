//
// Created by 86158 on 2024/6/4.
//

#ifndef ZEARO_BASH_ECHO_COMMAND_H
#define ZEARO_BASH_ECHO_COMMAND_H

#include "../utils/file.h"

static void echo_command_type_help() {
    printf("%s\n", "echo [content] [redirect] [goal]");
    puts("There must be more than one argument.");
    puts("Please make sure that there can only be one redirect sign.");
    puts("When you use echo content, it will print the content on the screen.");
    puts("When you use echo content > fileName, it will overwrite the content into the file.");
    puts("And you can also use echo content >> fileName to just add some content to the file.");
    puts("When you use echo < fileName, it will print the file to the screen.");
}

/**
 * TODO: Error Dealing
 * We only provide some very very basic functionalities. \n
 * To see the details, you can use echo -H to view.
 * @brief echo command
 * @param args
 * @return 1
 */
static int zbash_echo_command(char** args) {
    short flag = 0; // 0 not redirect, 1 > redirect, 2 >> redirect, 3 < redirect
    if (args[1] == nullptr) {
        fprintf(stderr, "echo command must have argument.\n");
        return 1;
    }

    if ((strcmp(args[1], "--help") == 0 || strcmp(args[1], "-H") == 0) && args[2] == nullptr) {
        echo_command_type_help();
        return 1;
    }

    char* content = nullptr;
    char* fileName = nullptr;

    auto invalidCommand = [&] () -> void {
        fprintf(stderr, "zbash: invalid command\n");
        free(content);
        free(fileName);
    };


    const char * redirectCommand[] = {
            ">",
            ">>",
            "<"
    };

    bool isRedirectCommand = false;
    for (auto index = args + 1; *index ; index ++ ) {
        for (short i = 0; i < 3 && !isRedirectCommand; i ++ ) {
            if (strcmp(*index, redirectCommand[i]) == 0) {
                isRedirectCommand = true;
                if (flag) {
                    invalidCommand();
                    return 1;
                }
                flag = static_cast<short>(i + 1);
            }
        }
        if (isRedirectCommand) {
            isRedirectCommand = false;
            continue;
        }

        // We should update content after checking flag, or the signs such as '<' will be writen into content.
        if (flag == 0) {
            content = *index;
        }
        else {
            fileName = *index;
            if (*(index + 1)) {
                invalidCommand();
                return 1;
            }
        }
    }

    // Print the content to the screen
    if (flag == 0) {
        printf("%s\n", content);
    } else if (flag == 1 || flag == 2) {
        zearo_bash_shell::utils::File::createFileIfNotExists(fileName);
        if (!content || !fileName) {
            invalidCommand();
            return 1;
        }
        if (flag == 1) zearo_bash_shell::utils::File::overWriteTheFile(fileName, content);
        else zearo_bash_shell::utils::File::addStringToTheEnd(fileName, content);
    } else if (flag == 3) {
        if (!fileName || content) {
            invalidCommand();
            return 1;
        }
        if (!zearo_bash_shell::utils::File::fileExists(fileName)) {
            fprintf(stderr, "zbash builtin: file not found.");
        }
        else {
            zearo_bash_shell::utils::File::printWholeFile(fileName);
        }
    }

    free(content);
    free(fileName);

    return 1;
}

#endif //ZEARO_BASH_ECHO_COMMAND_H
