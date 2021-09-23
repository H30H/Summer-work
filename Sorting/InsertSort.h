//
// Created by Grisha on 15.07.2021.
//

#ifndef BASE_CLASSES_INSERTSORT_H
#define BASE_CLASSES_INSERTSORT_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"

template<typename T>
mySequence<T>* InsertSort(const mySequence<T>& sequence, size_t from, size_t to, bool (*cmp)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return sequence.copy();
    }

    size_t index;

    mySequence<T>* resSequence = sequence.copy();

    for (size_t i = from + 1; i < to; i++) {
        index = i;
        for (size_t j = i; j > from; j--) {
            if (cmp(resSequence->operator[](i), resSequence->operator[](j-1)))
                --index;
            else
                break;
        }

        if (i != index)
            resSequence->move(i, index);
    }
    return resSequence;
}

template<typename T>
mySequence<T>* InsertSort(const mySequence<T>& sequence, size_t from, size_t to) {
    return InsertSort(sequence, from, to, sortFuncPrivate::isLessDefault);
}

template<typename T>
mySequence<T>* InsertSort(const mySequence<T>& sequence, bool (*cmp)(const T& obj1, const T& obj2)) {
    return InsertSort(sequence, 0, sequence.length(), cmp);
}

template<typename T>
mySequence<T>* InsertSort(const mySequence<T>& sequence) {
    return InsertSort(sequence, 0, sequence.length(), sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_INSERTSORT_H
