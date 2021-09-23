//
// Created by Grisha on 19.07.2021.
//

#ifndef BASE_CLASSES_MERGESORT_H
#define BASE_CLASSES_MERGESORT_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"
#include "iostream"

namespace sortFuncPrivate {
    template<typename T>
    void MergeSort(mySequence<T>& sequence, size_t from, size_t to, bool (*cmp)(const T& obj1, const T& obj2)) {
        if (to <= from || to - from < 2) {
            return;
        }

        size_t index = (from + to) / 2;
        MergeSort(sequence, from, index, cmp);
        MergeSort(sequence, index, to, cmp);

        size_t ind1 = from, ind2 = index;
        while(ind1 != index && ind2 != to) {
            if (cmp(sequence[ind2], sequence[ind1])) {
                sequence.move(ind2, ind1);
                ind1++;
                ind2++;
                index++;
            }
            else {
                ind1++;
            }
        }
    }
}

template<typename T>
mySequence<T>* MergeSort(const mySequence<T>& sequence, size_t from, size_t to, bool (*cmp)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return sequence.copy();
    }

    mySequence<T>* resSequence = sequence.copy();

    size_t index = (from + to) / 2;
    sortFuncPrivate::MergeSort(*resSequence, from, index, cmp);
    sortFuncPrivate::MergeSort(*resSequence, index, to, cmp);

    size_t ind1 = from, ind2 = index;
    while(ind1 != index && ind2 != to) {
        if (cmp(resSequence->operator[](ind2), resSequence->operator[](ind1))) {
            resSequence->move(ind2, ind1);
            ind1++;
            ind2++;
            index++;
        }
        else {
            ind1++;
        }
    }
    return resSequence;
}

template<typename T>
mySequence<T>* MergeSort(const mySequence<T>& sequence, size_t from, size_t to) {
    return MergeSort(sequence, from, to, sortFuncPrivate::isLessDefault);
}


template<typename T>
mySequence<T>* MergeSort(const mySequence<T>& sequence, bool (*cmp)(const T& obj1, const T& obj2)) {
    return MergeSort(sequence, 0, sequence.length(), cmp);
}

template<typename T>
mySequence<T>* MergeSort(const mySequence<T>& sequence) {
    return MergeSort(sequence, sortFuncPrivate::isLessDefault);
}


#endif //BASE_CLASSES_MERGESORT_H
