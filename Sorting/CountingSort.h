//
// Created by Grisha on 19.07.2021.
//

#ifndef BASE_CLASSES_COUNTINGSORT_H
#define BASE_CLASSES_COUNTINGSORT_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"
#include "../Map/myMap.h"

template<typename T>
mySequence<T>* CountingSort(const mySequence<T>& sequence, size_t from, size_t to, bool (*cmp)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return sequence.copy();
    }

    myMap<T, size_t> map(cmp, sortFuncPrivate::isTreeSameFunc);
    for (size_t i = from; i < to; i++) {
        if (map.find(sequence[i]) != map.end()) {
            map[sequence[i]] += 1;
        }
        else {
            map.insert(sequence[i], 1);
        }
    }

    mySequence<T>* resSequence = sequence.copy();

    size_t count = from;
    for (auto it = map.begin(); it != map.end(); ++it) {
        for (size_t i = 0; i < it->item; i++, count++) {
            resSequence->operator[](count) = it->key;
        }
    }
    return resSequence;
}

template<typename T>
mySequence<T>* CountingSort(const mySequence<T>& sequence, size_t from, size_t to) {
    return CountingSort(sequence, from, to, sortFuncPrivate::isLessDefault);
}

template<typename T>
mySequence<T>* CountingSort(const mySequence<T>& sequence, bool (*cmp)(const T& obj1, const T& obj2)) {
    return CountingSort(sequence, 0, sequence.length(), cmp);
}

template<typename T>
mySequence<T>* CountingSort(const mySequence<T>& sequence) {
    return CountingSort(sequence, 0, sequence.length(), sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_COUNTINGSORT_H
