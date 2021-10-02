//
// Created by Grisha on 21.09.2021.
//

#ifndef BASE_CLASSES_MYCONSOLE_H
#define BASE_CLASSES_MYCONSOLE_H

#include <iostream>

// All these commands were taken from the ANSI-Escape table

struct myConsole {
    template<typename T, typename...Args>
    static void print(const T& item, Args...args) {
        std::cout << item;
        print(args...);
    }

    static void print() {}

    static void changeTextColor(int R, int G, int B) {
        std::string res("\x1B[");
        res += "38;2;";     //change text color mode
        res += std::to_string(R%256) + ';';
        res += std::to_string(G%256) + ';';
        res += std::to_string(B%256) + 'm';
        std::cout << res;
    }

    static void changeBackgroundColor(char R, char G, char B) {
        std::string res("\x1B[");
        res += "48;2;";     // change background color mode
        res += std::to_string((int) R) + ';';
        res += std::to_string((int) G) + ';';
        res += std::to_string((int) B) + 'm';
        std::cout << res;
    }

    static void applyDefaultColor() {
        std::cout << "\x1B[0m";
    }

    static void moveCursorUp(size_t count = 1) {
        if (count == 0)
            return;
        std::cout << std::string("\x1B[") + std::to_string(count) + "A";
    }

    static void moveCursorDown(size_t count = 1) {
        if (count == 0)
            return;
        std::cout << std::string("\x1B[") + std::to_string(count) + "B";
    }

    static void moveCursorLeft(size_t count = 1) {
        if (count == 0)
            return;
        std::cout << std::string("\x1B[") + std::to_string(count) + "D";
    }

    static void moveCursorRight(size_t count = 1) {
        if (count == 0)
            return;
        std::cout << std::string("\x1B[") + std::to_string(count) + "C";
    }

    static void removeLine(char num = 2) {  //0 - from cursor to end, 1 - from cursor to start, 2 - all line
        if (num > 2)
            num = 2;

        std::cout << std::string("\x1B[") + std::to_string((int) num) + "K";
    }
};

#endif //BASE_CLASSES_MYCONSOLE_H
