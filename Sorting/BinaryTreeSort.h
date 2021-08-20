//
// Created by Grisha on 20.08.2021.
//

#ifndef BASE_CLASSES_BINARYTREESORT_H
#define BASE_CLASSES_BINARYTREESORT_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"
#include "../BinaryTree/myBinaryTree.h"
#include "cstring"

namespace sortFuncPrivate {
    template<typename T>
    bool TreeItemSameFunc(const T& obj1, const T& obj2) {
        return false;
    }
}

template<typename T>
mySequence<T>& BinaryTreeSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2)) {
    myBinaryTree<T> binaryTree(isLess, sortFuncPrivate::TreeItemSameFunc<T>);

    for (size_t i = 0; i < sequence.length(); i++) {
        binaryTree.insert(sequence[i]);
    }

    size_t index = 0;

    for (auto &i : binaryTree) {
        sequence[index++] = i;
    }

    return sequence;
}

template<typename T>
mySequence<T>& BinaryTreeSort(mySequence<T>& sequence) {
    return BinaryTreeSort(sequence, sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_BINARYTREESORT_H
