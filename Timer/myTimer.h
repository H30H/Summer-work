//
// Created by Grisha on 10.09.2021.
//

#ifndef BASE_CLASSES_MYTIMER_H
#define BASE_CLASSES_MYTIMER_H

#include <chrono>

class myTimer {
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<clock_t> _time;
public:
    myTimer();

    myTimer(const myTimer& timer);

    void reset();

    double time();
};


#endif //BASE_CLASSES_MYTIMER_H
