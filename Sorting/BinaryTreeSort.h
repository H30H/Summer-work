//
// Created by Grisha on 20.08.2021.
//

#ifndef BASE_CLASSES_BINARYTREESORT_H
#define BASE_CLASSES_BINARYTREESORT_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"
#include "../BinaryTree/myBinaryTree.h"

template<typename T>
mySequence<T>& BinaryTreeSort(mySequence<T>& sequence, size_t from, size_t to, bool (*isLess)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2)
        return sequence;

    myBinaryTree<T> binaryTree(isLess, sortFuncPrivate::isTreeSameFunc<T>);

    for (size_t i = from; i < to; i++) {
        binaryTree.insert(sequence[i]);
    }

    size_t index = from;

    for (auto &i : binaryTree) {
        sequence[index++] = i;
    }

    return sequence;
}

template<typename T>
mySequence<T>& BinaryTreeSort(mySequence<T>& sequence, size_t start, size_t end) {
    return BinaryTreeSort(sequence, start, end, sortFuncPrivate::isLessDefault);
}


template<typename T>
mySequence<T>& BinaryTreeSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2)) {
    return BinaryTreeSort(sequence, 0, sequence.length(), isLess);
}

template<typename T>
mySequence<T>& BinaryTreeSort(mySequence<T>& sequence) {
    return BinaryTreeSort(sequence, 0, sequence.length(), sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_BINARYTREESORT_H
