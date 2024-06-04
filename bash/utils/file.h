//
// Created by 86158 on 2024/6/4.
//

#ifndef ZEARO_BASH_UTILS_FILE_H
#define ZEARO_BASH_UTILS_FILE_H

#include <vector>
#include <fstream>

namespace zearo_bash_shell::utils {
    class File {
    public:
        /**
         * @brief Get last N lines of the file.
         * @param fileName The name of the file. const std::string_dealing&
         * @param n  int
         * @return
         */
        static std::vector<std::string> getLastNLines(const std::string& fileName, int n);


        /**
         * @brief Append a string_dealing to a file.
         * @param fileName
         * @param line
         */
        static void addStringToTheEnd(const std::string& fileName, char* line);
    };
}


#endif //ZEARO_BASH_UTILS_FILE_H
