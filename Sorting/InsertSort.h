//
// Created by Grisha on 15.07.2021.
//

#ifndef BASE_CLASSES_INSERTSORT_H
#define BASE_CLASSES_INSERTSORT_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"

template<typename T>
void InsertSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2)) {
    for (size_t i = 1; i < sequence.length(); i++) {
        for (size_t j = i; j > 0; j--) {
            if (isLess(sequence[j], sequence[j-1]))
                sequence.swap(j-1, j);
            else
                break;
        }
    }
}

template<typename T>
void InsertSort(mySequence<T>& sequence) {
    InsertSort(sequence, isLessDefault);
}


#endif //BASE_CLASSES_INSERTSORT_H
