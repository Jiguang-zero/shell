//
// Created by 86158 on 2024/6/4.
//

#include "string_dealing.h"

#include <cstring>


namespace zearo_bash_shell::utils {
    int string_dealing::getNumberOfOption(char *option) {
        auto len = std::strlen(option);
        if (len <= 1) {
            return ERROR_NUMBER_OPTION;
        }
        if (option[0] != '-') {
            return ERROR_NUMBER_OPTION;
        }
        int ans = 0;
        for (auto i = 1; i < len; i ++ ) {
            if (!isDigit(option[i])) {
                return ERROR_NUMBER_OPTION;
            }
            ans = ans * 10 + (option[i] - '0');
        }

        return ans;
    }

    bool string_dealing::isDigit(char character) {
        return character <= '9' && character >= '0';
    }
} // zearo_bash_shell
// utils