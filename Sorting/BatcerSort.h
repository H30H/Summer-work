//
// Created by Grisha on 22.07.2021.
//

#ifndef BASE_CLASSES_BATCERSORT_H
#define BASE_CLASSES_BATCERSORT_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"
#include "../Sequence/myArraySequence.h"
#include <cmath>
#include <iostream>

namespace sortFuncPrivate {
    bool checkLog2(size_t num) {
        auto res = log2((double) num);
        return fmod(res, 1) == 0;
    }

    template<typename T>
    void sortBitonicSequence(mySequence<T>& sequence, size_t from, size_t to,
                             bool (*isLess)(const T& obj1, const T& obj2) = sortFuncPrivate::isLessDefault) {
        if (to <= from || to - from < 2) {
            return;
        }

        size_t index = from + (to - from) / 2;

        for (size_t i = from, j = index; j < to; i++, j++) {
            if (isLess(sequence[j], sequence[i])) {
                sequence.swap(i, j);
            }
        }
        sortBitonicSequence(sequence, from, index, isLess);
        sortBitonicSequence(sequence, index, to, isLess);
    }

    template<typename T>
    void getBitonicSequence(mySequence<T>& sequence, size_t from, size_t to,
                            bool (*isLess)(const T& obj1, const T& obj2) = sortFuncPrivate::isLessDefault) {
        if (to <= from || to - from < 2) {
            return;
        }

        for (size_t i = from, j = to - 1; i < j; i++, j--) {
            if (isLess(sequence[j], sequence[i]))
                sequence.swap(i, j);
        }
    }
}

template<typename T>
mySequence<T>& BatcherSort(mySequence<T>& sequence, size_t from, size_t to, bool (*isLess)(const T& obj1, const T& obj2) = sortFuncPrivate::isLessDefault) {
    if (to <= from || to - from < 2) {
        return sequence;
    }

    size_t size = to - from;
    for (size_t i = 2; i <= size; i*=2) {
        for (size_t j = from; j + i <= to; j += i) {
            sortFuncPrivate::getBitonicSequence(sequence, j, j+i, isLess);             //преобразование отрезка к битонической последовательности
            sortFuncPrivate::sortBitonicSequence(sequence, j, j + i/2, isLess);        //сортировка левой части
            sortFuncPrivate::sortBitonicSequence(sequence, j + i/2, j+i, isLess);      //сортировка правой части
        }
    }
//    std::cout << sequence << std::endl;
    if (!sortFuncPrivate::checkLog2(to - from)) { //когда количество элементов не равно степени двойки
        //TODO приоритет: хуй знвет почему не работает (потом доделаю)
        sortFuncPrivate::getBitonicSequence(sequence, from, to, isLess);               //преобразование отрезка к битонической последовательности
//        std::cout << '-' << sequence << std::endl;
        sortFuncPrivate::sortBitonicSequence(sequence, from, from + size/2, isLess);   //сортировка левой части
//        std::cout << '-' << sequence << std::endl;
        sortFuncPrivate::sortBitonicSequence(sequence, from + size/2, to, isLess);     //сортировка правой части
//        std::cout << '-' << sequence << std::endl;
    }

    return sequence;
}

template<typename T>
mySequence<T>& BatcherSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2) = sortFuncPrivate::isLessDefault) {
    if (sequence.length() < 2)
        return sequence;

    return BatcherSort(sequence, 0, sequence.length(), isLess);
}

#endif //BASE_CLASSES_BATCERSORT_H
