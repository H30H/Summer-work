#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <iterator>
#include "Sequence/myArraySequence.h"
#include "Sorting/BubbleSort.h"
#include "random"
#include "BinaryTree/myBinaryHeap.h"
#include "LinkedList/myLinkedList.h"
#include "BinaryTree/myAVLTree.h"
#include "Map/myMap.h"
#include "Sorting/menu/sortingMenu.h"
#include "Timer/myTimer.h"
#include "Console/myConsole.h"
#include "thread"

bool compare(const int& obj1, const int& obj2) {
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
              mySequence<int>* (*sort)(const mySequence<int>&, bool (*a)(const int&, const int&)), bool (*isLess)(const int&, const int&)) {
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
            auto res = sort(sequence, isLess);
            if (!checkCorrect(*res)) {
                countErr++;
                std::cout << "Error " << countErr<< ": " << *res << std::endl;
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
                std::cout << "First correct: " << *res << "\n               " << sequence << std::endl;
                isCorrectFirst = false;
            }

            delete res;
        }
        catch (typename mySequence<int>::IndexOutOfRange) {
            std::cout << "IndexOutOfRange: " << sequence << std::endl;
        }
    }
    std::cout << "Error count: " << countErr << std::endl;
}

using namespace std;

void u() {

    int u1 = 0;

//    myArraySequence<int> seq123;
//    if ((mySequence<int>*)(&u1))
//        cout << 1 << endl;
//    else
//        cout << 0 << endl;

//    return 0;

    vector<int> v{1, 2, 3, 4, 5};
    vector<int> v1(v.begin(), v.end());

    struct testStruct {
        int a;
        bool b;
        string c;

        testStruct(int a, bool b, string c) : a(a), b(b), c(std::move(c)) {}
    };

    vector<testStruct> vex{testStruct(1, true, "abc"), testStruct(2, false, "true"), testStruct(3, false, "false")};

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

    arraySequence.append(arraySequence.getFirst());
    cout << arraySequence << ' ' << arraySequence.length() << endl;
    myArraySequence<size_t*> sizes;
    for (size_t i = 0; i < 10000; i++) {
        sizes.append(new size_t);
    }

    while (sizes.length()) {
        delete sizes.pop();
    }

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

//    binaryTree.insert(arr, sizeof(arr) / sizeof(int));

//    printTree(binaryTree);

//    myArraySequence<int> sequence(arr, sizeof(arr) / sizeof(int));

    myArraySequence<int> seqTest(arr, sizeof(arr) / sizeof(int));




//    cout << sequence << ' ' << sequence.length() << endl;
//    cout << QuickSort(sequence) << endl << endl;

//    cout <<
//    std::cout << sequence << std::endl;
//    sequence.move(0, 5);
//    std::cout << sequence << std::endl;
//    sequence.move(5, 0);
//    std::cout << sequence << std::endl;

    myArraySequence<size_t> arraySequence1;
    for (size_t i = 10000; i > 0; i--) {
        arraySequence1.append(i);
    }

    myTimer timer;
    BubbleSort(arraySequence1);
//    testSort(10'000, 1, 1000, BubbleSort<int>, sortFuncPrivate::isLessDefault);
    std::cout << "time of sorting 10'000: " << timer.time() << std::endl;


//    int n;
//    cin >> n;
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
}
/*
struct point {
    int x;
    int y;
};

bool copm(const point& p1, const point& p2) {
    return p1.x < p2.x;
}
*/

void bubbleSort(myArraySequence<int>& sequence, size_t from, size_t to) {
    bool changed = true;
    size_t delta = 0;
    while(changed) {
        changed = false;
        for (size_t i = from+1; i < to - delta; i++) {
            if (sequence[i] < sequence[i-1]) {
                changed = true;
                sequence.swap(i, i-1);
            }
        }
        delta++;
    }
}

template<typename T>
void QuickSort2(mySequence<T>& sequence, size_t from, size_t to, bool (*cmp)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return;
    }

    struct interval {
        size_t start;
        size_t end;

        interval(size_t start, size_t end): start(start), end(end) {}

        interval(const interval& other): start(other.start), end(other.end) {}

        bool operator == (const interval& other) const {
            return start == other.start && end == other.end;
        }
    };

    myQueue<interval> queue(interval(from, to));

    while (queue.length() > 0) {
        auto inter = queue.pop();
        if (inter.start + 1 >= inter.end)
            continue;
        size_t index = sortFuncPrivate::randomIndex(inter.start, inter.end);
        sortFuncPrivate::SortInterval(sequence, inter.start, inter.end, index, cmp);
        queue.add(interval(inter.start, index));
        queue.add(interval(index + 1, inter.end));
    }
}

int threads = 0;

void QuickSortThread(mySequence<int>& sequence, size_t from, size_t to, bool (*cmp)(const int& obj1, const int& obj2)) {
    if (to <= from || to - from < 2) {
        return;
    }

    size_t index = sortFuncPrivate::randomIndex(from, to);
    sortFuncPrivate::SortInterval(sequence, from, to, index, cmp);

    if (threads >= thread::hardware_concurrency()) {
        QuickSortThread(sequence, from, index, cmp);
        QuickSortThread(sequence, index, to, cmp);
        return;
    }

    thread t1(QuickSortThread, std::ref(sequence), from, index, cmp);
    thread t2(QuickSortThread, std::ref(sequence), index, to, cmp);
    threads += 2;
    t1.join();
    t2.join();
    threads -= 2;
}

int main() {

//    string skipSymbol;         //при открытии консоли в фулл экран вводиться '\0'... (костыль чтоб не портить вывод меню)
//    getline(cin, skipSymbol, '\0');
//    mySortMenuClass::mainMenu();

    myArraySequence<int> sequence1;
    myArraySequence<int> sequence2;
    for (int i = 0; i < 10000000; i++) {
        sequence1.append(rand());
        sequence2.append(rand());
    }

    myTimer timer;
    QuickSort2(sequence1, 0, sequence1.length(), sortFuncPrivate::isLessDefault);
    auto time1 = timer.time();

    timer.reset();

    QuickSortThread(sequence2, 0, sequence2.length(), sortFuncPrivate::isLessDefault);
    auto time2 = timer.time();

    cout << time1 << ' ' << time2 << endl;
//    u();
    return 0;
}
