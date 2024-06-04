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
         * @brief print the while file
         * @param fileName
         */
        static void printWholeFile(const std::string& fileName);

        /**
         * @brief Append a string_dealing to a file.
         * @param fileName
         * @param line
         */
        static void addStringToTheEnd(const std::string& fileName, char* line);

        /**
         * @brief overwrite the file
         * @param fileName
         * @param content char*
         */
        static void overWriteTheFile(const std::string& fileName, char* content);

        /**
         * @brief check a file exists or not
         * @param filename
         * @return
         */
        static bool fileExists(const std::string& filename);

        /**
         * @brief check the file exist a line which begins with "content: "
         * @param fileName
         * @param content
         * @return if find not a line, return ""; return the line which does not include content:
         */
        static std::string getSubstringAfterPrefix(const std::string& fileName, const std::string& content);

        /**
         * @brief replace line with prefix.
         * @param fileName
         * @param prefix
         * @param newLine
         * For example, replaceLineInFileWithPrefix("example.txt", "prefix", "newline") \n
         * And the new line in file will be: prefix: newline
         */
        static void replaceLineInFileWithPrefix(
                const std::string& fileName,
                const std::string& prefix,
                const std::string& newLine);

        static void createFileIfNotExists(const std::string& filename);
    };
}


#endif //ZEARO_BASH_UTILS_FILE_H
