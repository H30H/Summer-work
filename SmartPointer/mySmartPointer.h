//
// Created by Grisha on 19.09.2021.
//

#ifndef BASE_CLASSES_MYSMARTPOINTER_H
#define BASE_CLASSES_MYSMARTPOINTER_H

#include "iostream"

//TODO доделать копирование, не выделяется память через new (мб просто ошибка синтаксиса)

template<typename T>
class mySmartPointer {
    T* pointer = nullptr;
    size_t* usage = nullptr;

    void deletePointer() {
        if (*usage == 1) {
            delete pointer;
            delete usage;
        }
        (*usage)--;
    }
public:
    struct nullPtrObj: std::exception {

    };

    mySmartPointer(): usage(new size_t(1)) {}

    explicit mySmartPointer(T* pointer): pointer(pointer), usage(new size_t(1)) {}

    template<typename U>
    explicit mySmartPointer(U* ptr) {
        while (true) {
            try {
                usage = new size_t;
                break;
            }
            catch (std::exception& ba) {
                std::cerr << ba.what() << std::endl;
            }

        }
        (*usage) = 1;
    }

    mySmartPointer(const mySmartPointer<T>& other) {
        pointer = other.pointer;
        usage = other.usage;
        (*usage)++;
    }

    ~mySmartPointer() {
        deletePointer();
    }

    mySmartPointer<T>& operator = (const mySmartPointer<T>& other) {
        deletePointer();

        pointer = other.pointer;
        usage = other.usage;
        (*usage)++;

        return *this;
    }

    mySmartPointer<T>& operator = (T* ptr) {
        deletePointer();

        pointer = ptr;
        usage = new size_t(1);

        return *this;
    }

    T& operator * () {
        if (!pointer)
            throw nullPtrObj();
        return *pointer;
    }

    T* operator->() {
        return pointer;
    }
};


#endif //BASE_CLASSES_MYSMARTPOINTER_H
