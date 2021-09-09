//
// Created by Grisha on 02.09.2021.
//
/*
#include <iostream>
using namespace std;

class Device {
public:
    // constructor
    Device() {
        cout << "Device constructor called" << endl;
    }
    // destructor
    ~Device() {
        cout << "Device destructor called" << endl;
    }
};

class Computer: public Device {
public:
    Computer() {
        cout << "Computer constructor called" << endl;
    }
    ~Computer() {
        cout << "Computer destructor called" << endl;
    }
};

class Laptop: public Computer {
public:
    Laptop() {
        cout << "Laptop constructor called" << endl;
    }
    ~Laptop() {
        cout << "Laptop destructor called" << endl;
    }
};

int main() {
    cout << "\tConstructors" << endl;
    Laptop Laptop_instance;
    cout << "\tDestructors" << endl;
    return 0;
}
/**/

#include "iostream"

using namespace std;

class k1 {
public:
    int* arr = nullptr;
    size_t size = 0;
    const int u = 123;

    k1() {
        cout << "k1 constructor " << u << endl;
    }

    k1(int* arr, size_t size): arr(arr), size(size) {
        cout << "k1 constructor" << endl;
    }

    virtual void set(int item, size_t index) {
        if (index >= size)
            return;

        arr[index] = item;
    }

    virtual int get(size_t index) {
        if (index >= size)
            return 0;

        return arr[index];
    }

    void print() {
        cout << "{";
        for (size_t i = 0; i < size; i++) {
            cout << get(i) << ", ";
        }
        cout << "\b\b}" << endl;
    }
};

class k2: public k1 {
public:
    k2() {
        cout << "k2 constructor " << u << endl;
    }

    explicit k2(int* arr, size_t size) {
        this->arr = arr;
        this->size = size;
        cout << "k2 constructor" << endl;
    }

    void set(int item, size_t index) override {
        if (index >= size)
            return;

        arr[size-index] = item;
    }

    int get(size_t index) override {
        if (index >= size)
            return 0;

        return arr[size-index-1];
    }
};

class k3: public k2 {
public:
    k3() {
        cout << "k3 constructor " << u << endl;
    }

    explicit k3(int* arr, size_t size) {
        this->arr = arr;
        this->size = size;
        cout << "k3 constructor" << endl;
    }

    void set(int item, size_t index) final {
        if (index >= size)
            return;

        if (index < size / 2)
            arr[index*2] = item;
        else {
            arr[index-size/2+(index+1)%2] = item;
        }
    }

    int get(size_t index) final {
        if (index >= size)
            return 0;

        if (index < size / 2)
            return arr[index*2];
        else {
            return arr[index-size/2+(index+1)%2];
        }
    }
};

int getGlobal(k1& k, int index) {
    return k.get(index);
}

int main() {
    int a1[] = {0, 1, 2, 3, 4};

    k1 b1(a1, 5);
    k2 b2(a1, 5);
    k3 b3(a1, 5);

    b1.print();
    b2.print();
    b3.print();

    cout << getGlobal(b1, 1) << endl;
    cout << getGlobal(b2, 1) << endl;
    cout << getGlobal(b3, 1) << endl;
}
/**/