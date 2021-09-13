#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <iterator>
#include "DynamicArray/myDynamicArray.h"
#include "Sequence/myArraySequence.h"
#include "Sorting/allSorts.h"
#include "random"
#include "BinaryTree/myBinaryHeap.h"
#include "LinkedList/myLinkedList.h"
#include "BinaryTree/myAVLTree.h"
#include "Map/myMap.h"
#include "Sorting/menu/sortingMenu.h"

template <class...Args>
int sum(Args&&... args) {
    auto arguments = std::make_tuple(std::forward<Args>(args)...);
    int sum = 0;

    for (auto i : arguments) {
        sum += i;
    }
    return sum;
}

bool sravn(const int& obj1, const int& obj2) {
    return obj1 > obj2;
}

template<typename T>
bool checkCorrect(mySequence<T>& sequence) {
    for (size_t i = 1; i < sequence.length(); i++) {
        if (sequence[i-1] > sequence[i])
            return false;
    }
    return true;
}

void testSort(size_t length, size_t count, int maxElem,
              mySequence<int>& (*sort)(mySequence<int>&, bool (*a)(const int&, const int&)), bool (*isLess)(const int&, const int&)) {
    size_t countErr = 0;
    bool isCorrectFirst = false;
    std::cout << "Test sort: " << std::endl;
    for (size_t i = 1; i <= count; i++) {
        if (i%100 == 0) {
            std::cout << i << std::endl;
        }
        myArraySequence<int> sequence;
        try {
            size_t len = length;
            if (len == -1) {
                len = random()%1025;
            }
            for (size_t j = 0; j < len; j++) {
                sequence.append(random()%maxElem);
            }
            auto seq = sequence;
            sort(sequence, isLess);
            if (!checkCorrect(sequence)) {
                countErr++;
                std::cout << "Error " << countErr<< ": " << seq << std::endl;
                for (size_t k = countErr; k > 0; k/=10) {
                    std::cout << ' ';
                }
                std::cout << "        " << sequence;
                for (int k = 0; k < 20; k++) {
                    std::cout << '-';
                }
                std::cout << std::endl;
            }
            else if (isCorrectFirst) {
                std::cout << "First correct: " << seq << "\n               " << sequence << std::endl;
                isCorrectFirst = false;
            }
        }
        catch (typename mySequence<int>::IndexOutOfRange) {
            std::cout << "IndexOutOfRange: " << sequence << std::endl;
        }
    }
    std::cout << "Error count: " << countErr << std::endl;
}

template<typename T>
void printTree(const myBinaryTree<T>& tree) {
    std::cout << '{';
    for (auto i : tree) {
        std::cout << i << ' ';
    }
    std::cout << "\b\b}" << std::endl;
}

using namespace std;

int main() {
    mySortMenuClass::mainMenu();
    return 0;

    vector<int> v{1, 2, 3, 4, 5};
    vector<int> v1(v.begin(), v.end());

    struct testStruct {
        int a;
        bool b;
        string c;

        testStruct(int a, bool b, string c) : a(a), b(b), c(std::move(c)) {}
    };


    vector<testStruct> vex{testStruct(1, true, "abc"), testStruct(2, false, "true"), testStruct(3, false, "false")};

    int u;
    myDynamicArray<int> dynamicArray(v.begin(), v.end());
    cout << dynamicArray << ' ' << dynamicArray.length() << endl;

    myDynamicArray<int> dynamicArray1(dynamicArray.begin(), dynamicArray.end());
    cout << dynamicArray1 << ' ' << dynamicArray1.length() << endl;

    dynamicArray1.swap(0, 4);
    cout << dynamicArray1 << ' ' << dynamicArray1.length() << endl;

    myDynamicArray<int> dynamicArray2{2, 3, 4, 5, 6};
    cout << dynamicArray2 << ' ' << dynamicArray2.length() << endl;

    int a[]{1, 2, 3, 4, 5};
    myArraySequence<int> arraySequence(dynamicArray2.begin(), dynamicArray2.end());

    cout << arraySequence << ' ' << arraySequence.length() << endl;

//    arraySequence.append(7);
//    arraySequence.prepend(0);
//    arraySequence.insert(2, 2);
//    cout << ' ' << arraySequence << endl;
//    arraySequence.prepend(-1);
//    cout << ' ' << arraySequence << endl;
//    arraySequence.reverse();
//    cout << arraySequence << endl;
//    cout << BatcherSort(arraySequence) << endl;
//    myBinaryHeap<int> heap;
    myBinaryTree<int> binaryTree;
    int arr[] = {92, 49, 21, 62, 27, 90, 59, 63, 26, 40};//{1, 3, 4, 5 ,7, 9, -1, -2, 0, -5, -4};

    binaryTree.insert(arr, sizeof(arr) / sizeof(int));

    printTree(binaryTree);

    myArraySequence<int> sequence(arr, sizeof(arr) / sizeof(int));
//    cout << sequence << ' ' << sequence.length() << endl;
//    cout << QuickSort(sequence) << endl << endl;

//    cout <<
//    std::cout << sequence << std::endl;
//    sequence.move(0, 5);
//    std::cout << sequence << std::endl;
//    sequence.move(5, 0);
//    std::cout << sequence << std::endl;


    testSort(1000, 10000, 1000, InsertSort<int>, sortFuncPrivate::isLessDefault);
    //TODO попробовать написать альтернативу мёрджа через свапы и посмотреть на время работы
    /*
    myAVLTree<int> tree;
    int num = 0, k;
    for (int i = 0; i <= 10; i++) {
        tree.insert(i);
        cout << tree << endl;
    }

    cout << "{";
    for (size_t j = 0; j < 10000; j++) {
        for (auto i: tree) {
            cout << i << ", ";
        }
        cout << "\b\b}\n";
    }

    cout << tree << endl;
    while (num != -1) {
        cin >> num;
        cin >> k;
        if (num == 0) {
            tree.insert(k);
        }
        else {
            tree.remove(k);
        }
        cout << tree << endl;
    }
    /* */

    return 0;
}
