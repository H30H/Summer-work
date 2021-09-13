//
// Created by Grisha on 19.07.2021.
//

#ifndef BASE_CLASSES_MYMAP_H
#define BASE_CLASSES_MYMAP_H

#include "../BinaryTree/myAVLTree.h"

template<class K, class T>
class myMap {
protected:
    bool (*isLess)(const K& item1, const K& item2);
    bool (*isSame)(const K& item1, const K& item2);
private:
    class obj {
    public:
        K key;
        T item;
        bool (*isLess)(const K& obj1, const K& obj2);
        bool (*isSame)(const K& obj1, const K& obj2);

        explicit obj(const K& key, bool (*isLess)(const K& obj1, const K& obj2),
                     bool (*isSame)(const K& obj1, const K& obj2)): key(key), isLess(isLess), isSame(isSame) {}

        explicit obj(const K& key, const T& item, bool (*isLess)(const K& obj1, const K& obj2),
                     bool (*isSame)(const K& obj1, const K& obj2)): key(key), item(item), isLess(isLess), isSame(isSame) {}

        bool operator < (const obj& other) const {
            return isLess(key, other.key);
        }

        bool operator == (const obj& other) const {
            return isSame(key, other.key);
        }
    };

    myAVLTree<obj> avlTree;

public:
    class unknownKey {};

    myMap(): isLess(myBinaryTreePrivateFunc::isLessPrivate), isSame(myBinaryTreePrivateFunc::isSamePrivate) {}

    explicit myMap(bool (*isLess)(const K& obj1, const K& obj2)): isLess(isLess), isSame(myBinaryTreePrivateFunc::isSamePrivate) {}

    explicit myMap(bool (*isLess)(const K& obj1, const K& obj2),
                   bool (*isSame)(const K& obj1, const K& obj2)): isLess(isLess), isSame(isSame) {}

    //TODO сделать конструкторы также как и в myBinaryTree

    explicit myMap(const K& key, const T& item): isLess(myBinaryTreePrivateFunc::isLessPrivate), isSame(myBinaryTreePrivateFunc::isSamePrivate) {
        insert(key, item);
    }

    explicit myMap(const K& key, const T& item,
                   bool (*isLess)(const K& obj1, const K& obj2)): isLess(isLess), isSame(myBinaryTreePrivateFunc::isSamePrivate) {
        insert(key, item);
    }

    explicit myMap(const K& key, const T& item,
                   bool (*isLess)(const K& obj1, const K& obj2),
                   bool (*isSame)(const K& obj1, const K& obj2)): isLess(isLess), isSame(isSame) {
        insert(key, item);
    }

    explicit myMap(const K* keyArr, const T* itemArr, size_t size):
                   isLess(myBinaryTreePrivateFunc::isLessPrivate), isSame(myBinaryTreePrivateFunc::isSamePrivate) {
        insert(keyArr, itemArr, size);
    }

    explicit myMap(const K* keyArr, const T* itemArr, size_t size,
                   bool (*isLess)(const K& obj1, const K& obj2)):
                   isLess(isLess), isSame(myBinaryTreePrivateFunc::isSamePrivate) {
        insert(keyArr, itemArr, size);
    }

    explicit myMap(const K* keyArr, const T* itemArr, size_t size,
                   bool (*isLess)(const K& obj1, const K& obj2),
                   bool (*isSame)(const K& obj1, const K& obj2)):
            isLess(isLess), isSame(isSame) {
        insert(keyArr, itemArr, size);
    }

    myMap(std::initializer_list<T> list):
          isLess(myBinaryTreePrivateFunc::isLessPrivate),
          isSame(myBinaryTreePrivateFunc::isSamePrivate) {
        for (auto &i : list) {
            avlTree.insert(i);
        }
    }

    explicit myMap(std::initializer_list<T> list,
                   bool (*isLess)(const T& obj1, const T& obj2)):
                   isLess(isLess), isSame(myBinaryTreePrivateFunc::isSamePrivate) {
        for (auto &i : list) {
            avlTree.insert(i);
        }
    }

    explicit myMap(std::initializer_list<T> list,
                   bool (*isLess)(const T& obj1, const T& obj2),
                   bool (*isSame)(const T& obj1, const T& obj2)):
                   isLess(isLess), isSame(isSame) {
        for (auto &i : list) {
            avlTree.insert(i);
        }
    }
    void insert(K key, T item) {
        avlTree.insert(obj(key, item, isLess, isSame));
    }

    void insert(const K* keyArr, const T* itemArr, size_t size) {
        for (size_t i = 0; i < size; i++) {
            avlTree.insert(obj(keyArr[i], itemArr[i], isLess, isSame));
        }
    }

    typename myAVLTree<obj>::iterator find(const K& key) const {
        return avlTree.find(obj(key, isLess, isSame));
    }

    T get(const K& key) const {
        return operator[](key);
    }

    T& operator [] (const K& key) {
        auto iter = avlTree.find(obj(key, isLess, isSame));
        if (iter == avlTree.end())
            throw unknownKey();

        return iter->item;
    }

    const T& operator [] (const K& key) const {
        auto iter = avlTree.find(key, isLess, isSame);
        if (iter == avlTree.end())
            throw unknownKey();

        return iter->item;
    }

    void remove(const K& key) {
        avlTree.remove(obj(key, isLess, isSame));
    }

    typename myAVLTree<obj>::iterator begin() const {
        return avlTree.begin();
    }

    typename myAVLTree<obj>::iterator end() const {
        return avlTree.end();
    }
};


#endif //BASE_CLASSES_MYMAP_H
