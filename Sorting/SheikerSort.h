//
// Created by Grisha on 13.07.2021.
//

#ifndef BASE_CLASSES_SHEIKERSORT_H
#define BASE_CLASSES_SHEIKERSORT_H

#include "../Sequence/mySequence.h"
#include "isLessDefault.h"

template<typename T>
mySequence<T>& SheikerSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2) = sortFuncPrivate::isLessDefault) {
    bool isChanged = true;
    size_t min = 0, max = sequence.length() - 1;
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

#endif //BASE_CLASSES_SHEIKERSORT_H
