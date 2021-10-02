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
    template<typename t1, typename t2>
    struct cmpType {
        static const bool item = false;
    };

    template<typename u>
    struct cmpType<u, u> {
        static const bool item = true;
    };

    static void copyArr(size_t count, const T* from, T* to) {
        for (size_t i = 0; i < count; i++) {
            to[i] = from[i];
        }
    }

    static void copyArr(size_t count, const T* from, T* to, long intent) {
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

    template<typename U, typename ...Args>
    void appendItems(size_t index, const U& item, Args...args) {
        appendItems(index, item);
        appendItems(index + 1, args...);
    }

    template<typename U>
    void appendItems(size_t index, const U& item) {
        if (cmpType<T, U>::item) {
            array[index] = item;
            return;
        }
        else {
            array[index] = static_cast<const T&>(item);
        }
    }

    size_t size = 0;                       //размер массива
    T* array = nullptr;                    //сам массив
    T* swapBuff = (T*) malloc(sizeof(T));  //буфер для свапа
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

        T& operator*() {
            return *item;
        }

        T* operator->() {
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
        for (auto &i : list) {
            array[ind] = i;
            ind++;
        }
    }

    template <typename U, typename ...Args>
    explicit myDynamicArray(const U& item, Args... args) {
        resize(sizeof...(args) + 1);
        appendItems(0, item, args...);
    }

    myDynamicArray(T* arr, size_t count) {  //Конструктор через массив и его длину
        size = count;
        array = new T[count];
        copyArr(count, arr, array);
    }

    ~myDynamicArray(){ //Деструктор
        delete[] array;
        free(swapBuff);
    }

    myDynamicArray<T>& operator = (const myDynamicArray<T>& dynamicArray) {
        delete[] array;
        resize(dynamicArray.size);
        copyArr(size, dynamicArray.array, array);
        return *this;
    }

    T get(size_t index) const {
        if (index >= size)
            throw indexOutOfRange();

        return array[index];
    }

    void set(const T& item, size_t index) {
        if (index >= size)
            throw indexOutOfRange();

        array[index] = item;
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
            array = nullptr;
            size = 0;
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
        if ((index >= newSize && (long) index + intent >= newSize) || index > size) {
            throw indexOutOfRange();
        }

        if (newSize == 0) {
            delete[] array;
            array = nullptr;
            size = 0;
            return;
        }

        T* newArr = new T[newSize];
        size_t minSize = (newSize > size ? size : newSize);
        copyArr(index, array, newArr);
        copyArr(minSize-index, array+index, newArr+index, intent);
        delete[] array;
        array = newArr;
        size = newSize;
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

//        T* item = (T*) malloc(sizeof(T));
        memcpy(swapBuff, array + index1, sizeof(T));
        memcpy(array + index1, array + index2, sizeof(T));    //более универсальный варик
        memcpy(array + index2, swapBuff, sizeof(T));
//        free(item);

//        T item = array[index1];
//        array[index1] = array[index2];                     //самый лёгкий варик
//        array[index2] = item;
    }

    void move(size_t indexFrom, size_t indexTo) {  //перемещает элемент с индексом 1 на место с индексом 2
        if (indexFrom >= size)
            throw indexOutOfRange();
        if (indexTo >= size)
            throw indexOutOfRange();

        if (indexFrom == indexTo)
            return;

        size_t count;
        if (indexFrom > indexTo) {
            count = indexFrom - indexTo;
            memcpy(swapBuff, array + indexFrom, sizeof(T));
            memmove(array + indexTo + 1, array + indexTo, sizeof(T) * count);
            memcpy(array + indexTo, swapBuff, sizeof(T));
//            T *items = (T*) malloc(count * sizeof(T));                 //TODO: Посоветоваться с В.В., может стоит эту память тоже выделить заранее, как у swap
//            memcpy(items, array + indexTo, count * sizeof(T));
//            memcpy(array + indexTo, array + indexFrom, sizeof(T));
//            memcpy(array + indexTo + 1, items, count * sizeof(T));
//            free(items);
        }
        else {
            count = indexTo - indexFrom;
            memcpy(swapBuff, array + indexFrom, sizeof(T));
            memmove(array + indexFrom, array + indexFrom + 1, sizeof(T) * count);
            memcpy(array + indexTo, swapBuff, sizeof(T));
//            T *items = (T*) malloc(count * sizeof(T));
//            memcpy(items, array + indexFrom + 1, count * sizeof(T));
//            memcpy(array + indexTo, array + indexFrom, sizeof(T));
//            memcpy(array + indexFrom, items, count * sizeof(T));
//            free(items);
        }
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
