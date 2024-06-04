//
// Created by Lenovo on 2024/6/4.
//

#ifndef ZEAROBASH_COMMANDCOMPLETER_H
#define ZEAROBASH_COMMANDCOMPLETER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>

using std::string;
using std::vector;
using std::unordered_map;
using std::pair;
namespace fs = std::filesystem;

namespace zbashCommandCompleter {
    class CommandCompleter {
    private:
        // private constructor
        CommandCompleter();

        ~CommandCompleter() = default;

        static CommandCompleter *instance;

    public:
        // delete copy for single instance
        const CommandCompleter &operator=(const CommandCompleter &_) = delete;

        CommandCompleter(const CommandCompleter &_) = delete;

    public:
        /**
         * @brief get the only instance of this class.
         * @return
         */
        static CommandCompleter *getInstance();


    private:
        int prevCh;
        int completeLength;
        int curIndex;
        vector<string> temp;
        unordered_map<string, vector<string>> options;

        static vector<string> split(const string &str, const string &delim);

        static string getCurrentDir();

        static vector<string> getFilesInDir(const string &dir_path, const string &prefix);

        static pair<string, string> getDirAndPrefix(const string &inputDir);

    public:

        // 第一个int 为 index, 第二个int 为要抹去的长度
        pair<int, int> completePart(string &str);

        void reInitialize();

        void setPrevCh(int ch);

        int getPrevCh() const;

        const string &getTemp(int index);
    };

} // zbashCommandCompleter

#endif //ZEAROBASH_COMMANDCOMPLETER_H
