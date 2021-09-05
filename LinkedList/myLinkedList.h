//
// Created by Grisha on 24.07.2021.
//

#ifndef BASE_CLASSES_MYLINKEDLIST_H
#define BASE_CLASSES_MYLINKEDLIST_H

#include "cstring"
#include "iostream"

namespace LinkedListPrivateFunc {
    template<typename T>
    bool isSamePrivate(const T& obj1, const T& obj2) {
        return obj1 == obj2;
    }
}

template<typename T>
class myLinkedList {
private:
    class element {
    public:
        T item;
        element* next;
        element *prev;

        explicit element(const T& item): item(item), next(nullptr) {}

        explicit element(const T& item, element* prev, element* next): item(item), prev(prev), next(next) {}

        element(const element& element1) {
            item(element1.item);
            next(element1.next);
        }
    };

    element* head = nullptr;
    element* ending = nullptr;
    size_t size = 0;

    bool (*isSame)(const T& obj1, const T& obj2);

    element* getLastPrivate() {
        return ending;
    }
public:
    class IndexOutOfRange {};

    class iterator {
    private:
        element* item;
        myLinkedList<T>* list;
        bool (*isSame)(const T& obj1, const T& obj2);
    public:
        explicit iterator(element* elem, myLinkedList<T>* list, bool (*isSameFunc)(const T&, const T&) = LinkedListPrivateFunc::isSamePrivate): item(elem), isSame(isSameFunc) {}

        iterator(const iterator& other): item(other.item), list(other.list), isSame(other.isSame) {}

        iterator& operator = (const iterator& other) {
            item(other.item);
            list(other.list);
            isSame(other.isSame);
            return *this;
        }

        T& operator*() const {
            return item->item;
        }

        T* operator->() const {
            return &item->item;
        }

        bool operator == (const iterator& other) const {
            if (item == nullptr && other.item == nullptr)
                return true;

            if (item == nullptr || other.item == nullptr)
                return false;

            return item == other.item && isSame == other.isSame && list == other.list;
        }

        bool operator != (const iterator& other) const {
            return !operator==(other);
        }

        iterator& operator++() const {
            if (item != nullptr)
                item = item->next;
            return *this;
        }

        iterator& operator--() const {
            if (item->prev != nullptr)
                item = item->prev;
            return *this;
        }

        iterator operator++(int) const {
            if (item == nullptr)
                return iterator(nullptr, list, isSame);

            element* res = item;
            item = item->next;
            return iterator(res, list, isSame);
        }

        iterator operator--(int) const {
            if (item == nullptr)
                return iterator(list->ending, list, isSame);

            element* res = item;
            if (item->prev != nullptr)
                item = item->prev;
            return iterator(res, list, isSame);
        }
    };

    explicit myLinkedList(bool (*isSameFunc)(const T&, const T&) = LinkedListPrivateFunc::isSamePrivate): isSame(isSameFunc) {}

    explicit myLinkedList(const T& item, bool (*isSameFunc)(const T&, const T&) = LinkedListPrivateFunc::isSamePrivate): isSame(isSameFunc) {
        head = new element(item);
        ending = head;
        size = 1;
    }

    explicit myLinkedList(T arr[], bool (*isSameFunc)(const T&, const T&) = LinkedListPrivateFunc::isSamePrivate): isSame(isSameFunc) {
        for (auto &i : arr) {
            append(i);
        }
    }

    myLinkedList(std::initializer_list<T> list,
                 bool (*isSameFunc)(const T&, const T&) = LinkedListPrivateFunc::isSamePrivate): isSame(isSameFunc) {
        for (auto &i : list) {
            append(i);
        }
    }

    explicit myLinkedList(T* items, size_t size,
                          bool (*isSameFunc)(const T&, const T&) = LinkedListPrivateFunc::isSamePrivate): isSame(isSameFunc) {
        for (size_t i = 0; i < size; i++) {
            append(items[i]);
        }
    }

