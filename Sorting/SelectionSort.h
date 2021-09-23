//
// Created by Grisha on 15.07.2021.
//

#ifndef BASE_CLASSES_SELECTIONSORT_H
#define BASE_CLASSES_SELECTIONSORT_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"

template<typename T>
mySequence<T>* SelectionSort(const mySequence<T>& sequence, size_t from, size_t to, bool (*cmp)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return sequence.copy();
    }

    mySequence<T>* resSequence = sequence.copy();

    for (size_t i = from+1; i < to; i++) {
        size_t index_min = i-1;
        for (size_t j = i; j < to; j++) {
            if (cmp(resSequence->operator[](j), resSequence->operator[](index_min))) {
                index_min = j;
            }
        }
        if (i-1 != index_min)
            resSequence->swap(i-1, index_min);
    }

    return resSequence;
}

template<typename T>
mySequence<T>* SelectionSort(const mySequence<T>& sequence, size_t from, size_t to) {
    return SelectionSort(sequence, from, to, sortFuncPrivate::isLessDefault);
}

template<typename T>
mySequence<T>* SelectionSort(const mySequence<T>& sequence, bool (*cmp)(const T& obj1, const T& obj2)) {
    return SelectionSort(sequence, 0, sequence.length(), cmp);
}

template<typename T>
mySequence<T>* SelectionSort(const mySequence<T>& sequence) {
    return SelectionSort(sequence, 0, sequence.length(), sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_SELECTIONSORT_H
