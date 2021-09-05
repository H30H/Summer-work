//
// Created by Grisha on 17.07.2021.
//

#ifndef BASE_CLASSES_MYBINARYTREE_H
#define BASE_CLASSES_MYBINARYTREE_H

#include "random"
#include "../LinkedList/myQueue.h"

namespace myBinaryTreePrivateFunc{
    template<typename T>
    bool isLessPrivate(const T& item1, const T& item2) {
        return item1 < item2;
    }

    template<typename T>
    bool isSamePrivate(const T& item1, const T& item2) {
        return item1 == item2;
    }
}

template<typename T>
class myBinaryTree {
protected:
    bool (*isLess)(const T& item1, const T& item2);
    bool (*isSame)(const T& item1, const T& item2);

    class Node {
    public:
        T item;

        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;

        explicit Node(const T& item): item(item) {}

        explicit Node(const T& item, Node* leftNode, Node* rightNode, Node* parentNode):
                item(item), left(leftNode), right(rightNode), parent(parentNode) {}

        Node(const Node& other): item(other.item), left(other.left), right(other.right), parent(other.parent) {}
    };
private:

    Node* head = nullptr;

    Node* findPrivate(const T& item) const {
        Node* res = head;
        while (res) {
            if (isSame(item, res->item))
                return res;

            if (isLess(item, res->item)) {
                res = res->left;
            }
            else {
                res = res->right;
            }
        }
        return nullptr;
    }
public:
    using stdIterator = std::iterator<std::bidirectional_iterator_tag, T>;

    class iterator : public stdIterator {
    private:
        Node* item = nullptr;
        bool (*isSame)(const T& item1, const T& item2);
    public:
        iterator(): item(nullptr), isSame(myBinaryTreePrivateFunc::isSamePrivate) {}

        explicit iterator(Node* node, bool (*isSame)(const T& item1, const T& item2)): item(node), isSame(isSame) {}

        iterator(const iterator &other): item(other.item), isSame(other.isSame) {}

        iterator& operator = (const iterator &other) {
            item = other.item;
            isSame = other.isSame;
            return *this;
        }

        virtual T& operator*() const {
            return item->item;
        }

        virtual T* operator->() const {
            return &item->item;
        }

        virtual bool operator==(const iterator &other) const {
            if (item == nullptr && other.item == nullptr)
                return true;
            if (item == nullptr || other.item == nullptr)
                return false;
            return isSame(item->item, other.item->item);
        }

        virtual bool operator!=(const iterator &other) const {
            return !operator==(other);
        }

        virtual iterator& operator + (long int num) {
            if (num < 0)
                return operator-(-num);

            for (int i = 0; i < num; i++) {
                operator++();
            }
            return *this;
        }

        virtual iterator& operator - (long int num) {
            if (num < 0)
                return operator+(-num);

            for (int i = 0; i < num; i++) {
                operator--();
            }
            return *this;
        }

        virtual iterator& operator++() {
            if (!item)
                return *this;

            if (item->right) {
                item = item->right;

                while(item->left)
                    item = item->left;

                return *this;
            }

            Node* next = item->parent;
            while (next && next->right == item) {
                item = next;
                next = next->parent;
            }

            item = next;

            return *this;
        }

        virtual iterator& operator++(int) {
            Node* res = item;
            operator++();
            return * (new iterator(res, isSame));
        }

        virtual iterator &operator--() {
            if (!item)
                return *this;

            if (item->left) {
                item = item->left;

                while(item->right)
                    item = item->right;

                return *this;
            }

            Node* next = item->parent;
            while (next && next->left == item) {
                item = next;
                next = next->parent;
            }

            if (next != nullptr)
                item = next;

            return *this;
        }

        virtual iterator& operator--(int) {
            Node* res = item;
            operator--();
            return *(new iterator(res, isSame));
        }
    };

    explicit myBinaryTree() {
        isLess = myBinaryTreePrivateFunc::isLessPrivate;
        isSame = myBinaryTreePrivateFunc::isSamePrivate;
    }

    explicit myBinaryTree(bool (*isLessFunc)(const T&, const T&)):
                          isLess(isLessFunc),
                          isSame(myBinaryTreePrivateFunc::isSamePrivate) {}

    explicit myBinaryTree(bool (*isLessFunc)(const T&, const T&),
                          bool (*isSameFunc)(const T&, const T&)):
                          isLess(isLessFunc), isSame(isSameFunc) {}

    explicit myBinaryTree(const T& item):
                          isLess(myBinaryTreePrivateFunc::isLessPrivate),
                          isSame(myBinaryTreePrivateFunc::isSamePrivate),
                          head(new Node(item, isSame)) {}

    explicit myBinaryTree(const T& item,
                          bool (*isLessFunc)(const T&, const T&)):
                          isLess(isLessFunc),
                          isSame(myBinaryTreePrivateFunc::isSamePrivate),
                          head(new Node(item, isSame)) {}

    explicit myBinaryTree(const T& item, bool (*isLessFunc)(const T&, const T&),
                          bool (*isSameFunc)(const T&, const T&)):
                          isLess(isLessFunc), isSame(isSameFunc), head(new Node(item, isSame)) {
    }

