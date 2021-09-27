//
// Created by Grisha on 27.09.2021.
//

#include "TestFuncs.h"

namespace Tests {
    int getLen(int max) {
        int len;
        do {
            len = rand()%max;
        } while (len == 0);
        return len;
    }

    int getIndex(int max){
        if (max == 0) return 0;
        return rand()%max;
    }

    void printText(const std::string& str, bool print) {
        if (!print)
            return;

        std::cout << str;
    }

    void printText(const std::string& str, const colors& clr, bool print) {
        if (!print)
            return;

        myConsole::changeTextColor(clr.R, clr.G, clr.B);
        std::cout << str;
        myConsole::applyDefaultColor();
    }
}