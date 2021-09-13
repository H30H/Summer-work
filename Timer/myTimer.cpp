//
// Created by Grisha on 10.09.2021.
//

#include "myTimer.h"

myTimer::myTimer(): _time(clock_t::now()) {}

myTimer::myTimer(const myTimer& timer) = default;

void myTimer::reset() {
    _time = clock_t::now();
}

double myTimer::time() {
    return std::chrono::duration_cast<second_t>(clock_t::now() - _time).count();
}