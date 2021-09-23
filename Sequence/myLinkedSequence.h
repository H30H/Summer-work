//
// Created by Grisha on 23.08.2021.
//

#ifndef BASE_CLASSES_MYLINKEDSEQUENCE_H
#define BASE_CLASSES_MYLINKEDSEQUENCE_H

#include "mySequence.h"
#include "../LinkedList/myLinkedList.h"
template<typename T>
class myLinkedSequence: mySequence<T> {
private:
    myLinkedList<T> linkedList;
public:
    using IndexOutOfRange = mySequence<T>::IndexOutOfRange;

    myLinkedSequence() = default;

    explicit myLinkedSequence(const T& item) {
        linkedList.append(item);
    }

    myLinkedSequence(const myLinkedSequence<T>& linkedSequence) {
        linkedList = linkedSequence.linkedList;
    }

    explicit myLinkedSequence(const mySequence<T>& sequence) {
        for (size_t i = 0; i < sequence.length(); i++) {
            linkedList.append(i);
        }
    }

    explicit myLinkedSequence(T arr[], size_t size) {
        for (size_t i = 0; i < size; i++) {
            linkedList.append(arr[i]);
        }
    }

    myLinkedSequence(std::initializer_list<T> list) {
        for (auto i : list) {
            linkedList.append(i);
        }
    }

    explicit myLinkedSequence(const myLinkedList<T>& list) {
        linkedList = list;
    }

    template<typename U>
    explicit myLinkedSequence(U begin, U end) {
        linkedList = myLinkedList::myLinkedList<T>(begin, end);
    }

    T& getFirst() {
        if (linkedList.length() == 0)
            throw IndexOutOfRange();

        return linkedList[0];
    }

    const T& getFirst() const {
        if (linkedList.length() == 0)
            throw IndexOutOfRange();

        return linkedList[0];
    }

    T& getLast() {
        if (linkedList.length() == 0)
            throw IndexOutOfRange();

        return linkedList[linkedList.length() - 1];
    }

    const T& getLast() const {
        if (linkedList.length() == 0)
            throw IndexOutOfRange();

        return linkedList[linkedList.length() - 1];
    }

    T& get(size_t index) {
        if (index >= linkedList.length())
            throw IndexOutOfRange();

        return linkedList.get(index);
    }

    const T& get(size_t index) const {
        if (index >= linkedList.length())
            throw IndexOutOfRange();

        return linkedList.get(index);
    }

    T& operator [] (size_t index) {
        if (index >= linkedList.length())
            throw IndexOutOfRange();

        return linkedList[index];
    }

    const T& operator [] (size_t index) const {
        if (index >= linkedList.length())
            throw IndexOutOfRange();

        return linkedList[index];
    }

    void set(const T& item, size_t index) {
        if (index >= linkedList.length())
            throw IndexOutOfRange();

        linkedList.sew(index, index);
    }

    void swap(size_t index1, size_t index2) {
        if (index1 >= linkedList.length())
            throw IndexOutOfRange();

        if (index2 >= linkedList.length())
            throw IndexOutOfRange();

        linkedList.swap(index1, index2);
    }

    mySequence<T> getSubSequence(
            size_t startIndex, size_t endIndex) const {
        myLinkedSequence<T> res;

        auto* iter = linkedList.begin();
        for (size_t i = 0; i < startIndex; i++, iter++);

        for (size_t i = startIndex; i < endIndex; i++, iter++)
            res.append(iter.operator->());

        return res;
    }

    size_t length() const {
        return linkedList.length();
    }

    void append (const T& item) {
        linkedList.append(item);
    }

    void prepend(const T& item) {
        linkedList.prepend(item);
    }

    void insert (const T& item, size_t index) {
        linkedList.insert(item, index);
    }

    T pop() {
        return linkedList.pop();
    }

    T pop(size_t index) {
        return linkedList.pop(index);
    }

    mySequence<T>& concat (const mySequence<T>& sequence) {
        for (size_t i = 0; i < sequence.length(); i++) {
            linkedList.append(sequence[i]);
        }
        return *this;
    }

    mySequence<T>& reverse() {
        linkedList.reverse();
        return *this;
    }

    mySmartPointer<myLinkedSequence<T>> copy(bool clear = false) const {
        if (clear)
            return new myLinkedSequence<T>;
        return new myLinkedSequence<T>(*this);
    }
};


#endif //BASE_CLASSES_MYLINKEDSEQUENCE_H
