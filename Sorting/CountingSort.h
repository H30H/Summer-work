//
// Created by Grisha on 19.07.2021.
//

#ifndef BASE_CLASSES_COUNTINGSORT_H
#define BASE_CLASSES_COUNTINGSORT_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"
#include "../Map/myMap.h"

template<typename T>
mySequence<T>& CountingSort(mySequence<T>& sequence, size_t from, size_t to, bool (*isLess)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return sequence;
    }

    myMap<T, size_t> map(isLess, sortFuncPrivate::isTreeSameFunc);
    for (size_t i = from; i < to; i++) {
        if (map.find(sequence[i]) != map.end()) {
            map[sequence[i]] += 1;
        }
        else {
            map.insert(sequence[i], 1);
        }
    }
    size_t count = from;
    for (auto it = map.begin(); it != map.end(); ++it) {
        for (size_t i = 0; i < it->item; i++, count++) {
            sequence[count] = it->key;
        }
    }
    return sequence;
}

template<typename T>
mySequence<T>& CountingSort(mySequence<T>& sequence, size_t from, size_t to) {
    return CountingSort(sequence, from, to, sortFuncPrivate::isLessDefault);
}

template<typename T>
mySequence<T>& CountingSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2)) {
    return CountingSort(sequence, 0, sequence.length(), isLess);
}

template<typename T>
mySequence<T>& CountingSort(mySequence<T>& sequence) {
    return CountingSort(sequence, 0, sequence.length(), sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_COUNTINGSORT_H
