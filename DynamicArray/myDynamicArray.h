//
// Created by Grisha on 10.07.2021.
//

#ifndef BASE_CLASSES_MYDYNAMICARRAY_H
#define BASE_CLASSES_MYDYNAMICARRAY_H

#include <iostream>
#include <iterator>
#include <cstring>

template<typename T>
class myDynamicArray {
private:
    size_t size = 0;
    T* array = nullptr;

    static void copyArr(size_t count, T* from, T* to) {
        for (size_t i = 0; i < count; i++) {
            to[i] = from[i];
        }
    }

    static void copyArr(size_t count, T* from, T* to, long intent) {
        if (intent < 0) {
            for (size_t i = 0, j = -intent; j < count; i++, j++) {
                to[i] = from[j];
            }
        }
        else {
            for (size_t i = intent, j = 0; j < count; i++, j++) {
                to[i] = from[j];
            }
        }
    }

public:
    class indexOutOfRange{};

    class iterator : public std::iterator<std::bidirectional_iterator_tag, T> { //класс итератора
    private:
        T* item = nullptr;
    public:
        explicit iterator(T* item): item(item) {}

        iterator(const iterator &other): item(other.item) {}

        iterator& operator = (const iterator &other) {
            item(other.item);
            return *this;
        }

        T &operator*() const {
            return *item;
        }

        T *operator&() const {
            return item;
        }

        bool operator==(const iterator &other) const {
            return item == other.item;
        }

        bool operator!=(const iterator &other) const {
            return item != other.item;
        }

        iterator operator + (size_t num) {
            for (int i = 0; i < num; i++) {
                operator++();
            }
            return *this;
        }

        iterator operator + (int num) {
            if (num < 0)
                return operator-(-num);

            for (int i = 0; i < num; i++) {
                operator++();
            }
            return *this;
        }

        iterator operator - (size_t num) {
            for (int i = 0; i < num; i++) {
                operator--();
            }
            return *this;
        }

        iterator operator - (int num) {
            if (num < 0)
                return operator+(-num);

            for (int i = 0; i < num; i++) {
                operator--();
            }
            return *this;
        }

        iterator &operator++() {
            item++;
            return *this;
        }

        iterator operator++(int) {
            T* res = item;
            ++item;
            return iterator(res);
        }

        iterator &operator--() {
            item--;
            return *this;
        }

        iterator operator--(int) {
            T* res = item;
            --item;
            return iterator(res);
        }
    }; //Класс итератора

    myDynamicArray() = default; //пустой конструктор

    explicit myDynamicArray(T item) { //Конструктор через один объект
        size = 1;
        array = new T(item);
    }

    myDynamicArray(const myDynamicArray<T>& dynamicArray) { //Копирующий конструктор
        size = dynamicArray.size;
        array = new T[size];
        copyArr(size, dynamicArray.array, array);
    }

    template<typename iterator>
    explicit myDynamicArray(iterator begin, iterator end) { //Конструктор через итератор: myDynamicArray<int> dArray(thing.begin(), thing.end())
        resize(std::distance(begin, end));
        size_t ind = 0;
        for (auto i = begin; i != end; i++, ind++) {
            array[ind] = *i;
        }
    }

    myDynamicArray(std::initializer_list<T> list) { //Конструктор через массив (прикольная вещь): myDynamicArray<int> dArray{1, 2, 3, 4, 5};
        resize(list.size());
        size_t ind = 0;
        for (auto i = list.begin(); i != list.end(); i++, ind++) {
            array[ind] = *i;
        }
    }

    myDynamicArray(T* arr, size_t count) {  //Конструктор через массив и его длину
        size = count;
        array = new T[count];
        copyArr(count, arr, array);
    }

    ~myDynamicArray(){ //Деструктор
        delete[] array;
    }

    T& get(size_t index) {
        if (index >= size)
            throw indexOutOfRange();

        return array[index];
    }

    const T& get(size_t index) const {
        if (index >= size)
            throw indexOutOfRange();

        return array[index];
    }

    void set(T item, size_t index) {
        if (index >= size)
            throw indexOutOfRange();

        array[index] = size;
    }

    T& operator [] (size_t index) {
        if (index >= size)
            throw indexOutOfRange();

        return array[index];
    }

    const T& operator [] (size_t index) const {
        if (index >= size)
            throw indexOutOfRange();

        return array[index];
    }

    void resize(size_t newSize) {
        if (newSize == size)
            return;

        resize(newSize, 0);
    }

    void resize(size_t newSize, long intent) {
        if (newSize == 0) {
            delete[] array;
            size = 0;
            array = nullptr;
            return;
        }

        T* newArr = new T[newSize];
        size_t minSize = (newSize > size ? size : newSize);
        copyArr(minSize, array, newArr, intent);
        delete[] array;
        array = newArr;
        size = newSize;
    }

    void resize(size_t newSize, long intent, size_t index) {
        if ((index >= newSize && index + intent >= newSize) || index > size) {
            throw indexOutOfRange();
        }

        T* newArr = new T[newSize];
        size_t minSize = (newSize > size ? size : newSize);
        copyArr(index, array, newArr);
        copyArr(minSize-index, array+index, newArr+index, intent);
        delete[] array;
        array = newArr;
        size = newSize;
    }

    bool operator == (const myDynamicArray<T>& dynamicArray) const {
        if (size != dynamicArray.size)
            return false;

        for (int i = 0; i < size; i++) {
            if (array[i] != dynamicArray.array[i])
                return false;
        }
        return true;
    }

    bool operator != (const myDynamicArray<T>& dynamicArray) const {
        return !(operator==(dynamicArray));
    }

    myDynamicArray<T>& operator = (const myDynamicArray<T>& dynamicArray) {
        delete[] array;
        resize(dynamicArray.size);
        copyArr(size, dynamicArray.array, array);
        return *this;
    }

    size_t length() const {
        return size;
    }

    void swap(size_t index1, size_t index2) {
        if (index1 >= size)
            throw indexOutOfRange();
        if (index2 >= size)
            throw indexOutOfRange();

        if (index1 == index2)
            return;

        T* item = (T*) malloc(sizeof(T));
        memcpy(item, array + index1, sizeof(T));
        memcpy(array + index1, array + index2, sizeof(T));
        memcpy(array + index2, item, sizeof(T));
        free(item);
    }

    iterator begin() const { //Функция для итератора, возвращает итератор, указывающий на начало
        return iterator(array);
    }

    iterator end() const { //Функция для итератора, возвращает итератор, указывающий на конец
        return iterator(array + size);
    }
};

template<typename T>
std::ostream& operator << (std::ostream& cout, const myDynamicArray<T>& dynamicArray) {
    cout << "{";
    for (int i = 0; i < dynamicArray.length(); i++) {
        cout << dynamicArray[i];
        if (i == dynamicArray.length() - 1)
            break;

        cout << ", ";
    }
    return cout << "}";
}


#endif //BASE_CLASSES_MYDYNAMICARRAY_H
