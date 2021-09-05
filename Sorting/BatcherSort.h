//
// Created by Grisha on 22.07.2021.
//

#ifndef BASE_CLASSES_BATCHERSORT_H
#define BASE_CLASSES_BATCHERSORT_H

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
                             bool (*isLess)(const T& obj1, const T& obj2)) {
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
                            bool (*isLess)(const T& obj1, const T& obj2)) {
        if (to <= from || to - from < 2) {
            return;
        }

        for (size_t i = from, j = to - 1; i < j; i++, j--) {
            if (isLess(sequence[j], sequence[i]))
                sequence.swap(i, j);
        }
    }

    template<typename T>
    void mergeSequence(mySequence<T>& sequence, size_t from, size_t to, size_t index,
                       bool (*isLess)(const T& obj1, const T& obj2)) {
        size_t ind1 = from, ind2 = index;
        while(ind1 != index && ind2 != to) {
            if (isLess(sequence[ind2], sequence[ind1])) {
                sequence.insert(sequence[ind2], ind1);
                sequence.pop(ind2+1);
                ind1++;
                ind2++;
                index++;
            }
            else {
                ind1++;
            }
        }
    }
}

template<typename T>
mySequence<T>& BatcherSort(mySequence<T>& sequence, size_t from, size_t to, bool (*isLess)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return sequence;
    }

    size_t size = to - from;

    if (!sortFuncPrivate::checkLog2(size)) { //если размер отрезка не равен степени двойки
        myArraySequence<size_t> indexes(from);
        while (size != 0) {                  //сортировка вложенных отрезков, длиной степени двойки
            auto index = (size_t) pow(2, (size_t) log2(size));
            size -= index;
            index += indexes.getLast();
            BatcherSort(sequence, indexes.getLast(), index, isLess);
            indexes.append(index);
        }

        for (size_t i = indexes.length() - 1, j = 1; i >= 2; i--, j++) { //сортировка отсортированных отрезков
            sortFuncPrivate::mergeSequence(sequence, indexes[i-2], indexes.getLast(), indexes[i-1], isLess);
        }
        return sequence;
    }

    for (size_t i = 2; i <= size; i*=2) { //сортировка отрезков, длина которых равна степени двойки
        for (size_t j = from; j + i <= to; j += i) {
            sortFuncPrivate::getBitonicSequence(sequence, j, j+i, isLess);             //преобразование отрезка к битонической последовательности
            sortFuncPrivate::sortBitonicSequence(sequence, j, j + i/2, isLess);        //сортировка левой части
            sortFuncPrivate::sortBitonicSequence(sequence, j + i/2, j+i, isLess);      //сортировка правой части
        }
    }

    return sequence;
}

template<typename T>
mySequence<T>& BatcherSort(mySequence<T>& sequence, size_t start, size_t end) {
    return BatcherSort(sequence, start, end, sortFuncPrivate::isLessDefault);
}

template<typename T>
mySequence<T>& BatcherSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2)) {
    return BatcherSort(sequence, 0, sequence.length(), isLess);
}

template<typename T>
mySequence<T>& BatcherSort(mySequence<T>& sequence) {
    return BatcherSort(sequence, sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_BATCHERSORT_H
