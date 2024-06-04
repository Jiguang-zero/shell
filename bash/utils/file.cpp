//
// Created by 86158 on 2024/6/4.
//

#include "file.h"

namespace zearo_bash_shell::utils {

    std::vector<std::string> File::getLastNLines(const std::string &fileName, int n) {
        std::vector<std::string> lines;
        std::string line;

        std::fstream file(fileName);
        if (!file.is_open()) {
            fprintf(stderr, "file open error\n");
            return lines;
        }

        while (std::getline(file, line)) {
            lines.emplace_back(line);
            if (lines.size() > n) {
                lines.erase(lines.begin());
            }
        }
        file.close();

        return lines;
    }

    void File::addStringToTheEnd(const std::string &fileName, char *line) {
        std::ofstream file(fileName, std::ios::app);
        if (file.is_open()) {
            file << line << std::endl;
            file.close();
        }
        else {
            fprintf(stderr, "file open error.");
        }
    }

}
