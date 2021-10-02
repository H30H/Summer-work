//
// Created by Grisha on 13.07.2021.
//

#ifndef BASE_CLASSES_SHAKERSORT_H
#define BASE_CLASSES_SHAKERSORT_H

#include "../Sequence/mySequence.h"
#include "isLessDefault.h"

template<typename T>
mySequence<T>* ShakerSort(const mySequence<T>& sequence, size_t from, size_t to, bool (*cmp)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return sequence.copy();
    }

    mySequence<T>* resSequence = sequence.copy();

    bool isChanged = true;
    size_t min = from, max = to - 1;
    while (isChanged) {
        isChanged = false;
        for (size_t i = min + 1; i <= max; i++) {
            if (cmp(resSequence->operator[](i), resSequence->operator[](i-1))) {
                isChanged = true;
                resSequence->swap(i-1, i);
            }
        }
        if (!isChanged)
            break;
        max--;
        isChanged = false;
        for (size_t i = max; i >= min + 1; i--) {
            if (cmp(resSequence->operator[](i), resSequence->operator[](i-1))) {
                isChanged = true;
                resSequence->swap(i-1, i);
            }
        }
    }
    return resSequence;
}

template<typename T>
mySequence<T>* ShakerSort(const mySequence<T>& sequence, size_t from, size_t to) {
    return ShakerSort(sequence, from, to, sortFuncPrivate::isLessDefault);
}

template<typename T>
mySequence<T>* ShakerSort(const mySequence<T>& sequence, bool (*cmp)(const T& obj1, const T& obj2)) {
    return ShakerSort(sequence, 0, sequence.length(), cmp);
}

template<typename T>
mySequence<T>* ShakerSort(const mySequence<T>& sequence) {
    return ShakerSort(sequence, 0, sequence.length(), sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_SHAKERSORT_H
