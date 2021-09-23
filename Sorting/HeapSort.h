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
    void heapify(mySequence<T>& sequence, size_t heapSize, bool (*cmp)(const T& obj1, const T& obj2)) {
        size_t left, right, largest, index = 0;

        while(index < heapSize) {
            left  = index * 2 + 1;
            right = index * 2 + 2;
            largest = index;

            if (left < heapSize && cmp(sequence[largest], sequence[left]))
                largest = left;

            if (right < heapSize && cmp(sequence[largest], sequence[right]))
                largest = right;

            if (index == largest)
                break;

            sequence.swap(index, largest);
            index = largest;
        }
    }
}

template<typename T>
mySequence<T>* HeapSort(const mySequence<T>& sequence, size_t from, size_t to, bool (*cmp)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return sequence.copy();
    }

    myBinaryHeap<T> binaryHeap(cmp);
    for (size_t i = from; i < to; i++) {
        binaryHeap.insert(sequence[i]);
    }

    mySequence<T>* resSequence = binaryHeap.getSequence().copy();

    for (size_t i = resSequence->length() - 1; i > 0; i--) {
        resSequence->swap(0, i);
        sortFuncPrivate::heapify(*resSequence, i, cmp);
    }

    return resSequence;
}

template<typename T>
mySequence<T>* HeapSort(const mySequence<T>& sequence, size_t from, size_t to) {
    return HeapSort(sequence, from, to, sortFuncPrivate::isLessDefault);
}

template<typename T>
mySequence<T>* HeapSort(const mySequence<T>& sequence, bool (*cmp)(const T& obj1, const T& obj2)) {
    return HeapSort(sequence, 0, sequence.length(), cmp);
}

template<typename T>
mySequence<T>* HeapSort(const mySequence<T>& sequence) {
    return HeapSort(sequence, 0, sequence.length(), sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_HEAPSORT_H
