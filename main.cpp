#include <iostream>
#include <tuple>
#include <vector>
#include <iterator>
#include "DynamicArray/myDynamicArray.h"
#include "Sequence/myArraySequence.h"
#include "Sorting/allSorts.h"

template <class...Args>
int sum(Args&&... args) {
    auto arguments = std::make_tuple(std::forward<Args>(args)...);
    int sum = 0;

    for (auto i : arguments) {
        sum += i;
    }
    return sum;
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

    arraySequence.append(7);
    arraySequence.prepend(0);
    arraySequence.insert(2, 2);
    myArraySequence<int> arraySequence1{4, 5, 6};
    cout << arraySequence << ' ' << arraySequence.length() << endl;
    cout << arraySequence.find(4) << ' ' << arraySequence.find(9)
         << ' ' << arraySequence.find(arraySequence1) << ' ' << arraySequence.find(myArraySequence<int>{7, 8, 9}) << endl;
    arraySequence.reverse();
    cout << arraySequence << endl;
    SelectionSortMod(arraySequence);
    cout << arraySequence << endl;

    return 0;
}
