//
// Created by Grisha on 19.09.2021.
//

#ifndef BASE_CLASSES_MYSMARTPOINTER_H
#define BASE_CLASSES_MYSMARTPOINTER_H

#include "iostream"

template<typename T>
class mySmartPointer {
    using uint = unsigned int;

    T* pointer = nullptr;
    uint* usage = nullptr;

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

    mySmartPointer(): usage(new uint(1)) {}

    explicit mySmartPointer(T* pointer): pointer(pointer), usage(new uint(1)) {}

    template<typename U>
    explicit mySmartPointer(U* ptr) {

        while (true) {
            try {
                usage = new uint;
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

    mySmartPointer<T>& operator = (mySmartPointer<T>& other) {
        deletePointer();

        pointer = other.pointer;
        usage = other.usage;
        (*usage)++;

        return *this;
    }

    mySmartPointer<T> operator = (T* ptr) {
        deletePointer();

        pointer = ptr;
        usage = new uint(1);

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
