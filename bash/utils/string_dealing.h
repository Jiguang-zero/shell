//
// Created by 86158 on 2024/6/4.
//

#ifndef ZEARO_BASH_UTILS_STRING_H
#define ZEARO_BASH_UTILS_STRING_H

#define ERROR_NUMBER_OPTION (-1)

#include <unordered_map>
#include <string>
#include <vector>

namespace zearo_bash_shell::utils {
    class string_dealing {
    public:
        /**
         * @brief Get the number of the option: -n , and it will get n
         * @param option char*
         * @return n, int. And when the option does not satisfy the condition, it will return -1;
         */
        static int getNumberOfOption(char* option);

        /**
         * @brief transfer string to map. The string must be with the format like: a: b, c: d
         * @param map
         * @param string
         */
        static void
        transferStringToMap(std::unordered_map<std::string, std::string>& map,
                            const std::string& string);

        /**
         * @brief transfer map to string
         * @param map
         * @return std::string, such as a: b, c: d
         */
        static std::string transferMapToString(std::unordered_map<std::string, std::string>&map);

        static bool isDigit(char character);

        static std::vector<std::string> split(const std::string &str, const std::string &delim);

    };

} // zearo_bash_shell
// utils

#endif //ZEARO_BASH_UTILS_STRING_H
