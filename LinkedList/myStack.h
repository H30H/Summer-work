//
// Created by Grisha on 02.08.2021.
//

#ifndef BASE_CLASSES_MYSTACK_H
#define BASE_CLASSES_MYSTACK_H

#include "myLinkedList.h"

template<class T>
class myStack {
private:
    myLinkedList<T> linkedList;
public:
    myStack() = default;

    myStack(const myStack<T>& stack) = default;

    explicit myStack(const T& item) {
        linkedList.prepend(item);
    }

    explicit myStack(T *arr, size_t size) {
        for (size_t i = 0; i < size; i++) {
            add(arr[i]);
        }
    }

    myStack(std::initializer_list<T> list) {
        for (auto &i : list) {
            add(i);
        }
    }

    void add(const T& item) {
        linkedList.prepend(item);
    }

    T& get() {
        return linkedList.get(0);
    }

    const T& get() const {
        return linkedList.get(0);
    }

    T& pop() {
        return linkedList.pop(0);
    }

    size_t length() const {
        return linkedList.length();
    }
};


#endif //BASE_CLASSES_MYSTACK_H
