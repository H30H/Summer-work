//
// Created by Grisha on 15.07.2021.
//

#ifndef BASE_CLASSES_SELECTIONSORTMOD_H
#define BASE_CLASSES_SELECTIONSORTMOD_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"

template<typename T>
mySequence<T>& SelectionSortMod(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2)) {
    for (size_t i = 1, end = sequence.length() - 1; i <= end; i++, end--) {
        size_t min = i-1;
        size_t max = i;
        if (isLess(sequence[max], sequence[min])) {
            max = min;
            min = i;
        }
        for (size_t j = i + 1; j <= end; j++) {
            if (isLess(sequence[j], sequence[min])) {
                min = j;
            }

            if (isLess(sequence[max], sequence[j])) {
                max = j;
            }
        }

        if (min == end && max == i-1) { //когда минимальный находится в конце, а максимальный в начале (чтоб 2 раза не менять их местами)
            sequence.swap(min, max);
        }
        else if (min != end && max == i-1) { //когда максимальный находится в начале, а минимальный где-то в массиве (чтоб не потерять максимальный)
            sequence.swap(end, max);
            sequence.swap(min, i-1);
        }
        else {                          //дефолтный случай
            sequence.swap(min, i-1);
            sequence.swap(max, end);
        }
    }
    return sequence;
}

template<typename T>
mySequence<T>& SelectionSortMod(mySequence<T>& sequence) {
    return SelectionSortMod(sequence, isLessDefault);
}

#endif //BASE_CLASSES_SELECTIONSORTMOD_H
