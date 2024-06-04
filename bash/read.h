//
// Created by 86158 on 2024/6/2.
//

#ifndef ZEARO_BASH_READ_H
#define ZEARO_BASH_READ_H

#include <cstdio>
#include <unistd.h>
#include <termios.h>
#include <cstdlib>
#include <cstring>

#include <string>


namespace zearo_bash_shell {
    using std::string;

    class myInput {
    private:
        // private constructor
        myInput() = default;

        ~myInput() = default;

        static myInput* instance;

    public:
        // delete copy for single instance
        const myInput &operator=(const myInput& _) = delete;
        myInput(const myInput& _) = delete;

    public:
        /**
         * @brief get the only instance of this class.
         * @return
         */
        static myInput* getInstance();

        char* inputOneLine();

        /**
         * @brief When we press backspace key, it will call this function.
         * @param line string_dealing&
         */
        static void inputBackSpace(string & line);

        /**
         * @brief When we press enter key, it will call this function.
         * @param line
         * @return char*.
         */
        char* inputEnter(string & line);


    private:
        struct termios old_t{}, new_t{};

    private:
        /**
         * @brief Get the position of cursor.
         * @param row
         * @param col
         */
        static void getCursorPosition(int * row, int * col);

        [[maybe_unused]] static int getCursorColOnly();

        void initTerminalInputWay();

        void recoverTerminalInputWay();
    };



}



#ifndef ZEARO_BASH_GET_LINE
#define ZEARO_BASH_GET_LINE
#define zbash_read_line() zearo_bash_shell::myInput::getInstance()->inputOneLine()
#endif

#ifndef ZEARO_BASH_GET_LINE
char *zbash_read_line();
#endif


#endif //ZEARO_BASH_READ_H
