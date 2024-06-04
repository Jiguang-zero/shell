//
// Created by 86158 on 2024/5/29.
//
#include <cstdio>
#include <cstdlib>
#include <pwd.h>
#include <climits>
#include <string>
#include "prompt.h"

void printPrompt() {
    // get the username
    struct passwd *pw = getpwuid(getuid());
    const char *username = pw->pw_name;

    // get the hostname
    char hostname[HOST_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);

    // get the current working dictionary
    char cwd[PATH_MAX];
    getcwd(cwd, PATH_MAX);
    std::string homeDir = getenv("HOME");
    std::string currentDir(cwd);

    // 如果当前工作目录是家目录的子目录，则用~代替家目录路径显示
    if (currentDir.find(homeDir) != std::string::npos) {
        currentDir.replace(0, homeDir.length(), "~");
    }

    // 获取当前用户的操作权限
    char promptCharacter = getuid() ? '$' : '#';

    printf("%s@%s:%s %c ", username, hostname, currentDir.c_str(), promptCharacter);
}
