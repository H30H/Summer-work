//
// Created by Grisha on 15.07.2021.
//

#ifndef BASE_CLASSES_INSERTSORT_H
#define BASE_CLASSES_INSERTSORT_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"

template<typename T>
mySequence<T>& InsertSort(mySequence<T>& sequence, size_t from, size_t to, bool (*isLess)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return sequence;
    }

    size_t index;

    for (size_t i = from + 1; i < to; i++) {
        index = i;
        for (size_t j = i; j > from; j--) {
            if (isLess(sequence[i], sequence[j-1]))
                --index;
            else
                break;
        }

        if (i != index)
            sequence.move(i, index);
    }
    return sequence;
}

template<typename T>
mySequence<T>& InsertSort(mySequence<T>& sequence, size_t from, size_t to) {
    return InsertSort(sequence, from, to, sortFuncPrivate::isLessDefault);
}

template<typename T>
mySequence<T>& InsertSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2)) {
    return InsertSort(sequence, 0, sequence.length(), isLess);
}

template<typename T>
mySequence<T>& InsertSort(mySequence<T>& sequence) {
    return InsertSort(sequence, 0, sequence.length(), sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_INSERTSORT_H
