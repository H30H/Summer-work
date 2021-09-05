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

    mySequence<T>& operator = (const mySequence<T>& sequence) {
        if (length() < sequence.length()) {
            size_t i = 0;
            for (i; i < length(); i++) {
                operator[](i) = sequence[i];
            }
            for (i; i < sequence.length(); i++) {
                append(sequence[i]);
            }
        }
        else {
            size_t i = 0;
            for (i; i < sequence.length(); i++) {
                operator[](i) = sequence[i];
            }
            while (length() != i)
                pop();
        }
        return *this;
    }

//    using seqIterator = std::iterator<std::bidirectional_iterator_tag, T>;

    class seqIterator: std::iterator<std::bidirectional_iterator_tag, T> { //класс итератора
    public:
        virtual T& operator*() const = 0;

        virtual T* operator->() const = 0;

        virtual seqIterator& operator + (int num) = 0;

        virtual seqIterator& operator - (int num) = 0;

        virtual seqIterator& operator++() = 0;

        virtual seqIterator& operator++(int) = 0;

        virtual seqIterator& operator--() = 0;

        virtual seqIterator& operator--(int) = 0;
    }; //Класс итератора для последовательностей

    virtual T& getFirst() = 0;
    virtual const T& getFirst() const = 0;

    virtual T& getLast() = 0;
    virtual const T& getLast() const = 0;

    virtual T& get(size_t index) = 0;
    virtual const T& get(size_t index) const = 0;

    virtual T& operator [] (size_t index) = 0;
    virtual const T& operator [] (size_t index) const = 0;

    virtual void set(const T& item, size_t index) = 0;
    virtual void swap(size_t index1, size_t index2) = 0;

    virtual mySequence<T>& getSubSequence(
            size_t startIndex, size_t endIndex) const = 0;

    virtual size_t length() const = 0;

    virtual void append (const T& item) = 0;
    virtual void prepend(const T& item) = 0;
    virtual void insert (const T& item, size_t index) = 0;
    virtual T& pop() = 0;
    virtual T& pop(size_t index) = 0;

    virtual mySequence<T>& concat(const mySequence<T>& sequence) = 0;
    virtual mySequence<T>& reverse() = 0;

    virtual seqIterator& begin() const = 0;
    virtual seqIterator& end() const = 0;
};

template<typename T>
std::ostream& operator << (std::ostream& cout, const mySequence<T>& arraySequence) {
    cout << "{";
    for (size_t i = 0; i < arraySequence.length(); i++) {
        cout << arraySequence[i];
        if (i == arraySequence.length() - 1)
            break;

        cout << ", ";
    }
    return cout << "}";
}

#endif //BASE_CLASSES_MYSEQUENCE_H
