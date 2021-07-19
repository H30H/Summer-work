//
// Created by Grisha on 17.07.2021.
//

#ifndef BASE_CLASSES_MYBINARYTREE_H
#define BASE_CLASSES_MYBINARYTREE_H

#include "random"

template<typename T>
class myBinaryTree {
private:
    static bool isLessPrivate(const T& item1, const T& item2) {
        return item1 < item2;
    }

    static bool isSamePrivate(const T& item1, const T& item2) {
        return item1 == item2;
    }

    class Node {
    public:
        T item;

        Node* left = nullptr;
        Node* right = nullptr;

        explicit Node(T item): item(item) {}

        explicit Node(T item, Node* leftNode, Node* rightNode): item(item), left(leftNode), right(rightNode) {}

        static bool operator < (const Node* node1, const Node* node2) {
            if (node1 == nullptr || node2 == nullptr)
                return false;
            return isLess(node1->item, node2->item);
        }

        static bool operator < (const Node* node, const T& item) {
            if (node == nullptr)
                return false;
            return isLess(node->item, item);
        }

        static bool operator == (const Node* node1, const Node* node2) {
            if ((void*)node1 == (void*)node2)
                return thue;
            if (node1 == nullptr || node2 == nullptr)
                return false;
            return isSame(node1->item, node2->item);
        }

        static bool operator == (const Node* node, const T& item) {
            if (node == nullptr)
                return false;
            return isSame(node->item, item);
        }
    };

    bool (*isLess)(const T& item1, const T& item2) = isLessPrivate;
    bool (*isSame)(const T& item1, const T& item2) = isSamePrivate;

    Node* head = nullptr;

    Node* findPrivate(const T& item) const override {
        Node* res = head;
        while (res) {
            if (res == item)
                return res;

            if (res < item) {
                res = res->left;
            }
            else {
                res = res->right;
            }
        }
        return nullptr;
    }
public:
    class objNotItTree{};

    myBinaryTree(): isLess(isLessPrivate), isSame(isSamePrivate) {}

    explicit myBinaryTree(T item): isLess(isLessPrivate), isSame(isSamePrivate), head(new Node(item)) {}

    explicit myBinaryTree(bool (*isLessFunc)(const T& item1, const T& item2)): isLess(isLessFunc), isSame(isSamePrivate) {}

    explicit myBinaryTree(bool (*isLessFunc)(const T& item1, const T& item2),
                          bool (*isSameFunc)(const T& item1, const T& item2)): isLess(isLessFunc), isSame(isSameFunc) {}

    explicit myBinaryTree(T item, bool (*isLessFunc)(const T& item1, const T& item2),
                          bool (*isSameFunc)(const T& item1, const T& item2)): isLess(isLessFunc), isSame(isSameFunc) {}

    //TODO сделать конструктор через define

    void insert(T item) override {
        Node* node= head;
        while (node) {
            if (node == item)
                return;

            if (node < item)
                node = node->left;
            else
                node = node->right;
        }
    }

    void insert(T* arr, size_t size) override {
        for (int i = 0; i < size; i++) {
            insert(arr[i]);
        }
    }

    bool find(const T& item) const override {
        return findPrivate(item) != nullptr;
    }

    T get(const T& item) const override {
        Node* res = findPrivate(item);
        if (res == nullptr)
            throw objNotItTree();

        return res->item;
    }

    void remove(const T& item) override {
        Node* prev = nullptr;
        Node* start = head;
        while(start) {
            if (start == item)
                break;
            prev = start;
            if (start < item)
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
};


#endif //BASE_CLASSES_MYBINARYTREE_H
