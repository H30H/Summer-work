//
// Created by Grisha on 09.08.2021.
//

#ifndef BASE_CLASSES_MYQUEUE_H
#define BASE_CLASSES_MYQUEUE_H

#include "myLinkedList.h"


template<typename T>
class myQueue {
private:
    myLinkedList<T> linkedList;
public:
    myQueue() = default;

    myQueue(const myQueue<T>& stack) = default;

    explicit myQueue(const T& item) {
        linkedList.append(item);
    }

    explicit myQueue(T *arr, size_t size) {
        for (size_t i = 0; i < size; i++) {
            add(arr[i]);
        }
    }

    myQueue(std::initializer_list<T> list) {
        for (auto &i : list) {
            add(i);
        }
    }

    void add(const T& item) {
        linkedList.append(item);
    }

    T& get() {
        return linkedList.get(0);
    }

    const T& get() const {
        return linkedList.get(0);
    }

    T pop() {
        return linkedList.pop(0);
    }

    size_t length() const {
        return linkedList.length();
    }
};

#endif //BASE_CLASSES_MYQUEUE_H
