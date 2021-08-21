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

        while (size < newSize)
            size *= 2;

        while (size > newSize * 2) {
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
        dynamicArray.resize(dynSize, intent, index);
    }

public:
    class iterator: std::iterator<std::bidirectional_iterator_tag, T> { //класс итератора
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

        T& operator*() {
            return *item;
        }

        const T& operator*() const {
            return *item;
        }

        T* operator&() {
            return item;
        }

        const T* operator&() const {
            return item;
        }

        bool operator==(const iterator &other) const {
            return item == other.item;
        }

        bool operator!=(const iterator &other) const {
            return item != other.item;
        }

        iterator& operator + (int num) const {
            if (num < 0)
                return operator-(-num);

            for (int i = 0; i < num; i++) {
                operator++();
            }
            return *this;
        }

        iterator& operator - (int num) const {
            if (num < 0)
                return operator+(-num);

            for (int i = 0; i < num; i++) {
                operator--();
            }
            return *this;
        }

        iterator& operator++() const {
            item++;
            return *this;
        }

        iterator& operator++(int) const {
            T* res = item;
            ++item;
            return *(new iterator(res));
        }

        iterator& operator--() const {
            item--;
            return *this;
        }

        iterator& operator--(int) const {
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
        dynamicArray = myDynamicArray<int>(list);
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

    myArraySequence<T>& getSubSequence(
            size_t startIndex, size_t endIndex) const {
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
        resizePrivate(size+1);
        dynamicArray[size-1] = item;
    }

    void prepend(const T& item) {
        resizePrivate(size+1, 1);
        dynamicArray[0] = item;
    }

    void insert (const T& item, size_t index) {
        if (index >= size)
            throw typename mySequence<T>::IndexOutOfRange();


        resizePrivate(size+1, 1, index);
        dynamicArray[index] = item;
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

    size_t find(const T& item) const {
        for (size_t i = 0; i < size; i++) {
            if (item == dynamicArray[i])
                return i;
        }
        return -1;
    }

    size_t find(const mySequence<T>& sequence) const {
        if (sequence.length() > size) {
            return -1;
        }
        for (size_t i = 0, j = 0; i + sequence.length() - j < size; i++) {
            if (dynamicArray[i] == sequence[j])
                j++;
            else
                j = 0;

            if (j == sequence.length())
                return i - j + 1;
        }

        return -1;
    }

    iterator& begin() {
        return iterator(&dynamicArray.begin());
    }

    const iterator& begin() const {
        return iterator(&dynamicArray.begin());
    }

    iterator& end() {
        return iterator(&dynamicArray.begin() + size);
    }
    const iterator& end() const {
        return iterator(&dynamicArray.begin() + size);
    }
};

#endif //BASE_CLASSES_MYARRAYSEQUENCE_H
