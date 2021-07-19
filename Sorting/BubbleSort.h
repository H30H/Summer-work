//
// Created by Grisha on 13.07.2021.
//

#ifndef BASE_CLASSES_BUBBLESORT_H
#define BASE_CLASSES_BUBBLESORT_H

#include "../Sequence/mySequence.h"
#include "isLessDefault.h"

template<typename T>
mySequence<T>& BubbleSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2)) {
    bool isChanged = true;
    int count = sequence.length();
    while(isChanged) {
        isChanged = false;
        for (size_t i = 1; i < count; i++) {
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
mySequence<T>& BubbleSort(mySequence<T>& sequence) {
    return BubbleSort(sequence, isLessDefault);
}

#endif //BASE_CLASSES_BUBBLESORT_H
