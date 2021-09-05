//
// Created by Grisha on 15.07.2021.
//

#ifndef BASE_CLASSES_SELECTIONSORT_H
#define BASE_CLASSES_SELECTIONSORT_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"

template<typename T>
mySequence<T>& SelectionSort(mySequence<T>& sequence, size_t from, size_t to, bool (*isLess)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return sequence;
    }

    for (size_t i = from+1; i < to; i++) {
        size_t index_min = i-1;
        for (size_t j = i; j < to; j++) {
            if (isLess(sequence[j], sequence[index_min])) {
                index_min = j;
            }
        }
        if (i-1 != index_min)
            sequence.swap(i-1, index_min);
    }
    return sequence;
}

template<typename T>
mySequence<T>& SelectionSort(mySequence<T>& sequence, size_t from, size_t to) {
    return SelectionSort(sequence, from, to, sortFuncPrivate::isLessDefault);
}

template<typename T>
mySequence<T>& SelectionSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2)) {
    return SelectionSort(sequence, 0, sequence.length(), isLess);
}

template<typename T>
mySequence<T>& SelectionSort(mySequence<T>& sequence) {
    return SelectionSort(sequence, 0, sequence.length(), sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_SELECTIONSORT_H
