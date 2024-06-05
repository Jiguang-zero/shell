//
// Created by Lenovo on 2024/6/5.
//

#ifndef ZEAROBASH_HIGHLIGHTER_H
#define ZEAROBASH_HIGHLIGHTER_H

#include <vector>
#include <string>

namespace zbashHighLighter {
    class HighLighter {
    private:
        HighLighter() = default;

        ~HighLighter() = default;

        static HighLighter *instance;

    public:
        // delete copy for single instance
        const HighLighter &operator=(const HighLighter &_) = delete;

        HighLighter(const HighLighter &_) = delete;

        static HighLighter *getInstance();

    private:
        std::vector<std::string> colors;

    public:
        void add(const std::string &color);

        void addOrNot(bool isEmpty, char curCh, char backCh);

        void pop();

        void popOrNot(bool isEmpty, char prev, char backCh);

        void clear();

        bool isEmpty();

        std::string getBack();
    };
}

#ifndef ZEARO_BASH_HIGHLIGHTER_INSTANCE
#define ZEARO_BASH_HIGHLIGHTER_INSTANCE
#define highLighter zbashHighLighter::HighLighter::getInstance()
#endif

#endif //ZEAROBASH_HIGHLIGHTER_H
