//
// Created by Grisha on 19.07.2021.
//

#ifndef BASE_CLASSES_BININSERTSORT_H
#define BASE_CLASSES_BININSERTSORT_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"

template<typename T>
mySequence<T>* BinInsertSort(const mySequence<T>& sequence, size_t start, size_t end, bool (*cmp)(const T& obj1, const T& obj2)) {
    if (end <= start || end - start < 2)
        return sequence.copy();

    mySequence<T>* resSequence = sequence.copy();

    if (cmp(resSequence->operator[](start+1), resSequence->operator[](start))) {
        resSequence->swap(start, start+1);
    }

    for (size_t i = start+2; i < end; i++) {
        size_t min = 0, max = i;
        size_t last = -1;
        while (min != max) {
            size_t index = (min + max) / 2;
            if (cmp(resSequence->operator[](i), resSequence->operator[](index)))
                max = index;
            else
                min = index;

            if (last == index)
                break;
            last = index;
        }

        for (size_t j = max; j < i; j++) {
            resSequence->swap(j, i);
        }
    }
    return resSequence;
}

template<typename T>
mySequence<T>* BinInsertSort(const mySequence<T>& sequence, size_t from, size_t to) {
    return BinInsertSort(sequence, from, to, sortFuncPrivate::isLessDefault);
}

template<typename T>
mySequence<T>* BinInsertSort(const mySequence<T>& sequence, bool (*cmp)(const T& obj1, const T& obj2)) {
    return BinInsertSort(sequence, 0, sequence.length(), cmp);
}

template<typename T>
mySequence<T>* BinInsertSort(const mySequence<T>& sequence) {
    return BinInsertSort(sequence, 0, sequence.length(), sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_BININSERTSORT_H
