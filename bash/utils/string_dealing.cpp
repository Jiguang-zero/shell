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
        for (auto i = 1; i < len; i++) {
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
        auto alias = split(string, ",");
        for (const auto &alia: alias) {
            std::string key, value;

            int l = -1, r = (int) alia.length();
            while (alia[++l] != ':') {}
            key = alia.substr(0, l);

            while (alia[++l] == ' ') {}
            while (alia[--r] == ' ') {}
            value = alia.substr(l, r - l + 1);

            map[key] = value;
        }
    }

    std::string string_dealing::transferMapToString(std::unordered_map<std::string, std::string> &map) {
        std::ostringstream oss;

        for (auto it = map.begin(); it != map.end(); it++) {
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

    std::vector<std::string> string_dealing::split(const std::string &str, const std::string &delim) {
        std::vector<std::string> res;
        if (str.empty()) return res;
        size_t prev = 0, pos = 0;
        do {
            pos = str.find(delim, prev);
            if (pos == std::string::npos) pos = str.length();
            std::string substr = str.substr(prev, pos - prev);
            if (!substr.empty()) res.emplace_back(substr);
            prev = pos + delim.length();
        } while (pos < str.length() && prev < str.length());
        return res;

    }
} // zearo_bash_shell
// utils