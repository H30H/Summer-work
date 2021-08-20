//
// Created by Grisha on 19.07.2021.
//

#ifndef BASE_CLASSES_BININSERTSORT_H
#define BASE_CLASSES_BININSERTSORT_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"

template<typename T>
mySequence<T>& BinInsertSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2)) {
    if (sequence.length() < 2)
        return sequence;

    if (isLess(sequence[1], sequence[0])) {
        sequence.swap(0, 1);
    }

    for (size_t i = 2; i < sequence.length(); i++) {
        size_t min = 0, max = i;
        size_t last = -1;
        while (min != max) {
            size_t index = (min + max) / 2;
            if (isLess(sequence[i], sequence[index]))
                max = index;
            else
                min = index;

            if (last == index)
                break;
            last = index;
        }

        for (size_t j = max; j < i; j++) {
            sequence.swap(j, i);
        }
    }
    return sequence;
}

template<typename T>
mySequence<T>& BinInsertSort(mySequence<T>& sequence) {
    return BinInsertSort(sequence, sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_BININSERTSORT_H
