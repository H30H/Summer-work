//
// Created by Grisha on 10.07.2021.
//

#ifndef BASE_CLASSES_MYSEQUENCE_H
#define BASE_CLASSES_MYSEQUENCE_H

template<class T>
class mySequence {
public:
    class IndexOutOfRange{
    public:
        size_t length = 0;
        size_t index = 0;
        IndexOutOfRange(size_t length, size_t index): length(length), index(index) {};
        IndexOutOfRange() = default;
    };

    virtual T getFirst() const = 0;
    virtual T getLast() const = 0;
    virtual T get(size_t index) const = 0;
    virtual void set(T item, size_t index) = 0;
    virtual T& operator [] (size_t index) const = 0;

    virtual mySequence<T>& getSubSequence(
            size_t startIndex, size_t endIndex) const = 0;

    virtual size_t length() const = 0;

    virtual void append (T item) = 0;
    virtual void prepend(T item) = 0;
    virtual void insert (T item, size_t index) = 0;

    virtual mySequence<T>& concat (const mySequence<T>& sequence) = 0;
    virtual mySequence<T>& reverse() = 0;

    virtual size_t find(T item) const = 0;
    virtual size_t find(const mySequence<T>& sequence) const = 0;
};


#endif //BASE_CLASSES_MYSEQUENCE_H
