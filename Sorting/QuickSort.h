//
// Created by Grisha on 21.08.2021.
//

#ifndef BASE_CLASSES_QUICKSORT_H
#define BASE_CLASSES_QUICKSORT_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"
#include "../LinkedList/myQueue.h"
#include "random"

namespace sortFuncPrivate {
    size_t randomIndex(size_t start, size_t end) {
        if (start == end)
            return start;

        if (start > end) {
            size_t i = start;
            start = end;
            end = i;
        }

        return random()%(end - start) + start;
    }

    template<typename T>
    mySequence<T>& SortInterval(mySequence<T>& sequence, size_t start, size_t end, size_t& index,
                                bool (*cmp)(const T& obj1, const T& obj2)) {
        size_t left = start, right = end - 1;
        size_t index1 = index;
        bool state = false;   /// == true -> левый больше чем тот, относительно которого идёт сравнение
        while (left < right) {
            if (left == index) {
                left++;
                continue;
            }
            if (right == index) {
                right--;
                continue;
            }

            if (state) {
                if (cmp(sequence[right], sequence[index])) {
                    state = false;
                    sequence.swap(left, right);
                    left++;
                    right--;
                }
                else {
                    right--;
                }
            }
            else {
                if (cmp(sequence[index], sequence[left])) {
                    state = true;
                }
                else {
                    left++;
                }
            }
        }
        size_t swapIndex;
        if (state) {
            if (index < left)
                if (left == start)
                    swapIndex = left;
                else
                    swapIndex = left - 1;
            else
                swapIndex = left;
        }
        else {
            if (left == right) {
                if (left == index)
                    swapIndex = left;
                else if (cmp(sequence[index], sequence[left])) {
                    if (index < left) {
                        swapIndex = left - 1;
                    }
                    else {
                        swapIndex = left;
                    }
                }
                else {
                    if (index < left)
                        swapIndex = left;
                    else
                        swapIndex = left + 1;
                }
            }
            else {  //left > right
                if (index < right) {
                    swapIndex = right;
                }
                else
                    swapIndex = left;
            }
        }

        sequence.swap(index, swapIndex);
        index = swapIndex;
        return sequence;
    }
}

template<typename T>
mySequence<T>* QuickSort(const mySequence<T>& sequence, size_t from, size_t to, bool (*cmp)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return sequence.copy();
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
    
    mySequence<T>* resSequence = sequence.copy();

    while (queue.length() > 0) {
        auto inter = queue.pop();
        if (inter.start + 1 >= inter.end)
            continue;
        size_t index = sortFuncPrivate::randomIndex(inter.start, inter.end);
        sortFuncPrivate::SortInterval(*resSequence, inter.start, inter.end, index, cmp);
        queue.add(interval(inter.start, index));
        queue.add(interval(index + 1, inter.end));
    }
    return resSequence;
}

template<typename T>
mySequence<T>* QuickSort(const mySequence<T>& sequence, size_t from, size_t to) {
    return QuickSort(sequence, from, to, sortFuncPrivate::isLessDefault);
}

template<typename T>
mySequence<T>* QuickSort(const mySequence<T>& sequence, bool (*cmp)(const T& obj1, const T& obj2)) {
    return QuickSort(sequence, 0, sequence.length(), cmp);
}

template<typename T>
mySequence<T>* QuickSort(const mySequence<T>& sequence) {
    return QuickSort(sequence, 0, sequence.length(), sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_QUICKSORT_H
