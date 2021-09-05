//
// Created by Grisha on 13.07.2021.
//

#ifndef BASE_CLASSES_SHEIKERSORT_H
#define BASE_CLASSES_SHEIKERSORT_H

#include "../Sequence/mySequence.h"
#include "isLessDefault.h"

template<typename T>
mySequence<T>& SheikerSort(mySequence<T>& sequence, size_t from, size_t to, bool (*isLess)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return sequence;
    }

    bool isChanged = true;
    size_t min = from, max = to - 1;
    while (isChanged) {
        isChanged = false;
        for (size_t i = min + 1; i <= max; i++) {
            if (isLess(sequence[i], sequence[i-1])) {
                isChanged = true;
                sequence.swap(i-1, i);
            }
        }
        if (!isChanged)
            break;
        max--;
        isChanged = false;
        for (size_t i = max; i >= min + 1; i--) {
            if (isLess(sequence[i], sequence[i-1])) {
                isChanged = true;
                sequence.swap(i-1, i);
            }
        }
    }
    return sequence;
}

template<typename T>
mySequence<T>& SheikerSort(mySequence<T>& sequence, size_t from, size_t to) {
    return SheikerSort(sequence, from, to, sortFuncPrivate::isLessDefault);
}

template<typename T>
mySequence<T>& SheikerSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2)) {
    return SheikerSort(sequence, 0, sequence.length(), isLess);
}

template<typename T>
mySequence<T>& SheikerSort(mySequence<T>& sequence) {
    return SheikerSort(sequence, 0, sequence.length(), sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_SHEIKERSORT_H
