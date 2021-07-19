//
// Created by Grisha on 19.07.2021.
//

#ifndef BASE_CLASSES_MYMAP_H
#define BASE_CLASSES_MYMAP_H

#include "../BinaryTree/myBinaryTree.h"

template<class K, class T>
class myMap {
private:
    static bool isLessPrivate(const K& item1, const K& item2) {
        return item1 < item2;
    }

    static bool isSamePrivate(const K& item1, const K& item2) {
        return item1 == item2;
    }

    bool (*isLess)(const K& item1, const K& item2);
    bool (*isSame)(const K& item1, const K& item2);

    class obj {
        K key;
        T item;

        explicit obj(K&& key): key(key) {}

        explicit obj(K key, T item): key(key), item(item) {}

        bool operator < (const obj obj1) {
            return isLess(key, obj1.key);
        }

        bool operator == (const obj obj1) {
            return isSame(key, obj1.key);
        }
    };

    myBinaryTree<obj> binaryTree;
public:
    //TODO сделать конструкторы также как и в myBinaryTree

    void insert(K key, T item) {
        binaryTree.insert(obj(key, item));
    }

    void insert(K* keys, T* items, size_t size) {
        for (size_t i = 0; i < size; i++) {
            binaryTree.insert(obj(keys[i], items[i]));
        }
    }

    bool find(const K& key) {
        return binaryTree.find(obj(key));
    }

    T get(const K& key) {
        return binaryTree.get(key).item;
    }
};


#endif //BASE_CLASSES_MYMAP_H
