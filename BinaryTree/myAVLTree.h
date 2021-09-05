//
// Created by Grisha on 27.08.2021.
//

#ifndef BASE_CLASSES_MYAVLTREE_H
#define BASE_CLASSES_MYAVLTREE_H

#include "myBinaryTree.h"
#include "../LinkedList/myStack.h"
#include "../LinkedList/myQueue.h"
#define strK 5

template<typename T>
class myAVLTree: public myBinaryTree<T> {
protected:
    bool (*isLess)(const T& obj1, const T& obj2);
    bool (*isSame)(const T& obj1, const T& obj2);
private:
    class Node {
    private:
        void turnLeft(Node** head) {
            if (!right)
                return;
            Node* node = right;
            right = node->left;
            if (node->left)
                node->left->parent = this;
            node->left = this;

            node->parent = parent;
            if (parent != nullptr) {
                if (parent->left == this)
                    parent->left = node;
                else
                    parent->right = node;
            }
            else {
                *head = node;
            }

            node->left->parent = node;
            if (node->right)
                node->right->parent = node;

            checkHeight();
            node->checkHeight();
        }

        void turnRight(Node** head) {
            if (!left)
                return;

            Node* node = left;
            left = node->right;
            if (node->right)
                node->right->parent = this;
            node->right = this;

            node->parent = parent;
            if (parent != nullptr) {
                if (parent->left == this)
                    parent->left = node;
                else
                    parent->right = node;
            }
            else {
                *head = node;
            }

            if(node->left)
                node->left->parent = node;
            node->right->parent = node;

            checkHeight();
            node->checkHeight();
        }

        bool (*isSame)(const T& obj1, const T& obj2) = myBinaryTreePrivateFunc::isSamePrivate;
    public:
        T item;
        Node* left;
        Node* right;
        Node* parent;

        long height = 0;

        explicit Node(const T& item): item(item), height(1) {
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }

        explicit Node(const T& item, Node* parent):
                item(item),
                left(nullptr),
                right(nullptr),
                parent(parent),
                height(1) {}

        explicit Node(const T& item, Node* left, Node* right, Node* parent):
                item(item),
                left(left),
                right(right),
                parent(parent) {
            checkHeight();
        }

        Node(const Node& other):
                item(other.item),
                left(other.left),
                right(other.right),
                parent(other.parent),
                height(other.height) {
        }

        long getDelta() {
            if (left == nullptr && right == nullptr)
                return 0;
            if (left == nullptr && right != nullptr)
                return right->height;
            if (left != nullptr && right == nullptr)
                return -left->height;

            return right->height - left->height;
        }

        void checkHeight() {
            if (left == nullptr && right == nullptr)
                height = 1;
            else if (left == nullptr && right != nullptr)
                height = right->height + 1;
            else if (left != nullptr && right == nullptr)
                height = left->height + 1;
            else
                height = std::max(left->height, right->height) + 1;
        }

        void balance(Node** head) {
            auto delta = getDelta();
            if (delta >= -1 && delta <= 1)
                return;

            if (delta == 2) {
                if (right->getDelta() < 0)
                    right->turnRight(head);
                turnLeft(head);
            }
            else {
                if (left->getDelta() > 0)
                    left->turnLeft(head);
                turnRight(head);
            }
        }

        bool operator == (const Node& other) {
            return isSame(item, other.item);
        }

        bool operator == (const T& obj) {
            return isSame(item, obj);
        }
    };

    Node* head;

    std::string getSTR(Node* node, size_t a, size_t k) const {
        if (!node)
            return {};

        std::string res = getSTR(node->left, a + 1, k);

        for (size_t i = 0; i < a; i++) {
            for (size_t j = 0; j < k; j++) {
                res += ' ';
            }
        }

        res += std::to_string(node->item);
        res += '\n';

        res += getSTR(node->right, a + 1, k);

        return res;
    }

    Node* findPrivate(const T& item) const {
        myStack<Node*> stack;
        return findPrivate(item, stack);
    }

    Node* findPrivate(const T& item, myStack<Node*>& stack) const {
        Node* start = head;
        while (start) {
            if (start->operator==(item))
                break;
            stack.add(start);
            if (isLess(item, start->item))
                start = start->left;
            else
                start = start->right;
        }
        return start;
    }

    std::string strLikeList(Node* node, int count, int pol) {
        std::string res;
        for (int i = 0; i < count - (pol != 0) + count - 1; i++)
            res += ' ';

        if (pol == 1)
            res += "├-";
        else if (pol == 2)
            res += "└-";

        if (node == nullptr) {
            res += "nullptr\n";
            return res;
        }
        res += std::to_string(node->item) + '\n';

        res += strLikeList(node->left, count + 1, 1);
        res += strLikeList(node->right, count + 1, 2);
        return res;
    }

