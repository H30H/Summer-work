//
// Created by Grisha on 23.07.2021.
//

#ifndef BASE_CLASSES_MYBINARYHEAP_H
#define BASE_CLASSES_MYBINARYHEAP_H

#include "myBinaryTree.h"
#include "../Sequence/myArraySequence.h"
#include "iostream"
template<typename T>
class myBinaryHeap {
protected:
    static bool isLessPrivate(const T& item1, const T& item2) {
        return item1 < item2;
    }

    static bool isSamePrivate(const T& item1, const T& item2) {
        return item1 == item2;
    }
private:
    myArraySequence<T> heap;

    bool (*isLess)(const T& item1, const T& item2);
    bool (*isSame)(const T& item1, const T& item2);
public:

    class iterator {

    };

    explicit myBinaryHeap(bool (*isLessFunc)(const T& item1, const T& item2) = isLessPrivate,
              bool (*isSameFunc)(const T& item1, const T& item2) = isSamePrivate):
            isLess(isLessFunc), isSame(isSameFunc) {

        if (!isLess)
            isLess = isLessPrivate;

        if (!isSame)
            isSame = isSamePrivate;
    }

    explicit myBinaryHeap(const T& item, bool (*isLessFunc)(const T& item1, const T& item2) = isLessPrivate,
                       bool (*isSameFunc)(const T& item1, const T& item2) = isSamePrivate):
                       isLess(isLessFunc), isSame(isSameFunc) {
        if (!isLess)
            isLess = isLessPrivate;

        if (!isSame)
            isSame = isSamePrivate;

        heap(item);
    }

    explicit myBinaryHeap(T arr[], size_t size,  bool (*isLessFunc)(const T& item1, const T& item2) = isLessPrivate,
                       bool (*isSameFunc)(const T& item1, const T& item2) = isSamePrivate):
                       isLess(isLessFunc), isSame(isSameFunc) {
        if (!isLess)
            isLess = isLessPrivate;

        if (!isSame)
            isSame = isSamePrivate;

        heap(arr, size);
        heapify();
    }

    myBinaryHeap(const std::initializer_list<T>& list, bool (*isLessFunc)(const T&, const T&) = isLessPrivate,
                       bool (*isSameFunc)(const T&, const T&) = isSamePrivate):
                       isLess(isLessFunc), isSame(isSameFunc){
        if (!isLess)
            isLess = isLessPrivate;

        if (!isSame)
            isSame = isSamePrivate;

        heap(list);
        heapify();
    }

    template<typename iterator>
    explicit myBinaryHeap(iterator begin, iterator end, bool (*isLessFunc)(const T&, const T&) = isLessPrivate,
                               bool (*isSameFunc)(const T&, const T&) = isSamePrivate):
                               isLess(isLessFunc), isSame(isSameFunc) {
        if (!isLess)
            isLess = isLessPrivate;

        if (!isSame)
            isSame = isSamePrivate;

        heap(begin, end);
        heapify();
    }

    myBinaryHeap(const myBinaryHeap<T>& binaryHeap) {
        isLess(binaryHeap.isLess);
        isSame(binaryHeap.isSame);
        heap(binaryHeap.heap);
    }

    virtual void insert(const T& item) {
        heap.append(item);
        size_t startIndex = heap.length() - 1;
        size_t prevIndex = (startIndex - 1) / 2;

        while (startIndex != 0 && isLess(heap[prevIndex], heap[startIndex])) {
            heap.swap(prevIndex, startIndex);
            startIndex = prevIndex;
            prevIndex = (prevIndex - 1) / 2;
        }
    }

    virtual T popMax() {
        heap.swap(0, heap.length() - 1);
        T res = heap.pop();
        heapify(0);
        return res;
    }

    virtual T& getMax() {
        return heap[0];
    }

    virtual const T& getMax() const {
        return heap[0];
    }

    void heapify(size_t index) {
        size_t left;
        size_t right;
        size_t largest;
        size_t heapSize = heap.length();

        while(true) {
            left  = index * 2 + 1;
            right = index * 2 + 2;
            largest = index;

            if (left < heapSize && isLess(heap[largest], heap[left]))
                largest = left;

            if (right < heapSize && isLess(heap[largest], heap[right]))
                largest = right;

            if (index == largest)
                break;

            heap.swap(index, largest);
            index = largest;
        }
    }

    void heapify() {
        for (size_t i = heap.length() / 2; i >= 0; i--) {
            heapify(i);
        }
    }

    const myArraySequence<T>& getSequence() const {
        return heap;
    }
};

#endif //BASE_CLASSES_MYBINARYHEAP_H
