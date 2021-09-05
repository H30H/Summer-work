//
// Created by Grisha on 19.07.2021.
//

#ifndef BASE_CLASSES_MERGESORT_H
#define BASE_CLASSES_MERGESORT_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"
#include "iostream"

template<typename T>
mySequence<T>& MergeSort(mySequence<T>& sequence, size_t from, size_t to, bool (*isLess)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return sequence;
    }

    size_t index = (from + to) / 2;
    MergeSort(sequence, from, index, isLess);
    MergeSort(sequence, index, to, isLess);

    size_t ind1 = from, ind2 = index;
    while(ind1 != index && ind2 != to) {
        if (isLess(sequence[ind2], sequence[ind1])) {
            sequence.insert(sequence[ind2], ind1);
            sequence.pop(ind2+1);
            ind1++;
            ind2++;
            index++;
        }
        else {
            ind1++;
        }
    }
    return sequence;
}

template<typename T>
mySequence<T>& MergeSort(mySequence<T>& sequence, size_t from, size_t to) {
    return MergeSort(sequence, from, to, sortFuncPrivate::isLessDefault);
}


template<typename T>
mySequence<T>& MergeSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2)) {
    return MergeSort(sequence, 0, sequence.length(), isLess);
}

template<typename T>
mySequence<T>& MergeSort(mySequence<T>& sequence) {
    return MergeSort(sequence, sortFuncPrivate::isLessDefault);
}


#endif //BASE_CLASSES_MERGESORT_H
