//
// Created by Lenovo on 2024/6/4.
//

#ifndef ZEAROBASH_ALIAS_AND_UNALIAS_COMMAND_H
#define ZEAROBASH_ALIAS_AND_UNALIAS_COMMAND_H

#include "../alias.h"

static void alias_command_type_help() {
    printf("%s\n", "alias");
    printf("%s\n", "alias [name] = [original-command]");
    printf("%s\n", "alias -H");
    printf("%s\n", "alias --help");
}

#ifndef ZEARO_BASH_ALIAS_COMMAND_H
#define ZEARO_BASH_ALIAS_COMMAND_H

static int zbash_alias_command(char **args) {
    int argc = 0;
    while (args[argc + 1]) argc++;
    if (argc == 0) {
        alias::getInstance()->printTheMap();
        return 1;
    }

    if (argc == 1) {
        if (strcmp(args[1], "-H") == 0 || strcmp(args[1], "--help") == 0) {
            alias_command_type_help();
            return 1;
        } else {
            fprintf(stderr, "zbash: invalid command \"alias\"\n");
            return 1;
        }
    }

    if (argc < 3) {
        fprintf(stderr, "zbash: less arguments to \"alias\"\n");
        return 1;
    } else if (strcmp(args[2], "=") != 0) {
        fprintf(stderr, "zbash: invalid command where is the = ?");
        return 1;
    } else {
        int totalLength = 0;
        for (int i = 3; i <= argc; i ++ ) {
            totalLength += static_cast<int>(strlen(args[i]));
            if (i > 3) {
                totalLength += 1;
            }
        }

        char* mergedString = new char[totalLength + 1];
        int currPosition = 0;

        for (int i = 3; i <= argc; i ++ ) {
            if (i > 3) {
                mergedString[currPosition] = ' ';
                currPosition ++;
            }
            strcpy(mergedString + currPosition, args[i]);
            currPosition += static_cast<int>(strlen(args[i]));
        }
        mergedString[currPosition] = '\0';

        if (alias::getInstance()->addAlias(mergedString, args[1]) == 0) {
            fprintf(stderr, "alias has existed.\n");
        }
        free(mergedString);
    }
    return 1;
}

#endif

static void unalias_command_type_help() {
    printf("%s\n", "unalias [name]");
    printf("%s\n", "unalias -H");
    printf("%s\n", "unalias --help");
}


#ifndef ZEARO_BASH_UNALIAS_COMMAND_H
#define ZEARO_BASH_UNALIAS_COMMAND_H

static int zbash_unalias_command(char **args) {
    int argc = 0;
    while (args[argc + 1]) {
        argc++;
        if (argc > 1) {
            fprintf(stderr, "zbash: to much arguments to \"unalias\"\n");
            return 1;
        }
    }
    if (argc == 0) {
        fprintf(stderr, "zbash: less arguments to \"unalias\"\n");
        return 1;
    } else {
        if (strcmp(args[1], "-H") == 0 || strcmp(args[1], "--help") == 0) {
            unalias_command_type_help();
            return 1;
        }
        if (alias::getInstance()->removeAlias(args[1]) == 0) {
            fprintf(stderr, "alias does not exist.\n");
        }
    }

    return 1;
}

#endif

#endif //ZEAROBASH_ALIAS_AND_UNALIAS_COMMAND_H
