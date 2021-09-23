//
// Created by Grisha on 22.07.2021.
//

#ifndef BASE_CLASSES_BATCHERSORT_H
#define BASE_CLASSES_BATCHERSORT_H

#include "isLessDefault.h"
#include "../Sequence/mySequence.h"
#include "../Sequence/myArraySequence.h"
#include "../LinkedList/myQueue.h"
#include <cmath>
#include <iostream>

namespace sortFuncPrivate {
    bool checkLog2(size_t num) {
        auto res = log2((double) num);

        return fmod(res, 1) == 0;
    }

    template<typename T>
    void sortBitonicSequence(mySequence<T>& sequence, size_t from, size_t to,
                             bool (*cmp)(const T& obj1, const T& obj2)) {
        if (to <= from || to - from < 2) {
            return;
        }

        struct indexes {
            size_t from;
            size_t to;

            bool operator == (const indexes& other) const {
                return from == other.from && to == other.to;
            }
        };

        myQueue<indexes> queue(indexes{from, to});
        size_t index;
        while (queue.length()) {
            auto interval = queue.pop();

            if (interval.to <= interval.from || interval.to - interval.from < 2) {
                continue;
            }

            index = interval.from + (interval.to - interval.from) / 2;
//            std::cout << "interval: " << interval.from << ", " << index << ", " << interval.to << std::endl;

            for (size_t i = interval.from, j = index; j < interval.to; i++, j++) {
                if (cmp(sequence[j], sequence[i])) {
                    sequence.swap(i, j);
                }
            }

            queue.add(indexes{interval.from, index});
            queue.add(indexes{index, interval.to});
        }
    }

    template<typename T>
    void getBitonicSequence(mySequence<T>& sequence, size_t from, size_t to,
                            bool (*cmp)(const T& obj1, const T& obj2)) {
        if (to <= from || to - from < 2) {
            return;
        }

        for (size_t i = from, j = to - 1; i < j; i++, j--) {
            if (cmp(sequence[j], sequence[i]))
                sequence.swap(i, j);
        }
    }

    template<typename T>
    void mergeSequence(mySequence<T>& sequence, size_t from, size_t to, size_t index,
                       bool (*cmp)(const T& obj1, const T& obj2)) {
        size_t ind1 = from, ind2 = index;
        while(ind1 != index && ind2 != to) {
            if (cmp(sequence[ind2], sequence[ind1])) {
                sequence.move(ind2, ind1);
//                sequence.insert(sequence[ind2], ind1);
//                sequence.pop(ind2+1);
                ind1++;
                ind2++;
                index++;
            }
            else {
                ind1++;
            }
        }
    }
}

template<typename T>
mySequence<T>* BatcherSort(const mySequence<T>& sequence, size_t from, size_t to, bool (*cmp)(const T& obj1, const T& obj2)) {
    if (to <= from || to - from < 2) {
        return sequence.copy();
    }

    size_t size = to - from;

    if (!sortFuncPrivate::checkLog2(size)) { //если размер отрезка не равен степени двойки
        myArraySequence<size_t> indexes(from);
        auto resSequence = sequence.copy(true);
        while (size != 0) {                  //сортировка вложенных отрезков, длиной степени двойки
            auto index = (size_t) pow(2, static_cast<size_t>(log2(size)));
            size -= index;
            index += indexes.getLast();
            auto sorted = BatcherSort(sequence, indexes.getLast(), index, cmp);
            for (size_t i = indexes.getLast(); i < index; i++) {
                resSequence->append(sorted->operator[](i));
            }

            indexes.append(index);
            delete sorted;
        }

        for (size_t i = indexes.length() - 1, j = 1; i >= 2; i--, j++) { //сортировка отсортированных отрезков
            sortFuncPrivate::mergeSequence(*resSequence, indexes[i - 2], indexes.getLast(), indexes[i - 1], cmp);
        }
        return resSequence;
    }

    auto resSequence = sequence.copy();

    for (size_t i = 2; i <= size; i*=2) { //сортировка отрезков, длина которых равна степени двойки
        for (size_t j = from; j + i <= to; j += i) {
            sortFuncPrivate::getBitonicSequence(*resSequence, j, j + i, cmp);             //преобразование отрезка к битонической последовательности
            sortFuncPrivate::sortBitonicSequence(*resSequence, j, j + i / 2, cmp);        //сортировка левой части
            sortFuncPrivate::sortBitonicSequence(*resSequence, j + i / 2, j + i, cmp);      //сортировка правой части
        }
    }

    return resSequence;
}

template<typename T>
mySequence<T>* BatcherSort(const mySequence<T>& sequence, size_t start, size_t end) {
    return BatcherSort(sequence, start, end, sortFuncPrivate::isLessDefault);
}

template<typename T>
mySequence<T>* BatcherSort(const mySequence<T>& sequence, bool (*cmp)(const T& obj1, const T& obj2)) {
    return BatcherSort(sequence, 0, sequence.length(), cmp);
}

template<typename T>
mySequence<T>* BatcherSort(const mySequence<T>& sequence) {
    return BatcherSort(sequence, sortFuncPrivate::isLessDefault);
}

#endif //BASE_CLASSES_BATCHERSORT_H
