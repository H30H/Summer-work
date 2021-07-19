//
// Created by Grisha on 19.07.2021.
//

#ifndef BASE_CLASSES_COUNTINGSORT_H
#define BASE_CLASSES_COUNTINGSORT_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"
#include <map>

template<typename T>
mySequence<T>& CountingSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2)) {
    std::map<T, size_t> myMap;
    for (size_t i = 0; i < sequence.length(); i++) {
        if (myMap.find(sequence[i]) != myMap.end()) {
            myMap[sequence[i]] += 1;
        }
        else {
            myMap[sequence[i]] = 1;
        }
    }
    size_t count = 0;
    for (auto it = myMap.begin(); it != myMap.end(); it++) {
        for (size_t i = 0; i < it->second; i++, count++) {
            sequence[count] = it->first;
        }
    }
    return sequence;
}

template<typename T>
mySequence<T>& CountingSort(mySequence<T>& sequence) {
    return CountingSort(sequence, isLessDefault);
}

#endif //BASE_CLASSES_COUNTINGSORT_H
