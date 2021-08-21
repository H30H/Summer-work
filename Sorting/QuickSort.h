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
                                bool (*isLess)(const T& obj1, const T& obj2)) {
        size_t left = start, right = end - 1;
        size_t index1 = index;
        bool state = false;   /// == true -> левый больше чем исходный
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
                if (isLess(sequence[right], sequence[index])) {
                    state = false;
//                    std::cout << "\tswap: " << left << ", " << right << std::endl;
                    sequence.swap(left, right);
                    left++;
                    right--;
                }
                else {
                    right--;
                }
            }
            else {
                if (isLess(sequence[index], sequence[left])) {
                    state = true;
                }
                else {
                    left++;
                }
            }
        }
//        std::cout << "\tend: " << left << ", " << right << ", " << state << std::endl;
//        std::cout << " {" << start << ", " << end << "}, {" << index << ", " << index1 << "}: " << sequence << std::endl;
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
                else if (isLess(sequence[index], sequence[left])) {
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
        /*if (state) {
            if (index != left + 1) {
                T item = sequence[index];
                sequence.insert(item, left);
                if (index < left + 1) {
                    sequence.pop(index);
                }
                else {
                    sequence.pop(index + 1);
                }
                index = left;
            }
        }
        else {
            size_t place;
            if (left == right) {
                if (isLess(sequence[index], sequence[left])) {
                    place = left;
                }
                else {
                    place = left + 1;
                }
            }
            else {
                place = left;
            }

            if (place == sequence.length()) {
                T item = sequence[index];
                sequence.append(item);
                sequence.pop(index);
                index = place - 1;
            }
            else if (index != place) {
                T item = sequence[index];
                sequence.insert(item, place);
                if (index < place)
                    sequence.pop(index);
                else
                    sequence.pop(index + 1);
                if (place == end)
                    place--;
                index = place;
            }
        }*/
//        std::cout << " {" << start << ", " << end << "}, {" << index << ", " << index1 << "}: " << sequence << std::endl << std::endl;
        return sequence;
    }
}

template<typename T>
mySequence<T>& QuickSort(mySequence<T>& sequence, bool (*isLess)(const T& obj1, const T& obj2)) {
    struct interval {
        size_t start;
        size_t end;

        interval(size_t start, size_t end): start(start), end(end) {}

        interval(const interval& other): start(other.start), end(other.end) {}

        bool operator == (const interval& other) const {
            return start == other.start && end == other.end;
        }
    };
//    std::cout << "Quick start: " << sequence << std::endl;

    myQueue<interval> queue(interval(0, sequence.length()));

    while (queue.length() > 0) {
        auto inter = queue.pop();
        if (inter.start + 1 >= inter.end)
            continue;
//        std::cout << " interval: " << inter.start << ", " << inter.end << std::endl;
        size_t index = sortFuncPrivate::randomIndex(inter.start, inter.end);
        sortFuncPrivate::SortInterval(sequence, inter.start, inter.end, index, isLess);
        queue.add(interval(inter.start, index));
        queue.add(interval(index + 1, inter.end));
    }
//    std::cout << "Quick end" << std::endl;
    return sequence;
}

template<typename T>
mySequence<T>& QuickSort(mySequence<T>& sequence) {
    return QuickSort(sequence, sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_QUICKSORT_H
