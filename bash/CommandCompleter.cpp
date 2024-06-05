//
// Created by Lenovo on 2024/6/4.

#include "CommandCompleter.h"

namespace zbashCommandCompleter {
    vector<string> CommandCompleter::split(const std::string &str, const std::string &delim) {
        vector<string> res;
        if (str.empty()) return res;
        size_t prev = 0, pos;
        do {
            pos = str.find(delim, prev);
            if (pos == string::npos) pos = str.length();
            string substr = str.substr(prev, pos - prev);
            if (!substr.empty()) res.emplace_back(substr);
            prev = pos + delim.length();
        } while (pos < str.length() && prev < str.length());
        return res;
    }

    string CommandCompleter::getCurrentDir() {
        std::error_code ec;
        fs::path current_dir = fs::current_path(ec);

        if (ec) {
            //            std::cerr << "Error: " << ec.message() << std::endl;
            return "";
        }

        return current_dir.string();
    }

    vector<string> CommandCompleter::getFilesInDir(const std::string &dir_path, const std::string &prefix) {
        vector<string> files;
        fs::path path(dir_path);

        if (!fs::exists(path)) {
            //            std::cerr << "Error: Directory does not exist" << std::endl;
            return files;
        }

        if (!fs::is_directory(path)) {
            //            std::cerr << "Error: Not a directory" << std::endl;
            return files;
        }

        for (const auto &entry: fs::directory_iterator(path)) {
            if (fs::is_regular_file(entry.path()) || fs::is_directory(entry.path())) {
                if (entry.path().filename().string().compare(0, prefix.length(), prefix) == 0)
                    files.emplace_back(entry.path().filename().string());
            }
        }
        return files;
    }

    pair<string, string> CommandCompleter::getDirAndPrefix(const std::string &inputDir) {
        if (inputDir.empty()) return {"", ""};
        auto i = inputDir.find_last_of('/');
        string dir, prefix;
        dir = inputDir.substr(0, i + 1);
        prefix = inputDir.substr(i + 1);
        if (inputDir[0] != '/') dir = getCurrentDir() + "/" + dir;
        return {dir, prefix};
    }

    CommandCompleter::CommandCompleter() {
        prevCh = ' ';
        completeLength = 0;
        curIndex = -1;
        temp = {};
        options = {
                // 内部命令
                {"cd",      {}},
                {"history", {}},
                {"help",    {}},
                {"exit",    {}},
                {"clear",   {}},
                {"echo",    {}},
                {"alias",   {}},
                {"unalias", {}},

                // 外部命令
                {"ls",      {"-l", "-a", "-h", "-t", "-r", "-S", "-R", "-d", "-g", "-i", "-F", "-m", "-o", "-p", "-q"}},
                {"cat",     {"-b", "-e", "-n", "-s", "-t", "-v", "-A", "-E", "-T", "-u"}},
                {"cp",      {"-b", "-f", "-i", "-n", "-p", "-r", "-v", "-a", "-c", "-l", "-s", "-u"}},
                {"mv",      {"-b", "-f", "-i", "-n", "-p", "-r", "-v", "-u", "-t", "-s", "-l"}},
                {"rm",      {"-b", "-f", "-i", "-r", "-v", "-d", "-P", "-R", "-v"}},
                {"more",    {"-c", "-d", "-e", "-f", "-i", "-I", "-n", "-N", "-p", "-s", "-t", "-v", "-w", "-z", "-M", "-S"}},
                {"diff",    {"-b", "-B", "-C", "-E", "-F", "-I", "-L", "-N", "-P", "-Q", "-R", "-U", "-V", "-W", "-X", "-a",
                                    "-c", "-d", "-e", "-f", "-i", "-n", "-p", "-q", "-r", "-s", "-t", "-u", "-v", "-w", "-x", "-y",
                                    "-Z", "-H", "-M", "-T", "-O", "-Y", "-K", "-G", "-J", "-U"}},
                {"grep",    {"-i", "-r", "-n", "-v", "-w", "-c", "-l", "-E", "-A", "-B", "-C", "-f", "-h", "-o", "-q", "-s"}},
                {"mkdir",   {"-p", "-v", "-m", "-Z", "-v", "-Z", "-Z", "-Z", "-Z"}},
                {"touch",   {"-a", "-c", "-m", "-r", "-t", "-d", "-u", "-v"}},
                {"chmod",   {"-c", "-f", "-v", "-R", "-r", "-x", "-w", "-u", "-g"}},
                {"chown",   {"-v", "-f", "-R", "-H", "-L", "-P", "-c", "-h", "-v"}},
                {"ps",      {"-a", "-u", "-x", "-e", "-f", "-l", "-p", "-r", "-t"}},
        };
    }

    pair<int, int> CommandCompleter::completePart(std::string &str) {
        if (str.empty()) return {-1, 0};
        vector<string> enteredPart = split(str, " ");

        // 连续补全
        if (prevCh == '\t') {
            if (curIndex != -1) {
                curIndex = (curIndex + 1) % (int) temp.size();
                int t = completeLength;
                completeLength = (int) temp[curIndex].length();
                return {curIndex, t};
            }
            return {-1, 0};
        }

        // 补全"命令"
        if (enteredPart.empty() || (enteredPart.size() == 1 && str.back() != ' ')) {
            if (enteredPart.empty()) {
                for (const auto &option: options) {
                    temp.emplace_back(option.first);
                }
            } else {
                for (const auto &option: options) {
                    if (option.first.compare(0, enteredPart[0].length(), enteredPart[0]) == 0) {
                        temp.emplace_back(option.first.substr(enteredPart[0].length()));
                    }
                }
            }
        }

        // 补全"选项"
        if (enteredPart.size() > 1 && str.back() != ' ' && enteredPart.back()[0] == '-') {
            string command = enteredPart[0];
            for (const string &option: options[command]) {
                if (option.compare(0, enteredPart.back().length(), enteredPart.back()) == 0) {
                    temp.emplace_back(option.substr(enteredPart.back().length()));
                }
            }
        }

        // 补全目录
        if ((!enteredPart.empty() && str.back() == ' ') || (enteredPart.size() > 1 && enteredPart.back()[0] != '-')) {
            if (str.back() == ' ') {
                string dir = getCurrentDir();
                string prefix;
                temp = getFilesInDir(dir, prefix);
            } else {
                const string &inputDir = enteredPart.back();
                auto p = getDirAndPrefix(inputDir);
                string dir = p.first;
                string prefix = p.second;
                if (!dir.empty()) {
                    auto fileNames = getFilesInDir(dir, prefix);
                    for (auto &fileName: fileNames) {
                        temp.emplace_back(fileName.substr(prefix.length()));
                    }
                }
            }
        }

        if (temp.empty()) return {-1, 0};
        else {
            completeLength = (int) temp[0].length();
            curIndex = 0;
            return {0, 0};
        }
    }

    void CommandCompleter::reInitialize() {
        prevCh = ' ';
        completeLength = 0;
        curIndex = -1;
        temp = {};
    }

    void CommandCompleter::setPrevCh(int ch) {
        prevCh = ch;
    }

    int CommandCompleter::getPrevCh() const {
        return prevCh;
    }

    const string &CommandCompleter::getTemp(int index) {
        static const string emptyString;
        if (index < 0 || index >= temp.size()) return emptyString;
        return temp[index];
    }

    CommandCompleter *CommandCompleter::instance = nullptr;

    CommandCompleter *CommandCompleter::getInstance() {
        if (instance == nullptr) {
            instance = new CommandCompleter();
        }
        return instance;
    }

} // zbashCommandCompleter