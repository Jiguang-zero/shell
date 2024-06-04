//
// Created by 86158 on 2024/6/4.
//

#include "string_dealing.h"

#include <cstring>
#include <sstream>


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

    void
    string_dealing::transferStringToMap(std::unordered_map<std::string, std::string> &map,
                                        const std::string &string) {
        auto skipSpace = [] (int& i, const std::string& string) {
            while (i < string.length() && string[i] == ' ') {
                i ++ ;
            }
        };
        for (int i = 0; i < string.length(); ) {
            skipSpace(i, string);
            std::string key;
            while (i < string.length() && string[i] != ':') {
                key += string[i ++ ];
            }
            i ++;
            skipSpace(i, string);
            std::string value;
            while (i < string.length() && string[i] != ',') {
                value += string[i ++ ];
            }
            i ++;
            map[key] = value;
        }
    }

    std::string string_dealing::transferMapToString(std::unordered_map<std::string, std::string> &map) {
        std::ostringstream oss;

        for (auto it = map.begin(); it != map.end(); it ++ ) {
            auto pair = *it;
            oss << pair.first;
            oss << ": ";
            oss << pair.second;
            if (std::next(it) != map.end()) {
                oss << ",";
            }
        }

        return oss.str();
    }
} // zearo_bash_shell
// utils