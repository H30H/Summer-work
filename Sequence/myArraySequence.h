//
// Created by Grisha on 10.07.2021.
//

#ifndef BASE_CLASSES_MYARRAYSEQUENCE_H
#define BASE_CLASSES_MYARRAYSEQUENCE_H

#include "mySequence.h"
#include "../DynamicArray/myDynamicArray.h"

template<typename T>
class myArraySequence: public mySequence<T> {
public:
    static size_t defaultResizeFunc(size_t size, size_t newSize) {
        if (size == 0)
            size = 1;

        while (size <= newSize)
            size *= 2;

        while (size > newSize * 2 && size != 1) {
            size /= 2;
        }

        return size;
    }
private:
    myDynamicArray<T> dynamicArray;
    size_t size = 0;

    size_t (*resizeFunc)(size_t size, size_t newSize) = defaultResizeFunc;

    void resizePrivate(size_t newSize) {
        resizePrivate(newSize, 0, 0);
    }

    void resizePrivate(size_t newSize, long intent) {
        resizePrivate(newSize, intent, 0);
    }

    void resizePrivate(size_t newSize, long intent, size_t index) {
        auto dynSize = resizeFunc(0, newSize);
        size = newSize;
        if (dynamicArray.length() == dynSize && intent == 0 && index == 0) {
            return;
        }
        dynamicArray.resize(dynSize, intent, index);
    }

public:
    using seqIterator = typename mySequence<T>::seqIterator;

    class iterator: public mySequence<T>::seqIterator/*std::iterator<std::bidirectional_iterator_tag, T>*/ { //класс итератора
    private:
        T* item = nullptr;
    public:
        explicit iterator(T* item): item(item) {}

        iterator(const iterator &other): item(other.item) {}

        explicit iterator(const typename myDynamicArray<T>::iterator& other): item(other.item) {}

        iterator& operator = (const iterator &other) {
            item(other.item);
            return *this;
        }

        T& operator*() const {
            return *item;
        }

        T* operator->() const {
            return item;
        }

        bool operator==(const iterator &other) const {
            return item == other.item;
        }

        bool operator!=(const iterator &other) const {
            return item != other.item;
        }

        iterator& operator + (int num) {
            if (num < 0)
                return operator-(-num);

            for (int i = 0; i < num; i++) {
                operator++();
            }
            return *this;
        }

        iterator& operator - (int num) {
            if (num < 0)
                return operator+(-num);

            for (int i = 0; i < num; i++) {
                operator--();
            }
            return *this;
        }

        iterator& operator++() {
            item++;
            return *this;
        }

        iterator& operator++(int) {
            T* res = item;
            ++item;
            return *(new iterator(res));
        }

        iterator& operator--() {
            item--;
            return *this;
        }

        iterator& operator--(int) {
            T* res = item;
            --item;
            return *(new iterator(res));
        }
    }; //Класс итератора

    myArraySequence() = default;

    explicit myArraySequence(T item): size(1), dynamicArray(item) {}

    myArraySequence(const myArraySequence<T>& arraySequence): size(arraySequence.size),
                                                              dynamicArray(arraySequence.dynamicArray),
                                                              resizeFunc(arraySequence.resizeFunc) {}

    explicit myArraySequence(const myDynamicArray<T>& dynamicArray1) {
        dynamicArray = dynamicArray1;
        resizePrivate(dynamicArray.length());
    }

    myArraySequence(T* arr, size_t count) {
        resizePrivate(count);
        for (int i = 0; i < count; i++) {
            dynamicArray[i] = arr[i];
        }
    }
    myArraySequence(std::initializer_list<T> list) {
        dynamicArray = myDynamicArray<T>(list);
        resizePrivate(dynamicArray.length());
    }

    template<typename U>
    explicit myArraySequence(U begin, U end) {
        dynamicArray = myDynamicArray<T>(begin, end);
        resizePrivate(dynamicArray.length());
    }

    explicit myArraySequence(const mySequence<T>& sequence) {
        for (size_t i = 0; i < sequence.length(); i++) {
            append(sequence[i]);
        }
    }

    myArraySequence<T>& operator=(const myArraySequence<T>& arraySequence ) {
        size = arraySequence.size;
        dynamicArray = arraySequence.dynamicArray;
        resizeFunc = arraySequence.resizeFunc;
        return *this;
    }

    T& getFirst() {
        if (size == 0)
            throw typename mySequence<T>::IndexOutOfRange();

        return dynamicArray[0];
    }

    const T& getFirst() const {
        if (size == 0)
            throw typename mySequence<T>::IndexOutOfRange();

        return dynamicArray[0];
    }