    void removeLeft(Node* node) {
        Node* start = node->left;
        if (start->right == nullptr) {
            if (node->right) {
                start->right = node->right;
                start->right->parent = start;
            }

            if (node->parent) {
                start->parent = node->parent;
                if (node->parent->left == node) {
                    node->parent->left = start;
                } else {
                    node->parent->right = start;
                }
            }
            else {
                start->parent = nullptr;
                head = start;
            }

            delete node;
            return;
        }

        myStack<Node*> stack;
        while(start->right) {
            stack.add(start);
            start = start->right;
        }

        if (start->left) {
            start->parent->right = start->left;
            start->left->parent = start->parent;
        }
        else
            start->parent->right = nullptr;

        start->right = node->right;
        start->right->parent = start;
        start->left = node->left;
        start->left->parent = start;

        if (node->parent) {
            start->parent = node->parent;
            if (node->parent->left == node) {
                node->parent->left = start;
            } else {
                node->parent->right = start;
            }
        }
        else {
            start->parent = nullptr;
            head = start;
        }

        delete node;

        balanceStack(stack);
    }

    void removeRight(Node* node) {
        Node *start = node->right;
        if (start->left == nullptr) {
            if (node->left) {
                start->left = node->left;
                start->left->parent = start;
            }

            if (node->parent) {
                start->parent = node->parent;
                if (node->parent->right == node) {
                    node->parent->right = start;
                } else {
                    node->parent->left = start;
                }
            } else {
                start->parent = nullptr;
                head = start;
            }

            delete node;
            return;
        }

        myStack<Node *> stack;
        while (start->left) {
            stack.add(start);
            start = start->left;
        }

        if (start->right) {
            start->parent->left = start->right;
            start->right->parent = start->parent;
        } else
            start->parent->left = nullptr;

        start->left = node->left;
        start->left->parent = start;
        start->right = node->right;
        start->right->parent = start;

        if (node->parent) {
            start->parent = node->parent;
            if (node->parent->right == node) {
                node->parent->right = start;
            } else {
                node->parent->left = start;
            }
        } else {
            start->parent = nullptr;
            head = start;
        }

        delete node;

        balanceStack(stack);
    }

    void balanceStack(myStack<Node*>& stack) {
        while(stack.length()) {
            Node* node = stack.pop();
            node->checkHeight();
            node->balance(&head);
        }
    }
public:
//    using iterator = typename myBinaryTree<T>::iterator;
    class iterator : public myBinaryTree<T>::iterator {
    private:
        Node* item = nullptr;
        bool (*isSame)(const T& item1, const T& item2);
    public:
        explicit iterator(Node* node, bool (*isSame)(const T& item1, const T& item2)): item(node), isSame(isSame) {}

        iterator(const iterator &other): item(other.item), isSame(other.isSame) {}

        iterator& operator = (const iterator &other) {
            item = other.item;
            isSame = other.isSame;
            return *this;
        }

        T& operator*() const override {
            return item->item;
        }

        T* operator->() const override {
            return &item->item;
        }

        bool operator==(const iterator &other) const {
            if (item == nullptr && other.item == nullptr)
                return true;
            if (item == nullptr || other.item == nullptr)
                return false;
            return isSame(item->item, other.item->item);
        }

        bool operator!=(const iterator &other) const {
            return !operator==(other);
        }

        iterator& operator + (long int num) override {
            if (num < 0)
                return operator-(-num);

            for (int i = 0; i < num; i++) {
                operator++();
            }
            return *this;
        }

        iterator& operator - (long int num) override {
            if (num < 0)
                return operator+(-num);

            for (int i = 0; i < num; i++) {
                operator--();
            }
            return *this;
        }

