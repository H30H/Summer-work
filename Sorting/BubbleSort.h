//
// Created by Grisha on 13.07.2021.
//

#ifndef BASE_CLASSES_BUBBLESORT_H
#define BASE_CLASSES_BUBBLESORT_H

#include "../Sequence/mySequence.h"
#include "isLessDefault.h"

template<typename T>
mySequence<T>* BubbleSort(const mySequence<T>& sequence, size_t from, size_t to, bool (*cmp)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return sequence.copy();
    }
    bool isChanged = true;

    mySequence<T>* resSequence = sequence.copy();

    while(isChanged) {
        isChanged = false;
        for (size_t i = from+1; i < to; i++) {
            if (cmp(resSequence->operator[](i), resSequence->operator[](i-1))) {
                isChanged = true;
                resSequence->swap(i - 1, i);
            }
        }
        to--;
    }

    return resSequence;
}

template<typename T>
mySequence<T>* BubbleSort(const mySequence<T>& sequence, size_t from, size_t to) {
    return BubbleSort(sequence, from, to, sortFuncPrivate::isLessDefault);
}

template<typename T>
mySequence<T>* BubbleSort(const mySequence<T>& sequence, bool (*cmp)(const T& obj1, const T& obj2)) {
    return BubbleSort(sequence, 0, sequence.length(), cmp);
}

template<typename T>
mySequence<T>* BubbleSort(const mySequence<T>& sequence) {
    return BubbleSort(sequence, 0, sequence.length(), sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_BUBBLESORT_H
