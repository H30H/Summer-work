//
// Created by Grisha on 27.09.2021.
//

#ifndef BASE_CLASSES_TESTFUNCS_H
#define BASE_CLASSES_TESTFUNCS_H

#include "random"
#include "../Console/myConsole.h"

namespace Tests {
    struct colors {
        int R, G, B;
    };

    struct testFault: public std::exception {
        int done;
        int fault;
        std::string str;
        testFault(): testFault(0, 0) {}

        testFault(int done, int fault): done(done), fault(fault) {
            str = "Done: ";
            str += std::to_string(done);
            str += "; Fault: ";
            str += std::to_string(fault);
        }

        const char* what() const noexcept override {
            return str.c_str();
        }
    };

    int getLen(int max);

    int getIndex(int max);

    void printText(const std::string& str, bool print = true);

    void printText(const std::string& str, const colors& clr, bool print = true);
}

#endif //BASE_CLASSES_TESTFUNCS_H
