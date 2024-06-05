//
// Created by Lenovo on 2024/6/5.
//

#include "highlighter.h"

namespace zbashHighLighter {
    HighLighter *HighLighter::instance = nullptr;

    HighLighter *HighLighter::getInstance() {
        if (instance == nullptr) {
            instance = new HighLighter();
        }
        return instance;
    }
}

void zbashHighLighter::HighLighter::add(const std::string &color) {
    if (color == "yellow") {
        colors.emplace_back("\033[0m\033[1;33m");
    } else if (color == "red") {
        colors.emplace_back("\033[0m\033[1;31m");
    } else if (color == "green") {
        colors.emplace_back("\033[0m\033[1;32m");
    }
}

void zbashHighLighter::HighLighter::addOrNot(bool isEmpty, char curCh, char backCh) {
    if (curCh == '-') {
        if (isEmpty || backCh == ' ') this->add("green");
    } else if (curCh == ' ') {
        if (!isEmpty && backCh != ' ') {
            this->add("red");
        }
    } else {
        if (colors.empty()) this->add("yellow");
        else if (!isEmpty && backCh == ' ') this->add("red");
    }
}

void zbashHighLighter::HighLighter::pop() {
    if (!colors.empty()) colors.pop_back();
}

void zbashHighLighter::HighLighter::popOrNot(bool isEmpty, char prev, char backCh) {
    if (isEmpty) {
        colors.pop_back();
    } else if (backCh == ' ') {
        if (prev != ' ') {
            colors.pop_back();
        }
    } else {
        if (prev == ' ') {
            colors.pop_back();
        }
    }
}

void zbashHighLighter::HighLighter::clear() {
    colors.clear();
}

std::string zbashHighLighter::HighLighter::getBack() {
    if (!colors.empty()) return colors.back();
    return "";
}

bool zbashHighLighter::HighLighter::isEmpty() {
    return colors.empty();
}