#include <iostream>
#include <tuple>
#include <vector>
#include <iterator>
#include "DynamicArray/myDynamicArray.h"
#include "Sequence/myArraySequence.h"
#include "Sorting/allSorts.h"
#include "random"

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

void testSort(size_t length, size_t count, int maxElem) {
    size_t countErr = 0;
    for (size_t i = 0; i < count; i++) {
        myArraySequence<int> sequence;
        for (size_t j = 0; j < length; j++) {
            sequence.append(random()%maxElem);
        }
        auto seq = sequence;
        BatcherSort(sequence);
        if (!checkCorrect(sequence)) {
            countErr++;
            std::cout <<countErr<< ": " << seq << "\n    " << sequence << std::endl;
        }
    }
}

using namespace std;

int main() {
    vector<int> v{1, 2, 3, 4, 5};
    vector<int> v1(v.begin(), v.end());

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

    testSort(18, 100, 100);

    return 0;
}
