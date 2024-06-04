//
// Created by 86158 on 2024/6/4.
//

#include "file.h"
#include <vector>

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

    bool File::fileExists(const std::string &filename) {
        std::ifstream file(filename);
        return file.good();
    }

    void File::createFileIfNotExists(const std::string &filename) {
        if (!fileExists(filename)) {
            std::ofstream file(filename);
            if (file.is_open()) {
                file.close();
            } else {
                fprintf(stderr, "create file error.\n");
            }
        }
    }

    void File::overWriteTheFile(const std::string &fileName, char *content) {
        std::ofstream file(fileName);
        if (file.is_open()) {
            file << content << std::endl;
            file.close();
        }
        else {
            fprintf(stderr, "file open error.");
        }
    }

    void File::printWholeFile(const std::string &fileName) {
        std::string line;

        std::fstream file(fileName);
        if (!file.is_open()) {
            fprintf(stderr, "file open error\n");
        }

        while (std::getline(file, line)) {
            puts(line.c_str());
        }
        file.close();
    }

    std::string File::getSubstringAfterPrefix(const std::string &fileName, const std::string& content) {
        std::string line;

        std::fstream file(fileName);
        if (!file.is_open()) {
            fprintf(stderr, "file open error\n");
        }
        auto prefix = content + ": ";
        while (std::getline(file, line)) {
            if (line.find(prefix) == 0) {
                file.close();
                return line.substr(prefix.length());
            }
        }
        file.close();
        return "";
    }

    void File::replaceLineInFileWithPrefix(const std::string &fileName, const std::string &prefix,
                                           const std::string &newLine) {
        std::string line;
        std::vector<std::string> lines;

        std::fstream file(fileName);
        if (!file.is_open()) {
            fprintf(stderr, "file open error\n");
        }
        auto newPrefix = prefix + ": ";
        while (std::getline(file, line)) {
            if (line.find(newPrefix) == 0) {
                lines.emplace_back(newPrefix + newLine);
                continue;
            }
            lines.emplace_back(line);
        }
        file.close();

        // write into the file again
        std::ofstream oFile(fileName);
        for (const auto & l : lines) {
            printf("%s\n", l.c_str());
            oFile << l << std::endl;
        }
        oFile.close();
    }

}
