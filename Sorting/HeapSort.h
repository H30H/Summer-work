//
// Created by Grisha on 15.08.2021.
//

#ifndef BASE_CLASSES_HEAPSORT_H
#define BASE_CLASSES_HEAPSORT_H

#include "isLessDefault.h"
#include "../Sequence/myArraySequence.h"
#include "../BinaryTree/myBinaryHeap.h"

namespace sortFuncPrivate {
    template<typename T>
    void heapify(mySequence<T>& sequence, size_t heapSize, bool (*isLess)(const T& obj1, const T& obj2)) {
        size_t left, right, largest, index = 0;

        while(index < heapSize) {
            left  = index * 2 + 1;
            right = index * 2 + 2;
            largest = index;

            if (left < heapSize && isLess(sequence[largest], sequence[left]))
                largest = left;

            if (right < heapSize && isLess(sequence[largest], sequence[right]))
                largest = right;

            if (index == largest)
                break;

            sequence.swap(index, largest);
            index = largest;
        }
    }
}

template<typename T>
mySequence<T>& HeapSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2) = sortFuncPrivate::isLessDefault) {
    if (!isLess)
        isLess = sortFuncPrivate::isLessDefault;

    if (sequence.length() < 2)
        return sequence;

    myBinaryHeap<T> binaryHeap(isLess);
    for (size_t i = 0; i < sequence.length(); i++) {
        binaryHeap.insert(sequence[i]);
    }
    sequence = binaryHeap.getSequence();

    for (size_t i = sequence.length() - 1; i > 0; i--) {
        sequence.swap(0, i);
        sortFuncPrivate::heapify(sequence, i, isLess);
    }
    return sequence;
}

#endif //BASE_CLASSES_HEAPSORT_H
