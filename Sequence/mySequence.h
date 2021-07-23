//
// Created by Grisha on 10.07.2021.
//

#ifndef BASE_CLASSES_MYSEQUENCE_H
#define BASE_CLASSES_MYSEQUENCE_H

#include <iostream>

template<typename T>
class mySequence {
public:
    class IndexOutOfRange{
    public:
        size_t length = 0;
        size_t index = 0;
        IndexOutOfRange(size_t length, size_t index): length(length), index(index) {};
        IndexOutOfRange() = default;
    };

    class iterator;

    virtual T& getFirst() = 0;
    virtual const T& getFirst() const = 0;

    virtual T& getLast() = 0;
    virtual const T& getLast() const = 0;

    virtual T& get(size_t index) = 0;
    virtual const T& get(size_t index) const = 0;

    virtual T& operator [] (size_t index) = 0;
    virtual const T& operator [] (size_t index) const = 0;

    virtual void set(T item, size_t index) = 0;
    virtual void swap(size_t index1, size_t index2) = 0;

    virtual mySequence<T>& getSubSequence(
            size_t startIndex, size_t endIndex) const = 0;

    virtual size_t length() const = 0;

    virtual void append (T item) = 0;
    virtual void prepend(T item) = 0;
    virtual void insert (T item, size_t index) = 0;
    virtual void pop(size_t index) = 0;

    virtual mySequence<T>& concat (const mySequence<T>& sequence) = 0;
    virtual mySequence<T>& reverse() = 0;

    virtual size_t find(T item) const = 0;
    virtual size_t find(const mySequence<T>& sequence) const = 0;
};

template<typename T>
std::ostream& operator << (std::ostream& cout, const mySequence<T>& arraySequence) {
    cout << "{";
    for (int i = 0; i < arraySequence.length(); i++) {
        cout << arraySequence[i];
        if (i == arraySequence.length() - 1)
            break;

        cout << ", ";
    }
    return cout << "}";
}

#endif //BASE_CLASSES_MYSEQUENCE_H