    T& getLast() {
        if (size == 0)
            throw typename mySequence<T>::IndexOutOfRange();

        return dynamicArray[size - 1];
    }

    const T& getLast() const {
        if (size == 0)
            throw typename mySequence<T>::IndexOutOfRange();

        return dynamicArray[size - 1];
    }

    T& get(size_t index) {
        if (index >= size)
            throw typename mySequence<T>::IndexOutOfRange();

        return dynamicArray.get(index);
    }

    const T& get(size_t index) const {
        if (index >= size)
            throw typename mySequence<T>::IndexOutOfRange();

        return dynamicArray.get(index);
    }

    T& operator [] (size_t index) {
        if (index >= size)
            throw typename mySequence<T>::IndexOutOfRange();

        return dynamicArray[index];
    }

    const T& operator [] (size_t index) const {
        if (index >= size)
            throw typename mySequence<T>::IndexOutOfRange();

        return dynamicArray[index];
    }

    void set(const T& item, size_t index) {
        if (index >= size)
            throw typename mySequence<T>::IndexOutOfRange();

        dynamicArray.set(item, index);
    }

    void swap(size_t index1, size_t index2) {
        if (index1 >= size)
            throw typename mySequence<T>::IndexOutOfRange();
        if (index2 >= size)
            throw typename mySequence<T>::IndexOutOfRange();

        if (index1 == index2)
            return;

        dynamicArray.swap(index1, index2);
    }

    mySequence<T>& getSubSequence(size_t startIndex, size_t endIndex) const {
        if (startIndex >= size)
            throw typename mySequence<T>::IndexOutOfRange();
        if (endIndex > size)
            throw typename mySequence<T>::IndexOutOfRange();

        return *(new myArraySequence<T>(dynamicArray.begin() + startIndex,
                                        dynamicArray.begin() + endIndex)); //Возвращает последовательность через итератор
    }

    size_t length() const {
        return size;
    }

    void append (const T& item) {
        if (size != 0 && &item >= &dynamicArray[0] && &item <= &dynamicArray[dynamicArray.length() - 1]) { //добавляется элемент из массива
            size_t indexItem = ((size_t)&item - (size_t)&dynamicArray[0]) / sizeof(T);
            resizePrivate(size+1);
            dynamicArray[size-1] = dynamicArray[indexItem];
        }
        else {
            resizePrivate(size+1);
            dynamicArray[size-1] = item;
        }
    }

    void prepend(const T& item) {
        if (size != 0 && &item >= &dynamicArray[0] && &item <= &dynamicArray[dynamicArray.length() - 1]) { //добавляется элемент из массива
            size_t indexItem = ((size_t)&item - (size_t)&dynamicArray[0]) / sizeof(T);
            resizePrivate(size+1, 1);
            dynamicArray[0] = dynamicArray[indexItem + 1];
        }
        else {
            resizePrivate(size+1, 1);
            dynamicArray[0] = item;
        }
    }

    void insert (const T& item, size_t index) {
        if (index > size)
            throw typename mySequence<T>::IndexOutOfRange();
        if (index == 0) {
            prepend(item);
            return;
        }
        if (index == size) {
            append(item);
            return;
        }

        if (&item >= &dynamicArray[0] && &item <= &dynamicArray[dynamicArray.length() - 1]) {       //добавляется элемент из массива
            size_t itemIndex = ((size_t)&item - (size_t)&dynamicArray[0]) / sizeof(T);
            resizePrivate(size+1, 1, index);
            if (itemIndex > index)
                itemIndex++;
            dynamicArray[index] = dynamicArray[itemIndex];
        }
        else {
            resizePrivate(size+1, 1, index);
            dynamicArray[index] = item;
        }
//        dynamicArray[index] = item;
    }

    T& pop() {
        return pop(size - 1);
    }

    T& pop(size_t index) {
        if (index >= size)
            throw typename mySequence<T>::IndexOutOfRange();

        T& res = dynamicArray[index];

        resizePrivate(size - 1, -1, index);
        return res;
    }

    myArraySequence<T>& concat(const mySequence<T>& sequence) {
        auto startInd = size;
        resizePrivate(size + sequence.length());
        for (int i = 0; i < sequence.length(); i++, startInd++) {
            dynamicArray[startInd] = sequence[i];
        }
        return *this;
    }

     myArraySequence<T>& reverse() {
        for (int i = 0, j = size - 1; i < size/2; i++, j--) {
            dynamicArray.swap(i, j);
        }
         return *this;
    }

    seqIterator& begin() const {
        return *(new iterator(dynamicArray.begin().operator->()));
    }

    seqIterator& end() const {
        return *(new iterator(dynamicArray.begin().operator->()));
    }
};

#endif //BASE_CLASSES_MYARRAYSEQUENCE_H
