//
// Created by Grisha on 15.07.2021.
//

#ifndef BASE_CLASSES_SELECTIONSORT_H
#define BASE_CLASSES_SELECTIONSORT_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"

template<typename T>
mySequence<T>& SelectionSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2) = sortFuncPrivate::isLessDefault) {
    for (size_t i = 1; i < sequence.length(); i++) {
        size_t index_min = i-1;
        for (size_t j = i; j < sequence.length(); j++) {
            if (isLess(sequence[j], sequence[index_min])) {
                index_min = j;
            }
        }
        if (i-1 != index_min)
            sequence.swap(i-1, index_min);
    }
    return sequence;
}

#endif //BASE_CLASSES_SELECTIONSORT_H