        iterator& operator++() override {
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

        iterator& operator++(int) override {
            Node* res = item;
            operator++();
            return * (new iterator(res, isSame));
        }

        iterator &operator--() override {
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

        iterator& operator--(int) override {
            Node* res = item;
            operator--();
            return *(new iterator(res, isSame));
        }
    };


    myAVLTree(): head(nullptr), isLess(myBinaryTreePrivateFunc::isLessPrivate), isSame(myBinaryTreePrivateFunc::isSamePrivate) {}

    explicit myAVLTree(bool (*isLess)(const T& obj1, const T& obj2)):
              head(nullptr), isLess(isLess), isSame(myBinaryTreePrivateFunc::isSamePrivate) {}

    explicit myAVLTree(bool (*isLess)(const T& obj1, const T& obj2),
                       bool (*isSame)(const T& obj1, const T& obj2)):
                       head(nullptr), isLess(isLess), isSame(isSame) {}

    explicit myAVLTree(T* arr, size_t size):
            isLess(myBinaryTreePrivateFunc::isLessPrivate), isSame(myBinaryTreePrivateFunc::isSamePrivate) {
        insert(arr, size);
    }

    explicit myAVLTree(T* arr, size_t size, bool (*isLess)(const T& obj1, const T& obj2)):
                       head(nullptr), isLess(isLess), isSame(myBinaryTreePrivateFunc::isSamePrivate) {
        insert(arr, size);
    }

    explicit myAVLTree(T* arr, size_t size, bool (*isLess)(const T& obj1, const T& obj2),
                       bool (*isSame)(const T& obj1, const T& obj2)):
                       head(nullptr), isLess(isLess), isSame(isSame){
        insert(arr, size);
    }

    myAVLTree(const std::initializer_list<T>& list): head(nullptr),
                                              isLess(myBinaryTreePrivateFunc::isLessPrivate),
                                              isSame(myBinaryTreePrivateFunc::isSamePrivate) {
        for (auto &i : list) {
            insert(i);
        }
    }

    myAVLTree(const myAVLTree<T>& tree): head(nullptr), isLess(tree.isLess), isSame(tree.isSame) {
        myQueue<Node*> queue(tree.head);
        while(queue.length()) {
            Node* node = queue.pop();
            if (!node)
                continue;
            insert(node->item);
            queue.add(node->left);
            queue.add(node->right);
        }
    }

    explicit myAVLTree(const myBinaryTree<T>& tree): head(nullptr), isLess(tree.getLessFunc()), isSame(tree.getSameFunc()) {
        for (auto i : tree) {
            insert(i);
        }
    }

    ~myAVLTree() {
        myQueue<Node*> queue(head);
        while (queue.length()) {
            Node* node = queue.pop();
            if (!node)
                continue;
            queue.add(node->left);
            queue.add(node->right);
            delete node;
        }
    }

    void insert(const T& item) override {
        if (head == nullptr) {
            head = new Node(item);
            return;
        }

        myStack<Node*> stack;
        Node* start = head;
        Node* prev = nullptr;
        while (start != nullptr) {
            if (start->operator==(item)) {
                return;
            }
            prev = start;
            stack.add(prev);
            if (isLess(item, start->item)) {
                start = start->left;
            }
            else {
                start = start->right;
            }
        }

        if (isLess(item, prev->item)) {
            prev->left = new Node(item, prev);
        }
        else {
            prev->right = new Node(item, prev);
        }
        prev->checkHeight();

        balanceStack(stack);
    }

    void insert(T* arr, size_t size) override {
        for (size_t i = 0; i < size; i++)
            insert(arr[i]);
    }

    iterator& find(const T& item) const override {
        return *(new iterator(findPrivate(item), isSame));
    }

    bool inTree(const T& item) const override {
        return findPrivate(item) != nullptr;
    }

    void remove(const T& item) override {
        myStack<Node*> stack;
        Node* node = findPrivate(item, stack);
        if (!node)
            return;

        if (node->left == nullptr && node->right == nullptr) {
            if (node != head) {
                if (node->parent->left == node)
                    node->parent->left = nullptr;
                else
                    node->parent->right = nullptr;
            }
            else {
                head = nullptr;
            }
            delete node;
            balanceStack(stack);
            return;
        }

        if (node->left == nullptr && node->right != nullptr) {
            if (node != head) {
                if (node->parent->left == node)
                    node->parent->left = node->right;
                else
                    node->parent->right = node->right;

                node->right->parent = node->parent;
            }
            else {
                head = node->right;
                head->parent = nullptr;
            }
            delete node;
            balanceStack(stack);
            return;
        }

        if (node->left != nullptr && node->right == nullptr) {
            if (node != head) {
                if (node->parent->left == node)
                    node->parent->left = node->left;
                else
                    node->parent->right = node->left;

                node->left->parent = node->parent;
            }
            else {
                head = node->left;
                head->parent = nullptr;
            }
            delete node;
            balanceStack(stack);
            return;
        }

        auto delta = node->getDelta();

        if (delta > 0)
            removeRight(node);
        else
            removeLeft(node);

        balanceStack(stack);
    }

    iterator& begin() const override {
        if (!head)
            return end();
        Node* start = head;
        while(start->left)
            start = start->left;
        return *(new iterator(start, isSame));
    }

    iterator& end() const override {
        return *(new iterator(nullptr, isSame));
    }

    typeof(isLess) getLessFunc() const {
        return isLess;
    }

    typeof(isSame) getSameFunc() const {
        return isSame;
    }

    std::string strLikeList(int count, int pol) {  //вывод дерева в виде списка с аргументами (красивый вывод)
        return strLikeList(head, count, pol);
    }

    std::string getSTR() const {
        return getSTR(0);
    }

    std::string getSTR(size_t a) const {
        return getSTR(a, strK);
    }

    std::string getSTR(size_t a, size_t k) const {
        return getSTR(head, a, k);
    }
};

template<typename T>
std::ostream& operator << (std::ostream& cout, const myAVLTree<T>& tree) {
    return cout << tree.getSTR();
}

#endif //BASE_CLASSES_MYAVLTREE_H
