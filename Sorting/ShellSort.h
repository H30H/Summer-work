//
// Created by Grisha on 21.08.2021.
//

#ifndef BASE_CLASSES_SHELLSORT_H
#define BASE_CLASSES_SHELLSORT_H

#include "isLessDefault.h"
#include "../Sequence/myArraySequence.h"

namespace sortFuncPrivate {
    template<typename T>
    mySequence<T>& InsertSort(mySequence<T>& sequence, size_t interval, size_t from, size_t to, bool (*isLess)(const T& obj1, const T& obj2)) {
        for (size_t j = 0; j < interval; j++) {
            for (size_t i2 = j + interval; i2 < to; i2 += interval) {
                for (size_t i1 = i2 - interval; i1 >= from; i1 -= interval) {
                    if (isLess(sequence[i1 + interval], sequence[i1]))
                        sequence.swap(i1, i1 + interval);
                    else
                        break;

                    if (i1 < interval)
                        break;
                }
            }
        }
        return sequence;
    }
}

template<typename T>
mySequence<T>& ShellSort(mySequence<T>& sequence, mySequence<size_t>& intervals, size_t from, size_t to, bool (*isLess)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return sequence;
    }

    for (size_t i = 0; i < intervals.length(); i++) {
        sortFuncPrivate::InsertSort(sequence, intervals[i], from, to, isLess);
    }

    return sequence;
}

template<typename T>
mySequence<T>& ShellSort(mySequence<T>& sequence, mySequence<size_t>& intervals, size_t from, size_t to) {
    return ShellSort(sequence, intervals, from, to, sortFuncPrivate::isLessDefault);
}

template<typename T>
mySequence<T>& ShellSort(mySequence<T>& sequence, mySequence<size_t>& intervals, bool (*isLess)(const T& obj1, const T& obj2)) {
    return ShellSort(sequence, intervals, 0, sequence.length(), isLess);
}

template<typename T>
mySequence<T>& ShellSort(mySequence<T>& sequence, mySequence<size_t>& intervals) {
    return ShellSort(sequence, intervals, 0, sequence.length(), sortFuncPrivate::isLessDefault);
}

template<typename T>
mySequence<T>& ShellSort(mySequence<T>& sequence, size_t from, size_t to, bool (*isLess)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return sequence;
    }

    myArraySequence<size_t> intervals; //формирование последовательности Седжвика для сортировки Шелла
    size_t last = 1;
    size_t predLast = 1;

    size_t powI0 = 1;  //2^i
    size_t powI1 = 1;  //2^((i+1)/2)  для нечётных i
    size_t powI2 = 1;  //2^(i/2)      для чётных i

    for (size_t i = 1; last < sequence.length(); i++) {
        if (i % 2 == 0) {
            powI0 *= 2;
            powI2 *= 2;

            predLast = last;
            last = 9*(powI0 - powI2) + 1;
        }
        else {
            powI0 *= 2;
            powI1 *= 2;

            predLast = last;
            last = 8*powI0 - 6*powI1 + 1;
        }
        intervals.prepend(predLast);
    }

    return ShellSort(sequence, intervals, from, to, isLess);
}

template<typename T>
mySequence<T>& ShellSort(mySequence<T>& sequence, size_t from, size_t to) {
    return ShellSort(sequence, from, to, sortFuncPrivate::isLessDefault);
}

template<typename T>
mySequence<T>& ShellSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2)) {
    return ShellSort(sequence, 0, sequence.length(), isLess);
}

template<typename T>
mySequence<T>& ShellSort(mySequence<T>& sequence) {
    return ShellSort(sequence, 0, sequence.length(), sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_SHELLSORT_H
