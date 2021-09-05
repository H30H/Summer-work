//
// Created by Grisha on 13.07.2021.
//

#ifndef BASE_CLASSES_BUBBLESORT_H
#define BASE_CLASSES_BUBBLESORT_H

#include "../Sequence/mySequence.h"
#include "isLessDefault.h"

template<typename T>
mySequence<T>& BubbleSort(mySequence<T>& sequence, size_t from, size_t to, bool (*isLess)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return sequence;
    }

    bool isChanged = true;
    size_t count = to - from;
    while(isChanged) {
        isChanged = false;
        for (size_t i = from+1; i < count; i++) {
            if (isLess(sequence[i], sequence[i-1])) {
                isChanged = true;
                sequence.swap(i-1, i);
            }
        }
        count--;
    }
    return sequence;
}

template<typename T>
mySequence<T>& BubbleSort(mySequence<T>& sequence, size_t from, size_t to) {
    return BubbleSort(sequence, from, to, sortFuncPrivate::isLessDefault);
}

template<typename T>
mySequence<T>& BubbleSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2)) {
    return BubbleSort(sequence, 0, sequence.length(), isLess);
}

template<typename T>
mySequence<T>& BubbleSort(mySequence<T>& sequence) {
    return BubbleSort(sequence, 0, sequence.length(), sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_BUBBLESORT_H