    myLinkedList<T>& operator = (const myLinkedList<T>& linkedList) {
        clear();
        for (auto i : linkedList) {
            append(i);
        }

        return *this;
    }

    myLinkedList(const myLinkedList<T>& list) {
        for (auto &i : list) {
            append(i);
        }
    }

    ~myLinkedList() {
        element* elem = head;
        element* buf;
        while(elem) {
            buf = elem->next;
            delete elem;
            elem = buf;
        }
    }

    void append(const T& item) {
        if (ending == nullptr) {
            head = new element(item);
            ending = head;
            size = 1;
            return;
        }

        auto* elem = new element(item);
        ending->next = elem;
        ending = elem;
        size++;
    }

    void prepend(const T& item) {
        if (head == nullptr) {
            head = new element(item);
            ending = head;
            size = 1;
            return;
        }

        auto* elem = new element(item);
        elem->next = head;
        head = elem;
        size++;
    }

    void insert(const T& item, size_t index) {
        if (index >= size)
            throw IndexOutOfRange();

        if (index == 0)
            prepend(item);

        if (index == size - 1)
            append(item);

        element* prev = head;
        for (size_t i = 1; i < index; i++, prev = prev->next);

        prev->next = new element(item, prev->next);
        size++;
    }

    void set(const T& item, size_t index) {
        if (index >= size)
            throw IndexOutOfRange();

        element* elem = head;
        for (size_t i = 0; i < index; i++, elem = elem->next);

        elem->item(item);
    }

    T& get(size_t index) {
        if (index >= size)
            throw IndexOutOfRange();

        if (index == size - 1)
            return ending->item;

        element* elem = head;
        for (size_t i = 0; i < index; i++, elem = elem->next);

        return elem->item;
    }

    const T& get(size_t index) const {
        if (index >= size)
            throw IndexOutOfRange();

        if (index == size - 1)
            return ending->item;

        element* elem = head;
        for (size_t i = 0; i < index; i++, elem = elem->next);

        return elem->item;
    }

    T& pop() {
        return pop(size - 1);
    }

    T& pop(size_t index) {
        if (index >= size)
            throw IndexOutOfRange();
        size--;
        element* elem = head;
        element* prev = nullptr;
        for (size_t i = 0; i < index; i++, prev = elem, elem = elem->next);

        auto *res = new T(elem->item);

        if (prev == nullptr) {
            head = elem->next;
            delete elem;
            if (size == 0)
                ending = nullptr;
            return *res;
        }

        if (elem == ending) {
            ending = prev;
            delete elem;
            prev->next = nullptr;
            return *res;
        }

        prev->next = elem->next;
        delete elem;

        return *res;
    }

    T& operator [] (size_t index) {
        return get(index);
    }

    const T& operator [] (size_t index) const {
        return get(index);
    }

    void swap(size_t index1, size_t index2) {
        if (index1 >= size || index2 >= size)
            throw IndexOutOfRange();

        if (index1 == index2)
            return;

        if (index1 > index2) {
            size_t t = index1;
            index1 = index2;
            index2 = t;
        }

        size_t i = 0;
        element* first = head;
        for (i; i < index1; i++, first = first->next);

        element* second = first;
        for (i; i < index2; i++, second = second->next);

        auto* buf = first->prev;
        first->prev = second->prev;
        second->prev = buf;

        buf = first->next;
        first->next = second->next;
        second->next = buf;
    }

    void clear() {
        element* next;
        while (head) {
            next = head->next;
            delete head;
            head = next;
        }
        head = nullptr;
        ending = nullptr;
        size = 0;
    }

    void reverse() {
        auto* start = head;
        auto* buf = head;

        for (size_t i = 0; i < size; i++) {
            buf = start->next;
            start->next = start->prev;
            start->prev = buf;
        }

        buf = head;
        head = ending;
        ending = buf;
    }

    size_t length() const {
        return size;
    }

    iterator begin() const {
        return iterator(head, isSame);
    }

    iterator end() const {
        return iterator(nullptr, isSame);
    }
};

#endif //BASE_CLASSES_MYLINKEDLIST_H
