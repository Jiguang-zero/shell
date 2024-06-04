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
        std::istringstream iss(string);
        std::string token;

        while (std::getline(iss, token, ',')) {
            std::istringstream tokenStream(token);
            std::string key, value;
            if (std::getline(tokenStream, key, ':') && std::getline(tokenStream, value)) {
                key.erase(0, key.find_first_not_of(' '));
                key.erase(key.find_last_not_of(' ' + 1));
                value.erase(0, value.find_last_not_of(' '));
                value.erase(value.find_last_not_of(' ') + 1);
                map[key] = value;
            }
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