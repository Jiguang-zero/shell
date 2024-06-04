//
// Created by 86158 on 2024/6/4.
//

#ifndef ZEARO_BASH_UTILS_STRING_H
#define ZEARO_BASH_UTILS_STRING_H

#define ERROR_NUMBER_OPTION (-1)

namespace zearo_bash_shell::utils {
    class string_dealing {
    public:
        /**
         * @brief Get the number of the option: -n , and it will get n
         * @param option char*
         * @return n, int. And when the option does not satisfy the condition, it will return -1;
         */
        static int getNumberOfOption(char* option);

        static bool isDigit(char character);
    };

} // zearo_bash_shell
// utils

#endif //ZEARO_BASH_UTILS_STRING_H