    explicit myBinaryTree(T *items, size_t size):
                          isLess(myBinaryTreePrivateFunc::isLessPrivate),
                          isSame(myBinaryTreePrivateFunc::isSamePrivate) {
        insert(items, size);
    }

    explicit myBinaryTree(T *items, size_t size, bool (*isLessFunc)(const T&, const T&)):
                          isLess(isLessFunc), isSame(myBinaryTreePrivateFunc::isSamePrivate) {
        insert(items, size);
    }

    explicit myBinaryTree(T *items, size_t size, bool (*isLessFunc)(const T&, const T&),
                          bool (*isSameFunc)(const T&, const T&)):
                          isLess(isLessFunc), isSame(isSameFunc) {
        insert(items, size);
    }

    myBinaryTree(const std::initializer_list<T>& list, bool (*isLessFunc)(const T&, const T&) = myBinaryTreePrivateFunc::isLessPrivate,
                 bool (*isSameFunc)(const T&, const T&) = myBinaryTreePrivateFunc::isSamePrivate):
                          isLess(isLessFunc), isSame(isSameFunc){
        if (!isLess)
            isLess = myBinaryTreePrivateFunc::isLessPrivate;

        if (!isSame)
            isSame = myBinaryTreePrivateFunc::isSamePrivate;

        for (auto i : list) {
            insert(i);
        }
    }

    template<typename iterator>
    explicit myBinaryTree(iterator begin, iterator end, bool (*isLessFunc)(const T&, const T&) = myBinaryTreePrivateFunc::isLessPrivate,
                          bool (*isSameFunc)(const T&, const T&) = myBinaryTreePrivateFunc::isSamePrivate):
                          isLess(isLessFunc), isSame(isSameFunc){
        if (!isLessFunc)
            isLess(myBinaryTreePrivateFunc::isLessPrivate);

        if (!isSameFunc)
            isSame(myBinaryTreePrivateFunc::isSamePrivate);

        for (auto i = begin; i != end; i++) {
            insert(*i);
        }
    }

    myBinaryTree(const myBinaryTree<T>& tree) {
        isSame = tree.isSame;
        isLess = tree.isLess;

        if (tree->head == nullptr)
            return;

        myQueue<Node*> queue(tree->head);

        while(queue.length()) {
            Node* elem = queue.pop();
            if (elem == nullptr)
                continue;

            insert(elem->item);
            queue.add(elem->left);
            queue.add(elem->right);
        }
    }

    ~myBinaryTree() {
        myQueue<Node*> queue(head);
        while(queue.length()) {
            Node* node = queue.pop();
            if (!node)
                continue;
            queue.add(node->left);
            queue.add(node->right);
            delete node;
        }
    }

    virtual void insert(const T& item) {
        if (!head) {
            head = new Node(item);
            return;
        }

        Node* node = head;
        Node* prev = nullptr;
        while (node) {
            prev = node;
            if (isLess(item, node->item))
                node = node->left;
            else
                node = node->right;
        }

        node = new Node(item);
        node->parent = prev;
        if (isLess(item, prev->item))
            prev->left = node;
        else
            prev->right = node;
    }

    virtual void insert(T* arr, size_t size) {
        for (int i = 0; i < size; i++) {
            insert(arr[i]);
        }
    }

    virtual iterator& find(const T& item) const {
        return * (new iterator(findPrivate(item), isSame));
    }

    virtual bool inTree(const T& item) const {
        return findPrivate(item) != nullptr;
    }

    virtual void remove(const T& item) {
        Node* prev = nullptr;
        Node* start = head;
        while(start) {
            if (isSame(start->item, item))
                break;
            prev = start;
            if (isLess(start->item, item))
                start = start->left;
            else
                start = start->right;
        }
        if (start == nullptr)
            return;

        if (!start->left || !start->right) { //если одна подветвь пустая
            Node* changeTo;
            if (!start->left && !start->right) { //обе пустые
                changeTo = nullptr;
            }
            else if (!start->left) {         //левая пустая
                changeTo = start->right;
            }
            else {                           //правая пустая
                changeTo = start->left;
            }

            if (prev) {
                if (prev->left == start)
                    prev->left = changeTo;
                else
                    prev->right = changeTo;
            }
            else {
                head == changeTo;
            }
            delete start;
            return;
        }

        Node* from = start->left;
        Node* fromPrev = nullptr;

        while(from->right) {
            fromPrev = from;
            from = from->right;
        }

        if (!fromPrev)
            start->left = from->left;
        else
            fromPrev->right = from->left;

        from->left = start->left;
        from->right = start->right;

        if (prev) {
            if (prev->left == start)
                prev->left = from;
            else
                prev->right = from;
        }
        else {
            head = from;
        }
        delete start;
    }

    virtual iterator& begin() const {
        if (!head) {
            return end();
        }

        Node* leftNode = head;

        while(leftNode->left)
            leftNode = leftNode->left;

        return * (new iterator(leftNode, isSame));
    }

    virtual iterator& end() const {
        return * (new iterator(nullptr, isSame));
    }

    virtual typeof(isLess) getLessFunc() const {
        return isLess;
    }

    virtual typeof(isSame) getSameFunc() const {
        return isSame;
    }
};

#endif //BASE_CLASSES_MYBINARYTREE_H
