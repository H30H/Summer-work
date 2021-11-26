//
// Created by Grisha on 04.09.2021.
//

#ifndef BASE_CLASSES_SORTINGMENU_H
#define BASE_CLASSES_SORTINGMENU_H

#include "../allSorts.h"
#include "../../Timer/myTimer.h"
#include <windows.h>
#include "../../Console/myConsole.h"
#include "../../Sequence/ArraySequenceTest.h"

class mySortMenuClass {
public:
    static void mainMenu() {
        myArraySequence<mySortInfo> allSorts
                {
                        mySortInfo{"BatcherSort", BatcherSort, BatcherSort},
                        mySortInfo{"BinaryTreeSort", BinaryTreeSort, BinaryTreeSort},
                        mySortInfo{"BinInsertSort", BinInsertSort, BinInsertSort},
                        mySortInfo{"BubbleSort", BubbleSort, BubbleSort},
                        mySortInfo{"CountingSort", CountingSort, CountingSort},
                        mySortInfo{"HeapSort", HeapSort, HeapSort},
                        mySortInfo{"InsertSort", InsertSort, InsertSort},
                        mySortInfo{"MergeSort", MergeSort, MergeSort},
                        mySortInfo{"QuickSort", QuickSort, QuickSort},
                        mySortInfo{"SelectionSort", SelectionSort, SelectionSort},
                        mySortInfo{"SelectionSortMod", SelectionSortMod, SelectionSortMod},
                        mySortInfo{"ShakerSort", ShakerSort, ShakerSort},
                        mySortInfo{"ShellSort", ShellSort, ShellSort}
                };

        myArraySequence<mySequence<int>*> memory;
        myArraySequence<bool> includeInComparison;

        for (size_t i = 0; i < allSorts.length(); i++)
            includeInComparison.append(false);

        size_t state = 0;

//        for (size_t i = 0; i < allSorts.length(); i++) {
//            includeInComparison.append(false);
//        }

        bool update = true;

        while (true) {
            std::cin.clear();
            contextMenu(update, state, memory.length());
            std::cout << ": ";
            bool good;
            state = readItem(good);

            if (!good) {
                continue;
            }

            if (state == 6)
                break;

            if (state > 6 || state == 0) {
                if (state != (size_t)(-1)) {
                    myConsole::moveCursorUp(9);
                    myConsole::removeLine();
                    myConsole::changeTextColor(255, 0, 0);
                    stateError();
                    std::cout << std::endl;
                    myConsole::applyDefaultColor();
                    myConsole::moveCursorDown(8);
                }
                continue;
            }

            if (state == 6)
                break;

            switch (state) {
                default:
                    break;
                case 1:
                    getArray(memory, getRandomInt);
                    update = true;
                    break;
                case 2:
                    if (memory.length() == 0)
                        break;
                    update = true;
                    checkArray(memory, getRandomInt);
                    break;
                case 3:
                    if (memory.length() == 0)
                        break;
                    update = true;
                    sortSequence(memory, allSorts);
                    break;
                case 4:
                    compareTime(allSorts, includeInComparison);
                    update = true;
                    break;
                case 5:
                    myConsole::moveCursorUp(9);
                    myConsole::removeLine();
                    myConsole::changeTextColor(255, 120, 0);
                    std::cout << "В разработке... (Coming soon)" << std::endl;
                    myConsole::applyDefaultColor();
                    myConsole::moveCursorDown(8);
//                    myArraySequenceTest(1000, true);
//                    update = true;
                    break;
            }

        }
    }
private:
    struct mySortInfo {
        std::string sortName;
        mySequence<int>* (*sortFunc)(const mySequence<int>& sequence) = nullptr;
        mySequence<int>* (*sortFuncIndex)(const mySequence<int>& sequence, size_t from, size_t to) = nullptr;
    };

    static int getRandomInt() {
        return rand();
    }

    static size_t readItem(bool& good) {
        std::string str;
        getline( std::cin, str);
        std::cin.clear();
        size_t i = 0;

        while (i < str.length() && (str[i] < '0' || str[i] > '9')) {
            i++;
        }

        if (i == str.length() || str[i] == '\0') {
            good = false;
            return -1;
        }

        size_t res = 0;
        good = true;

        for (i; i < str.length(); i++) {
            if (str[i] < '0' || str[i] > '9')
                break;
            res *= 10;
            res += str[i] - '0';
        }

        return res;
    }

    static size_t readItem() {
        bool k;
        return readItem(k);
    }

    static void contextMenu(bool& update, size_t state, size_t length) {
//        std::cout << "main :: Выберите необходимый пункт работы программы: " << std::endl <<
//                  "\t1. Считать массив типа int в память" << std::endl <<
//                  "\t2. Посмотреть все записанные массивы в памяти" << std::endl <<
//                  "\t3. Отсортировать массив выбранной сортировкой" << std::endl <<
//                  "\t4. Сравнить время работы сортировок на случайных данных" << std::endl <<
//                  "\t5. Выполнить тесты работы основнх функций" << std::endl <<
//                  "\t6. Выйти из программы" << std::endl;

        myConsole::applyDefaultColor();
        if (update) {
            update = false;
            std::cout << std::endl << "main :: Выберите необходимый пункт работы программы: " << std::endl;
            std::cout << "\t1. Считать массив типа int в память" << std::endl;
            if (length == 0)
                myConsole::changeTextColor(255, 0, 0);
            std::cout << "\t2. Посмотреть все записанные массивы в памяти" << std::endl;
            std::cout << "\t3. Отсортировать массив выбранной сортировкой" << std::endl;
            if (length == 0)
                myConsole::applyDefaultColor();
            std::cout << "\t4. Сравнить время работы сортировок на случайных данных" << std::endl;
            std::cout << "\t5. Выполнить тесты работы основнх функций" << std::endl;
            std::cout << "\t6. Выйти из программы" << std::endl;
            return;
        }
        myConsole::moveCursorUp();
        myConsole::removeLine();
        if (length == 0) {
            if (state == 2 || state == 3) {
                myConsole::moveCursorUp(8);
                myConsole::removeLine();
                myConsole::changeTextColor(255, 0, 0);
                std::cout << "В памяти нет массивов. Для начала запишите массив в память." << std::endl;
                myConsole::applyDefaultColor();
                myConsole::moveCursorDown(7);
            }
        }
    }

    static void stateError() {
        std::cout << "В меню нет такого пункта, повторите попытку!" << std::endl;
    }

    static void indexError(const std::string& item = "памяти") {
        std::cout << "Индекс превышает размер " << item << "!" << std::endl;
    }

//1

    template<typename T>
    static myArraySequence<T> createRandomArray(size_t size, T (*randomFunc)()) {
        myArraySequence<T> arraySequence;
        for (size_t i = 0; i < size; i++) {
            arraySequence.append(randomFunc());
        }
        return arraySequence;
    }

    template<typename T>
    static void getArray(myArraySequence<mySequence<T>*>& memory, T (*randomFunc)()) {
        if (memory.length() != 0)
            std::cout << "1::В памяти находиться \"" << memory.length() << "\" масивов. ";
        else
            std::cout << "1::В памяти не обнаружено массивов. ";
        std::cout << "Введите количество элементов нового массива." << std::endl << ": ";
        size_t size, state;
        size = readItem();
        myArraySequence<T> arraySequence;

        if (size == 0) {
            std::cout << "Вы действительно хотите добавить ПУСТОЙ массив? (0 - нет, 1 - да)" << std::endl;
            while (state > 1) {
                std::cout << ": ";
                state = readItem();
                if (state > 1) {
                    stateError();
                    continue;
                }

                if (state == 0) {
                    return;
                }
            }

            auto* item = new myArraySequence<T>();

            memory.append(item);
            std::cout << "В память был добавлен ПУСТОЙ массив." << std::endl;
            return;
        }

        std::cout << "Сгенерировать массив автоматически? (0 - нет, 1 - да)" << std::endl;
        state = 2;
        while (state > 1) {
            std::cout << ": ";
            state = readItem();
            if (state > 1) {
                stateError();
            }
        }


        if (state) {
            arraySequence = createRandomArray(size, randomFunc);
        }
        else {
            std::cout << " Введите \"" << size << "\" элементов нового массива." << std::endl;
            for (size_t i = 0; i < size; i++) {
                T k;
                std::cout << "\t: ";
                state = readItem();
                arraySequence.append(k);
            }
        }

        std::cout << "Вы действительно хотите записать массив " << arraySequence << " в память? (0 - нет, 1 - даб)" << std::endl;
        state = 2;
        while (state > 1) {
            std::cout << ": ";
            state = readItem();
            if (state > 1) {
                stateError();
                continue;
            }
            if (state == 0)
                return;
        }

        auto* item = new myArraySequence<T>(arraySequence);

        memory.append(item);
        std::cout << "В память был добавлен новый массив." << std::endl;
        int k = 0;
    }

    //2
    template<typename T>
    static void checkArray(myArraySequence<mySequence<T>*>& memory, T (*randFunc)()) {
        if (memory.length() == 0) {
            //std::cout << "В памяти не обнаружено массивов. Для начала запишите массив в память!" << std::endl;
            return;
        }

        while (memory.length()) {
            checkArrayMenu();
            std::cout << ": ";
            size_t state;
            state = readItem();
            if (state == 6)
                break;

            if (state > 6 || state == 0) {
                stateError();
                continue;
            }

            switch(state) {
                default:
                    break;
                case 1:
                    printArray(memory);
                    break;
                case 2:
                    swapArray(memory);
                    break;
                case 3:
                    deleteArray(memory);
                    break;
                case 4:
                    editArray(memory, randFunc);
                    break;
                case 5:
                    copyArray(memory);
                    break;
            }
        }

        if (memory.length() == 0) {
            std::cout << "В памяти больше не осталось массивов! Выход в главное меню." << std::endl;
        }
    }

    static void checkArrayMenu() {
        std::cout << "2 :: Выберите пункт меню для выбора операции: " << std::endl <<
                  "\t1: Для вывода одного массива в консоль" << std::endl <<
                  "\t2: Для изменения индексов у двух массивов (поменять 2 массива местами)" << std::endl <<
                  "\t3: Удалить один массив" << std::endl <<
                  "\t4: Изменить один массив" << std::endl <<
                  "\t5: Скопировать массив в конец памяти" << std::endl <<
                  "\t6: Выйти в главное меню" << std::endl;
    }

    template<typename T>
    static void printArray(myArraySequence<mySequence<T>*>& memory) {
        std::cout << "В памяти храниться \"" << memory.length() << "\" элементов. Введите индекс массива, который необходимо вывести" << std::endl;
        std::cout << ": ";
        size_t index;
        index = readItem();

        if (index >= memory.length()) {
            std::cout << "Индекс превышает размер памяти!" << std::endl;
        }

        std::cout << *memory[index] << std::endl;
    }

    template<typename T>
    static void swapArray(myArraySequence<mySequence<T>*>& memory) {
        if (memory.length() == 1) {
            std::cout << "В памяти находиться \"1\" элемент. Нет второго элемента для обмена индексов." << std::endl;
            return;
        }
        std::cout << "В памяти находится \"" << memory.length() << "\" масивов. Введите индекс первого массива" << std::endl;
        std::cout << ": ";
        size_t index1, index2;
        index1 = readItem();

        if (index1 >= memory.length()) {
            std::cout << "Индекс превышает размер памяти!" << std::endl;
            return;
        }

        std::cout << "Введите индекс второго массива" << std::endl;
        std::cout << ": ";
        index2 = readItem();

        if (index2 >= memory.length()) {
            std::cout << "Индекс превышает размер памяти!" << std::endl;
            return;
        }

        if (index1 == index2) {
            std::cout << "Индексы совпадают!" << std::endl;
            return;
        }

        memory.swap(index1, index2);
        std::cout << "Массивы были поменяны местами." << std::endl;
    }

    template<typename T>
    static void deleteArray(myArraySequence<mySequence<T>*>& memory) {
        std::cout << "В памяти находится \"" << memory.length() << "\" массивов. ";
        std::cout << "Введите индекс массива для его удаления" << std::endl;
        std::cout << ": ";

        size_t index, state;
        index = readItem();

        if (index >= memory.length()) {
            std::cout << "Индекс превышает размер памяти!" << std::endl;
        }

        std::cout << "Вы точно хотите удалить массив: " << *memory[index] << "? (0 - нет, 1 - да)" << std::endl;
        state = 2;
        while (state > 1) {
            std::cout << ": ";
            state = readItem();
            if (state > 1) {
                stateError();
            }
        }

        if (!state)
            return;

        delete memory.pop(index);
        std::cout << "Массив успешно удалён." << std::endl;
    }

    template<typename T>
    static void editArray(myArraySequence<mySequence<T>*> memory, T (*randFunc)()) {
        std::cout << "В памяти находится \"" << memory.length() << "\" масивов. Введите индекс массива для изменения" << std::endl;
        std::cout << ": ";
        size_t index, state = 1;
        index = readItem();

        if (index >= memory.length()) {
            std::cout << "Индекс превышает размер памяти!" << std::endl;
            return;
        }

        while (state) {
            editContexMenu();
            std::cout << ": ";
            state = readItem();

            if (state > 8 || state == 0) {
                stateError();
                continue;
            }

            if (state == 8)
                break;

            switch (state) {
                default:
                    break;
                case 1:
                    std::cout << *memory[index] << std::endl;
                    break;
                case 2:
                    getIndexItem(*memory[index]);
                    break;
                case 3:
                    std::cout << "Введите новый элемент" << std::endl << ": ";
                    T item;
                    std::cin >> item;
                    memory[index]->append(item);
                    break;
                case 4:
                    memory[index]->append(randFunc());
                    std::cout << "Был сгенерирован элемент \"" << memory[index]->get(memory[index]->length() - 1) << "\"." << std::endl;
                    break;
                case 5:
                    removeIndexItem(*memory[index]);
                    break;
                case 6:
                    swapIndexItem(*memory[index]);
                    break;
                case 7:
                    mixSequence(*memory[index]);
                    break;
            }
        }
    }

    static void editContexMenu() {
        std::cout << "2.4 :: Выберите пункт меню для работы с массивом:" << std::endl <<
                  "\t1: Вывести массив в консоль." << std::endl <<
                  "\t2: Вывести один элемент в консоль." << std::endl <<
                  "\t3: Добавить один элемент в конец массива." << std::endl <<
                  "\t4: Добавить случайный элемент в конец массива." << std::endl <<
                  "\t5: Удалить один элемент из массива." << std::endl <<
                  "\t6: Поменять элементы в массиве местами." << std::endl <<
                  "\t7: Перемешать массив" << std::endl <<
                  "\t8: Выход из редактирования массива" << std::endl;
    }

    template<typename T>
    static void getIndexItem(const mySequence<T>& sequence) {
        if (sequence.length() == 0) {
            std::cout << "Пустой массив!" << std::endl;
            return;
        }

        std::cout << "В массиве храниться \"" << sequence.length() << "\" элементов. ";
        std::cout << "Введите индекс элемента" << std::endl << ": ";
        size_t index;
        std::cin >> index;
        if (index >= sequence.length()) {
            indexError("массива");
            return;
        }

        std::cout << "По этому индексу лежит элемент \"" << sequence[index] << "\"." << std::endl;
    }

    template<typename T>
    static void removeIndexItem(mySequence<T>& sequence) {
        if (sequence.length() == 0) {
            std::cout << "Пустой массив!" << std::endl;
            return;
        }

        std::cout << "В массиве храниться \"" << sequence.length() << "\" элементов. ";
        std::cout << "Введите индекс элемента" << std::endl << ": ";
        size_t index;
        std::cin >> index;
        if (index >= sequence.length()) {
            indexError("массива");
            return;
        }

        std::cout << "Был удалён элемент \"" << sequence.pop(index) << "\"." << std::endl;
    }

    template<typename T>
    static void swapIndexItem(mySequence<T>& sequence) {
        if (sequence.length() == 0) {
            std::cout << "Пустой массив!" << std::endl;
            return;
        }
        if (sequence.length() == 1) {
            std::cout << "В массиве один элемент!" << std::endl;
            return;
        }

        std::cout << "В массиве храниться \"" << sequence.length() << "\" элементов. ";
        std::cout << "Введите индекс первого элемента" << std::endl << ": ";
        size_t index1, index2;
        std::cin >> index1;
        if (index1 >= sequence.length()) {
            indexError("массива");
            return;
        }

        std::cout << "Введите индекс второго элемента" << std::endl << ": ";
        std::cin >> index2;
        if (index2 >= sequence.length()) {
            indexError("массива");
            return;
        }

        if (index1 == index2) {
            std::cout << "Индексы совпадают!" << std::endl;
            return;
        }

        sequence.swap(index1, index2);
        std::cout << "Элементы \"" << sequence[index2] << "\" и \"" << sequence[index1] << "\" были переставлены." << std::endl;
    }

    static size_t getRandomIndex(size_t maxIndex) {
        return static_cast<size_t>(random())%maxIndex;
    }

    template<typename T>
    static void mixSequence(mySequence<T>& sequence) {
        for (size_t i = 0; i < sequence.length(); i++) {
            sequence.swap(getRandomIndex(sequence.length()), getRandomIndex(sequence.length()));
        }
    }

    template<typename T>
    static void copyArray(myArraySequence<mySequence<T>*>& memory) {
        std::cout << "Введите индекс массива для копирования" << std::endl << ": ";
        size_t index, state = 2;
        index = readItem();
        if (index >= memory.length()) {
            std::cout << " Индекс превышает размер памяти!" << std::endl;
            return;
        }

        std::cout << "Вы точно хотите скопировать массив " << *memory[index] << "? (0 - нет, 1 - да)";
        while (state > 1) {
            std::cout << ": ";
            state = readItem();
            if (state > 1)
                stateError();
        }

        if (!state)
            return;

        memory.append(new myArraySequence<T>(*memory[index]));
        std::cout << "Массив скопирован." << std::endl;
    }

    //3
    template<typename T>
    static void sortSequence(myArraySequence<mySequence<T>*>& memory, myArraySequence<mySortInfo>& sorts) {
        if (memory.length() == 0) {
//            std::cout << "В памяти не обнаружено массивов. Для начала запишите массив в память!" << std::endl;
            return;
        }
        std::cout << "В памяти находится \"" << memory.length() << "\" массивов. Введите индекс массива, который необходимо отсортировать" << std::endl;
        size_t index, state, indexFrom, indexTo;
        std::cout << ": ";
        index = readItem();
        if (index >= memory.length()) {
            indexError();
            return;
        }

        std::cout << "В массиве находится \"" << memory[index]->length() << "\" элементов. Хотите задать диапазон сортировки? (0 - нет, 1 - да)" << std::endl;

        state = 2;
        while (state > 1) {
            std::cout << ": ";
            state = readItem();
            if (state > 1)
                stateError();
        }

        if (state) {
            std::cout << "Введите индекс нижней границы" << std::endl << ": ";
            indexFrom = readItem();
            if (indexFrom >= memory[index]->length()) {
                indexError("массива");
                return;
            }

            std::cout << "Введите индекс верхней границы" << std::endl << ": ";
            indexTo = readItem();
            if (indexTo > memory[index]->length()) {
                indexError("массива");
                return;
            }
        }
        else {
            indexFrom = 0;
            indexTo = memory[index]->length();
        }

        std::cout << "Выберите следующий тип сортировки: " << std::endl;
        for (size_t i = 1; i <= sorts.length(); i++) {
            std::cout << "\t" << i << ": " + sorts[i-1].sortName << std::endl;
        }

        state = 0;
        while (state == 0 || state > sorts.length() + 1) {
            std::cout << ": ";
            state = readItem();
            if (state == 0 || state > sorts.length()) {
                stateError();
            }
        }

        size_t indexSort = state - 1;
        if (sorts[indexSort].sortName != "ShellSort") {
            mySequence<T>* res = sorts[indexSort].sortFuncIndex(*memory[index], indexFrom, indexTo);
            memory.append(res);
            std::cout << "Массив отсортирован." << std::endl;
            return;
        }

        ShellSortMenu(memory, index, indexFrom, indexTo);
        std::cout << "Массив отсортирован." << std::endl;
    }

    template<typename T>
    static void ShellSortMenu(myArraySequence<mySequence<T>*>& memory, size_t index, size_t indexFrom, size_t indexTo) {
        std::cout << "Хотите задать вручную интервалы для ShellSort? (0 - нет, 1 - да)" << std::endl;
        size_t state = 2;
        while (state > 1) {
            std::cout << ": ";
            std::cin >> state;
            if (state > 1)
                stateError();
        }

        if (state == 0) {
            memory.append(ShellSort(*memory[index], indexFrom, indexTo));
            return;
        }

        myArraySequence<size_t> intervals;
        while (true) {
            intervals = getIntervals();
            std::cout << intervals;
            std::cout << "; Использовать данные интервалы для сортировки? (0 - повторить ввод, 1 - да)" << std::endl;
            state = 2;
            while (state > 1) {
                std::cout << ": ";
                std::cin >> state;
                if (state > 2)
                    stateError();
            }
            if (state == 1)
                break;
        }

        memory.append(ShellSort(*memory[index], intervals, indexFrom, indexTo));
    }

    static myArraySequence<size_t> getIntervals() {
        myArraySequence<size_t> intervals;
        std::cout << "Введите интервалы для сортировки (1 - конец ввода)" << std::endl;
        size_t interval = 1;
        while (interval != 1) {
            std::cout << ": ";
            std::cin >> interval;
            if (interval == 0) {
                std::cout << "Интервал не может быть нулевым";
            }
            intervals.append(interval);
        }
        return intervals;
    }

    //4
    static void compareTime(const myArraySequence<mySortInfo>& sorts, myArraySequence<bool>& compSorts) {
        size_t state = 1;
        char c;

        getSorts(sorts, compSorts);

        size_t count = 0;
        for (bool compSort : compSorts)
            count += compSort ? 1 : 0;

        if (count == 0) {
            std::cout << "Ни одна сортировка не была выбрана!" << std::endl;
            return;
        }

        std::cout << "Было выбрано \"" << count << "\" сортировок. ";
        std::cout << "Введите размеры массивов, на которых необходимо выполнить сравнение времени работы. (0 - окончание ввода)" << std::endl;

        myArraySequence<size_t> arraySizes;
        size_t size = 1;
        while (size != 0) {
            std::cin.clear();
            std::cout << ": ";
            size = readItem();
            if (size != 0)
                arraySizes.append(size);
        }

        if (arraySizes.length() == 0) {
            std::cout << "Нет был введён ни один размер массива!" << std::endl;
            return;
        }
        std::cout << "Введённые размеры массивов: " << arraySizes << std::endl;
        std::cout << "Введите количество попыток сортировки одним массивом" << std::endl;

        size_t sortCount;
        std::cout << ": ";
        sortCount = readItem();
        if (sortCount == 0) {
            std::cout << "Нулевое количество массивов!" << std::endl;
            return;
        }

        myArraySequence<myArraySequence<double>> times;
        //std::cout << "size " << arraySizes.length() << std::endl;
        for (auto &i : arraySizes) {
            std::cout << "  size: " << i << std::endl;
            times.append(getSortsTime(sorts, compSorts, i, sortCount));
        }

        myConsole::changeTextColor(255, 127, 0);
        std::cout << "Таблица времени сортировок (в милисекундах)" << std::endl;
        myConsole::applyDefaultColor();
        std::cout << getTable(sorts, compSorts, arraySizes, times) << std::endl;
    }

    static void getSorts(const myArraySequence<mySortInfo>& sorts, myArraySequence<bool>& compSorts) {
        bool error = false;
        size_t state = 1;
        size_t maxState = -1;
        std::cout << std::endl;

        contextMenuCompareTime(sorts, compSorts, true);
        while (true) {
            std::cout << ": ";
            state = readItem();

            if (state == 0)
                break;

            if (state == maxState || state > sorts.length()) {
                myConsole::moveCursorUp();
                myConsole::removeLine();

                if (error) {
                    continue;
                }
                myConsole::moveCursorUp(sorts.length() + 2);
                myConsole::changeTextColor(255, 0, 0);
                stateError();
                myConsole::moveCursorDown(sorts.length() + 1);
                myConsole::applyDefaultColor();
                error = true;
                continue;
            }

            if (error) {
                myConsole::moveCursorUp(sorts.length() + 3);
                myConsole::removeLine();
                myConsole::moveCursorDown(state + 1);
//                std::cout << std::string("\x1B[") + std::to_string(sorts.length() + 3) + "A"; //переместиться на строку с ошибкой
//                std::cout << std::string("\x1B[K");                                               //убрать ошибку
//                std::cout << std::string("\x1B[") + std::to_string(state + 1) + "B";          //переместиться на строку state
            }
            else {
                myConsole::moveCursorUp(sorts.length() + 2 - state);
//                std::cout << std::string("\x1B[") + std::to_string(sorts.length() + 2 - state) + "A"; //переместиться на строку state
            }

            compSorts[state-1] = !compSorts[state-1];

            if (compSorts[state-1])
                myConsole::changeTextColor(0, 255, 0);
//                std::cout << "\x1B[0;32;40m";  //поменять цвет на зелёный
            else
                myConsole::changeTextColor(255, 0, 0);
//                std::cout << "\x1B[0;31;40m";  //поменять цвет на красный

            std::cout << "\t" << state << "." << "[" << (compSorts[state-1] ? "+" : "-") << "]: " << sorts[state-1].sortName << "." << std::endl;  //обновить текущую строку
            myConsole::applyDefaultColor();
//            std::cout << "\x1b[0;0m";                                                                         //поменять цвет на обычный
            if (state != sorts.length())    //проверка на то, что был выбран не последний пункт (если последний, нет необходимости переноса курсора)
                myConsole::moveCursorDown(sorts.length() - state);
//                std::cout << std::string("\x1B[") + std::to_string(sorts.length() - state) + "B";  //переместиться на строку ввода
            myConsole::removeLine();
//            std::cout << "\x1B[K";                                                                            //убрать текущий ввод

            error = false;
        }
    }

    static void contextMenuCompareTime(const myArraySequence<mySortInfo>& sorts, const myArraySequence<bool>& compSorts, bool first) {
//        if (!first) {
//            for (size_t i = 0; i < compSorts.length(); i++) {
//                clear();
//            }

//            std::cout << std::string("\x1B[") + std::to_string(sorts.length() + 2) + "A";
//        }
        std::cout << "4 :: Введите номер сортировки для её включения/выключения или 0 для запуска функции." << std::endl;
        size_t spaceCount = 0;
        size_t nextPoint = 10;
        for (size_t i = compSorts.length() - 1; i > 0; i /= 10, spaceCount += 1);
        for (size_t i = 0; i < sorts.length(); i++) {
            if (compSorts[i])
                myConsole::changeTextColor(0, 255, 0);
//                std::cout << "\x1B[0;32;40m";
            else
                myConsole::changeTextColor(255, 0, 0);
//                std::cout << "\x1B[0;31;40m";

            std::cout << "\t" << (i+1) << ".";
            if (i+1 == nextPoint) {
                nextPoint *= 10;
                spaceCount--;
            }

//            for (size_t j = 0; j < spaceCount; j++)
//                std::cout << ' ';

            std::cout << "[" << (compSorts[i] ? "+" : "-") << "]: " << sorts[i].sortName << "." << std::endl;
        }
//        std::cout << "\x1b[0;0m";
        myConsole::applyDefaultColor();
    }

    static myArraySequence<double> getSortsTime(const myArraySequence<mySortInfo>& sorts, const myArraySequence<bool>& compSorts, size_t size, size_t count) {
        myArraySequence<myArraySequence<int>> arrays;
        myArraySequence<double> res;
        for (size_t j = 0; j < count; j++) {
            arrays.append(myArraySequence<int>());
            for (size_t i = 0; i < size; i++) {
                arrays[arrays.length() - 1].append(getRandomInt());
            }
        }

        size_t errors;

        for (size_t i = 0; i < compSorts.length(); i++) {
            if (compSorts[i]) {
                double time = 0;
                myConsole::changeTextColor(255, 120, 0);
                std::cout << "    " << sorts[i].sortName << std::endl;
                for (size_t j = 0; j < count; j++) {
                    double tm = getOneSortTime(sorts[i], arrays[j], count, errors);
                    time += tm;
//                    std::cout << tm << std::endl;
                }
                res.append(time / (double)count * 1000);
                myConsole::moveCursorUp();
                myConsole::applyDefaultColor();
                if (errors != 0)
                    myConsole::changeTextColor(255, 0, 0);
                else
                    myConsole::changeTextColor(0, 255, 0);
                std::cout << "    " << sorts[i].sortName << " done!";
                if (errors != 0) {
                    std::cout << " (" << errors << " ошибок)";
                }
                myConsole::applyDefaultColor();
                std::cout << std::endl;
            }
        }
        return res;
    }

    static double getOneSortTime(const mySortInfo& sort, const myArraySequence<int>& seq, size_t count, size_t& errors) {
        myTimer timer;
        auto sortArray = sort.sortFunc(seq);
        double time = timer.time();

        errors = checkSort(sortArray);

        delete sortArray;
        return time;
    }

    static size_t checkSort(mySequence<int>* sortSeq) {
        size_t res = 0;
        for (size_t j = 1; j < sortSeq->length(); j++) {
            if (sortSeq->operator[](j-1) > sortSeq->operator[](j)) {
                ++res;
                break;
            }
        }
        return res;
    }

    static std::string getTable(const myArraySequence<mySortInfo>& sorts,
                                const myArraySequence<bool>& compSorts,
                                const myArraySequence<size_t>& sizes,
                                const myArraySequence<myArraySequence<double>>& values) {
        std::string res;
        myArraySequence<size_t> indexes;
        myArraySequence<std::string> strings;
        size_t maxStrLen;
        strings.append(std::string("|") + "sorts");
        strings.append("+");
        maxStrLen = strings[0].length();

        for (size_t i = 0, j = 2; i < compSorts.length(); i++) {
            if (compSorts[i]) {
                indexes.append(i);
                strings.append("|");
                strings[j] += sorts[i].sortName;
                maxStrLen = (strings[j].length() > maxStrLen) ? strings[j].length() : maxStrLen;
                ++j;
            }
        }

        checkSpaces(strings, maxStrLen);
        for (size_t i = 0; i < values.length(); i++) {
            strings[0] += std::to_string(sizes[i]);
            maxStrLen = strings[0].length();

            for (size_t j = 0; j < values[i].length(); j++) {
                strings[j+2] += std::to_string(values[i][j]);
                if (maxStrLen < strings[j+2].length())
                    maxStrLen = strings[j+2].length();
            }
            checkSpaces(strings, maxStrLen);
        }

        for (auto &i : strings) {
            res += i + '\n';
        }

        return res;
    }

    static void checkSpaces(const myArraySequence<std::string>& strArr, size_t& size) {
        for (auto &i : strArr) {
            if (i[0] == '+') {
                while (i.length() < size)
                    i += '-';
                i += '+';
            }
            else {
                while (i.length() < size)
                    i += ' ';
                i += '|';
            }
        }
        size++;
    }
};


class mySortMenuClassOld {
public:
    static void mainMenu() {
        myArraySequence<mySortList> allSorts
                {
                        mySortList{"BatcherSort", BatcherSort, BatcherSort},
                        mySortList{"BinaryTreeSort", BinaryTreeSort, BinaryTreeSort},
                        mySortList{"BinInsertSort", BinInsertSort, BinInsertSort},
                        mySortList{"BubbleSort", BubbleSort, BubbleSort},
                        mySortList{"CountingSort", CountingSort, CountingSort},
                        mySortList{"HeapSort", HeapSort, HeapSort},
                        mySortList{"InsertSort", InsertSort, InsertSort},
                        mySortList{"MergeSort", MergeSort, MergeSort},
                        mySortList{"QuickSort", QuickSort, QuickSort},
                        mySortList{"SelectionSort", SelectionSort, SelectionSort},
                        mySortList{"SelectionSortMod", SelectionSortMod, SelectionSortMod},
                        mySortList{"ShakerSort", ShakerSort, ShakerSort},
                        mySortList{"ShellSort", ShellSort, ShellSort}
                };

        myArraySequence<mySequence<int>*> memory;
        myArraySequence<bool> compareArray;
        for (size_t i = 0; i < allSorts.length(); i++)
            compareArray.append(false);

        size_t state;

        for (size_t i = 0; i < allSorts.length(); i++) {
            compareArray.append(false);
        }

        while (true) {
            std::cin.clear();
            contextMenu();
            std::cout << ": ";
            std::cin >> state;

            if (state == 6)
                break;

            if (state > 6 || state == 0) {
                stateError();
                continue;
            }

            if (state == 6)
                break;

            switch (state) {
                default:
                    break;
                case 1:
                    getArray(memory, getRandomInt);
                    break;
                case 2:
                    checkArray(memory, getRandomInt);
                    break;
                case 3:
                    sortSequence(memory, allSorts);
                    break;
                case 4:
                    compareTime(allSorts, compareArray);
                    break;
                case 5:
                    std::cout << "В разработке... (Coming soon)" << std::endl;
                    break;
            }

        }
    }
private:
    struct mySortList {
        std::string sortName;
        mySequence<int>* (*sortFunc)(const mySequence<int>& sequence) = nullptr;
        mySequence<int>* (*sortFuncIndex)(const mySequence<int>& sequence, size_t from, size_t to) = nullptr;
    };

    static int getRandomInt() {
        return rand();
    }

    static void contextMenu() {
        std::cout << "main :: Выберите необходимый пункт работы программы: " << std::endl <<
                  "\t1. Считать массив типа int в память" << std::endl <<
                  "\t2. Посмотреть все записанные массивы в памяти" << std::endl <<
                  "\t3. Отсортировать массив выбранной сортировкой" << std::endl <<
                  "\t4. Сравнить время работы сортировок на случайных данных" << std::endl <<
                  "\t5. Выполнить тесты работы основнх функций" << std::endl <<
                  "\t6. Выйти из программы" << std::endl;
    }

    static void stateError() {
        std::cout << "В меню нет такого пункта, повторите попытку!" << std::endl;
    }

    static void indexError(const std::string& item = "памяти") {
        std::cout << "Индекс превышает размер " << item << "!" << std::endl;
    }

//1

    template<typename T>
    static myArraySequence<T> getRandomArray(size_t size, T (*randomFunc)()) {
        myArraySequence<T> arraySequence;
        for (size_t i = 0; i < size; i++) {
            arraySequence.append(randomFunc());
        }
        return arraySequence;
    }

    template<typename T>
    static void getArray(myArraySequence<mySequence<T>*>& memory, T (*randomFunc)()) {
        if (memory.length() != 0)
            std::cout << "1::В памяти находиться \"" << memory.length() << "\" масивов. ";
        else
            std::cout << "1::В памяти не обнаружено массивов. ";
        std::cout << "Введите количество элементов нового массива." << std::endl << ": ";
        size_t size, state;
        std::cin >> size;
        myArraySequence<T> arraySequence;

        if (size == 0) {
            std::cout << "Вы действительно хотите добавить ПУСТОЙ массив? (0 - нет, 1 - да)" << std::endl;
            while (state > 1) {
                std::cout << ": ";
                std::cin >> state;
                if (state > 1) {
                    stateError();
                    continue;
                }

                if (state == 0) {
                    return;
                }
            }

            auto* item = new myArraySequence<T>();

            memory.append(item);
            std::cout << "В память был добавлен ПУСТОЙ массив." << std::endl;
            return;
        }

        std::cout << "Сгенерировать массив автоматически? (0 - нет, 1 - да)" << std::endl;
        state = 2;
        while (state > 1) {
            std::cout << ": ";
            std::cin >> state;
            if (state > 1) {
                stateError();
            }
        }


        if (state) {
            arraySequence = getRandomArray(size, randomFunc);
        }
        else {
            std::cout << " Введите \"" << size << "\" элементов нового массива." << std::endl;
            for (size_t i = 0; i < size; i++) {
                T k;
                std::cout << "\t: ";
                std::cin >> k;
                arraySequence.append(k);
            }
        }

        std::cout << "Вы действительно хотите записать массив " << arraySequence << " в память? (0 - нет, 1 - даб)" << std::endl;
        state = 2;
        while (state > 1) {
            std::cout << ": ";
            std::cin >> state;
            if (state > 1) {
                stateError();
                continue;
            }
            if (state == 0)
                return;
        }

        auto* item = new myArraySequence<T>(arraySequence);

        memory.append(item);
        std::cout << "В память был добавлен новый массив." << std::endl;
        int k = 0;
    }

    //2
    template<typename T>
    static void checkArray(myArraySequence<mySequence<T>*>& memory, T (*randFunc)()) {
        if (memory.length() == 0) {
            std::cout << "В памяти не обнаружено массивов. Для начала запишите массив в память!" << std::endl;
            return;
        }

        while (memory.length()) {
            checkArrayMenu();
            std::cout << ": ";
            size_t state;
            std::cin >> state;
            if (state == 5)
                break;

            if (state > 5 || state == 0) {
                stateError();
                continue;
            }

            switch(state) {
                default:
                    break;
                case 1:
                    printArray(memory);
                    break;
                case 2:
                    swapArray(memory);
                    break;
                case 3:
                    deleteArray(memory);
                    break;
                case 4:
                    editArray(memory, randFunc);
                    break;
                case 5:
                    copyArray(memory);
                    break;
            }
        }

        if (memory.length() == 0) {
            std::cout << "В памяти больше не осталось массивов! Выход в главное меню." << std::endl;
        }
    }

    static void checkArrayMenu() {
        std::cout << "2 :: Выберите пункт меню для выбора операции: " << std::endl <<
                  "\t1: Для вывода одного массива в консоль" << std::endl <<
                  "\t2: Для изменения индексов у двух массивов (поменять 2 массива местами)" << std::endl <<
                  "\t3: Удалить один массив" << std::endl <<
                  "\t4: Изменить один массив" << std::endl <<
                  "\t5: Скопировать массив в конец памяти" << std::endl <<
                  "\t6: Выйти в главное меню" << std::endl;
    }

    template<typename T>
    static void printArray(myArraySequence<mySequence<T>*>& memory) {
        std::cout << "В памяти храниться \"" << memory.length() << "\" элементов. Введите индекс массива, который необходимо вывести" << std::endl;
        std::cout << ": ";
        size_t index;
        std::cin >> index;

        if (index >= memory.length()) {
            std::cout << "Индекс превышает размер памяти!" << std::endl;
        }

        std::cout << *memory[index] << std::endl;
    }

    template<typename T>
    static void swapArray(myArraySequence<mySequence<T>*>& memory) {
        if (memory.length() == 1) {
            std::cout << "В памяти находиться \"1\" элемент. Нет второго элемента для обмена индексов." << std::endl;
            return;
        }
        std::cout << "В памяти находится \"" << memory.length() << "\" масивов. Введите индекс первого массива" << std::endl;
        std::cout << ": ";
        size_t index1, index2;
        std::cin >> index1;

        if (index1 >= memory.length()) {
            std::cout << "Индекс превышает размер памяти!" << std::endl;
            return;
        }

        std::cout << "Введите индекс второго массива" << std::endl;
        std::cout << ": ";
        std::cin >> index2;

        if (index2 >= memory.length()) {
            std::cout << "Индекс превышает размер памяти!" << std::endl;
            return;
        }

        if (index1 == index2) {
            std::cout << "Индексы совпадают!" << std::endl;
            return;
        }

        memory.swap(index1, index2);
        std::cout << "Массивы были поменяны местами." << std::endl;
    }

    template<typename T>
    static void deleteArray(myArraySequence<mySequence<T>*>& memory) {
        std::cout << "В памяти находится \"" << memory.length() << "\" массивов. ";
        std::cout << "Введите индекс массива для его удаления" << std::endl;
        std::cout << ": ";

        size_t index, state;
        std::cin >> index;

        if (index >= memory.length()) {
            std::cout << "Индекс превышает размер памяти!" << std::endl;
        }

        std::cout << "Вы точно хотите удалить массив: " << *memory[index] << "? (0 - нет, 1 - да)";
        state = 2;
        while (state > 1) {
            std::cout << ": ";
            std::cin >> state;
            if (state > 1) {
                stateError();
            }
        }

        if (!state)
            return;

        delete memory.pop(index);
        std::cout << "Массив успешно удалён." << std::endl;
    }

    template<typename T>
    static void editArray(myArraySequence<mySequence<T>*> memory, T (*randFunc)()) {
        std::cout << "В памяти находится \"" << memory.length() << "\" масивов. Введите индекс массива для изменения" << std::endl;
        std::cout << ": ";
        size_t index, state = 1;
        std::cin >> index;

        if (index >= memory.length()) {
            std::cout << "Индекс превышает размер памяти!" << std::endl;
            return;
        }

        while (state) {
            editContexMenu();
            std::cout << ": ";
            std::cin >> state;

            if (state > 8 || state == 0) {
                stateError();
                continue;
            }

            if (state == 8)
                break;

            switch (state) {
                default:
                    break;
                case 1:
                    std::cout << *memory[index] << std::endl;
                    break;
                case 2:
                    getIndexItem(*memory[index]);
                    break;
                case 3:
                    std::cout << "Введите новый элемент" << std::endl << ": ";
                    T item;
                    std::cin >> item;
                    memory[index]->append(item);
                    break;
                case 4:
                    memory[index]->append(randFunc());
                    std::cout << "Был сгенерирован элемент \"" << memory[index]->get(memory[index]->length() - 1) << "\"." << std::endl;
                    break;
                case 5:
                    removeIndexItem(*memory[index]);
                    break;
                case 6:
                    swapIndexItem(*memory[index]);
                    break;
                case 7:
                    mixSequence(*memory[index]);
                    break;
            }
        }
    }

    static void editContexMenu() {
        std::cout << "2.4 :: Выберите пункт меню для работы с массивом:" << std::endl <<
                  "\t1: Вывести массив в консоль." << std::endl <<
                  "\t2: Вывести один элемент в консоль." << std::endl <<
                  "\t3: Добавить один элемент в конец массива." << std::endl <<
                  "\t4: Добавить случайный элемент в конец массива." << std::endl <<
                  "\t5: Удалить один элемент из массива." << std::endl <<
                  "\t6: Поменять элементы в массиве местами." << std::endl <<
                  "\t7: Перемешать массив" << std::endl <<
                  "\t8: Выход из редактирования массива" << std::endl;
    }

    template<typename T>
    static void getIndexItem(const mySequence<T>& sequence) {
        if (sequence.length() == 0) {
            std::cout << "Пустой массив!" << std::endl;
            return;
        }

        std::cout << "В массиве храниться \"" << sequence.length() << "\" элементов. ";
        std::cout << "Введите индекс элемента" << std::endl << ": ";
        size_t index;
        std::cin >> index;
        if (index >= sequence.length()) {
            indexError("массива");
            return;
        }

        std::cout << "По этому индексу лежит элемент \"" << sequence[index] << "\"." << std::endl;
    }

    template<typename T>
    static void removeIndexItem(mySequence<T>& sequence) {
        if (sequence.length() == 0) {
            std::cout << "Пустой массив!" << std::endl;
            return;
        }

        std::cout << "В массиве храниться \"" << sequence.length() << "\" элементов. ";
        std::cout << "Введите индекс элемента" << std::endl << ": ";
        size_t index;
        std::cin >> index;
        if (index >= sequence.length()) {
            indexError("массива");
            return;
        }

        std::cout << "Был удалён элемент \"" << sequence.pop(index) << "\"." << std::endl;
    }

    template<typename T>
    static void swapIndexItem(mySequence<T>& sequence) {
        if (sequence.length() == 0) {
            std::cout << "Пустой массив!" << std::endl;
            return;
        }
        if (sequence.length() == 1) {
            std::cout << "В массиве один элемент!" << std::endl;
            return;
        }

        std::cout << "В массиве храниться \"" << sequence.length() << "\" элементов. ";
        std::cout << "Введите индекс первого элемента" << std::endl << ": ";
        size_t index1, index2;
        std::cin >> index1;
        if (index1 >= sequence.length()) {
            indexError("массива");
            return;
        }

        std::cout << "Введите индекс второго элемента" << std::endl << ": ";
        std::cin >> index2;
        if (index2 >= sequence.length()) {
            indexError("массива");
            return;
        }

        if (index1 == index2) {
            std::cout << "Индексы совпадают!" << std::endl;
            return;
        }

        sequence.swap(index1, index2);
        std::cout << "Элементы \"" << sequence[index2] << "\" и \"" << sequence[index1] << "\" были переставлены." << std::endl;
    }

    static size_t getRandomIndex(size_t maxIndex) {
        return static_cast<size_t>(random())%maxIndex;
    }

    template<typename T>
    static void mixSequence(mySequence<T>& sequence) {
        for (size_t i = 0; i < sequence.length(); i++) {
            sequence.swap(getRandomIndex(sequence.length()), getRandomIndex(sequence.length()));
        }
    }

    template<typename T>
    static void copyArray(myArraySequence<mySequence<T>*>& memory) {
        std::cout << "Введите индекс массива для копирования" << std::endl << ": ";
        size_t index, state = 2;
        std::cin >> index;
        if (index >= memory.length()) {
            std::cout << " Индекс превышает размер памяти!" << std::endl;
            return;
        }

        std::cout << "Вы точно хотите скопировать массив " << *memory[index] << "? (0 - нет, 1 - да)";
        while (state > 1) {
            std::cout << ": ";
            std::cin >> state;
            if (state > 1)
                stateError();
        }

        if (!state)
            return;

        memory.append(new myArraySequence<T>(*memory[index]));
        std::cout << "Массив скопирован." << std::endl;
    }

    //3
    template<typename T>
    static void sortSequence(myArraySequence<mySequence<T>*> memory, myArraySequence<mySortList>& sorts) {
        if (memory.length() == 0) {
            std::cout << "В памяти не обнаружено массивов. Для начала запишите массив в память!" << std::endl;
            return;
        }
        std::cout << "В памяти находится \"" << memory.length() << "\" массивов. Введите индекс массива, который необходимо отсортировать" << std::endl;
        size_t index, state, indexFrom, indexTo;
        std::cout << ": ";
        std::cin >> index;
        if (index >= memory.length()) {
            indexError();
            return;
        }

        std::cout << "В массиве находится \"" << memory[index]->length() << "\" элементов. Хотите задать диапазон сортировки? (0 - нет, 1 - да)" << std::endl;

        state = 2;
        while (state > 1) {
            std::cout << ": ";
            std::cin >> state;
            if (state > 1)
                stateError();
        }

        if (state) {
            std::cout << "Введите индекс нижней границы" << std::endl << ": ";
            std::cin >> indexFrom;
            if (indexFrom >= memory[index]->length()) {
                indexError("массива");
                return;
            }

            std::cout << "Введите индекс верхней границы" << std::endl << ": ";
            std::cin >> indexTo;
            if (indexTo > memory[index]->length()) {
                indexError("массива");
                return;
            }
        }
        else {
            indexFrom = 0;
            indexTo = memory[index]->length();
        }

        std::cout << "Выберите следующий тип сортировки: " << std::endl;
        for (size_t i = 1; i <= sorts.length(); i++) {
            std::cout << "\t" << i << ": " + sorts[i-1].sortName << std::endl;
        }

        state = sorts.length() + 1;
        while (state == 0 || state > sorts.length() + 1) {
            std::cout << ": ";
            std::cin >> state;
            if (state == 0 || state > sorts.length()) {
                stateError();
            }
        }

        size_t indexSort = state - 1;
        if (sorts[indexSort].sortName != "ShellSort") {
            mySequence<T>* res = sorts[indexSort].sortFuncIndex(*memory[index], indexFrom, indexTo);
            memory.append(res);
            std::cout << "Массив отсортирован." << std::endl;
            return;
        }

        ShellSortMenu(memory, index, indexFrom, indexTo);
        std::cout << "Массив отсортирован." << std::endl;

    }

    template<typename T>
    static void ShellSortMenu(myArraySequence<mySequence<T>*>& memory, size_t index, size_t indexFrom, size_t indexTo) {
        std::cout << "Хотите задать вручную интервалы для ShellSort? (0 - нет, 1 - да)" << std::endl;
        size_t state = 2;
        while (state > 1) {
            std::cout << ": ";
            std::cin >> state;
            if (state > 1)
                stateError();
        }

        if (state == 0) {
            memory.append(ShellSort(*memory[index], indexFrom, indexTo));
            return;
        }

        myArraySequence<size_t> intervals;
        while (true) {
            intervals = getIntervals();
            std::cout << intervals;
            std::cout << "; Использовать данные интервалы для сортировки? (0 - повторить ввод, 1 - да)" << std::endl;
            state = 2;
            while (state > 1) {
                std::cout << ": ";
                std::cin >> state;
                if (state > 2)
                    stateError();
            }
            if (state == 1)
                break;
        }

        memory.append(ShellSort(*memory[index], intervals, indexFrom, indexTo));
    }

    static myArraySequence<size_t> getIntervals() {
        myArraySequence<size_t> intervals;
        std::cout << "Введите интервалы для сортировки (1 - конец ввода)" << std::endl;
        size_t interval = 1;
        while (interval != 1) {
            std::cout << ": ";
            std::cin >> interval;
            if (interval == 0) {
                std::cout << "Интервал не может быть нулевым";
            }
            intervals.append(interval);
        }
        return intervals;
    }

    //4
    static void compareTime(const myArraySequence<mySortList>& sorts, myArraySequence<bool>& compSorts) {
        size_t state = 1;
        char c;
        std::cin.getline(&c, 1);
        /*bool first = true;
        while (state > 0) {
            contextMenuCompareTime(sorts, compSorts, first);
            first = false;
            std::cout << ": ";
            std::cin >> state;
            if (state == 0) {
                break;
            }

            size_t index = state - 1;
            if (index >= sorts.length()) {
                stateError();
                continue;
            }

            compSorts[index] = !compSorts[index];
        }*/

        getSorts(sorts, compSorts);

        size_t count = 0;
        for (bool compSort : compSorts)
            count += compSort ? 1 : 0;

        if (count == 0) {
            std::cout << "Ни одна сортировка не была выбрана!" << std::endl;
            return;
        }

        std::cout << "Было выбрано \"" << count << "\" сортировок. ";
        std::cout << "Введите размеры массивов, на которых необходимо выполнить сравнение времени работы. (0 - окончание ввода)" << std::endl;

        myArraySequence<size_t> arraySizes;
        size_t size = 1;
        while (size != 0) {
            std::cin.clear();
            std::cout << ": ";
            std::cin >> size;
            if (size != 0)
                arraySizes.append(size);
        }

        if (arraySizes.length() == 0) {
            std::cout << "Нет был введён ни один размер массива!" << std::endl;
            return;
        }
        std::cout << "Введённые размеры массивов: " << arraySizes << std::endl;
        std::cout << "Введите количество попыток сортировки одним массивом" << std::endl;

        size_t sortCount;
        std::cout << ": ";
        std::cin >> sortCount;
        if (sortCount == 0) {
            std::cout << "Нулевое количество массивов!" << std::endl;
            return;
        }

        myArraySequence<myArraySequence<double>> times;
        //std::cout << "size " << arraySizes.length() << std::endl;
        for (auto &i : arraySizes) {
            std::cout << "  size: " << i << std::endl;
            times.append(getSortsTime(sorts, compSorts, i, sortCount));
        }

        std::cout << getTable(sorts, compSorts, arraySizes, times) << std::endl;
    }

    static void getSorts(const myArraySequence<mySortList>& sorts, myArraySequence<bool>& compSorts) {
        bool error = false;
        size_t state = 1;
        size_t maxState = -1;
        std::cout << std::endl;

        contextMenuCompareTime(sorts, compSorts, true);
        while (true) {
            std::cout << ": ";
            state = getItem();

            if (state == 0)
                break;

            if (state == maxState || state > sorts.length()) {
                std::cout << "\x1B[1A";  //переместиться на строку вверх
                std::cout << "\x1B[K";   //убрать текущий ввод

                if (error) {
                    continue;
                }

                std::cout << std::string("\x1B[") + std::to_string(sorts.length() + 2) + "A"; //переместиться на строку с ошибкой
                std::cout << "\x1B[0;31;40m";  //поменять цвет на красный
                stateError();
                std::cout << "\x1b[0;0m";
                std::cout << std::string("\x1B[") + std::to_string(sorts.length() + 1) + "B"; //переместиться на строку с вводом
                error = true;
                continue;
            }

            if (error) {
                std::cout << std::string("\x1B[") + std::to_string(sorts.length() + 3) + "A"; //переместиться на строку с ошибкой
                std::cout << std::string("\x1B[K");                                               //убрать ошибку
                std::cout << std::string("\x1B[") + std::to_string(state + 1) + "B";          //переместиться на строку state
            }
            else {
                std::cout << std::string("\x1B[") + std::to_string(sorts.length() + 2 - state) + "A"; //переместиться на строку state
            }

            compSorts[state-1] = !compSorts[state-1];

            if (compSorts[state-1])
                std::cout << "\x1B[0;32;40m";  //поменять цвет на зелёный
            else
                std::cout << "\x1B[0;31;40m";  //поменять цвет на красный

            std::cout << "\t" << state << "." << "[" << (compSorts[state-1] ? "+" : "-") << "]: " << sorts[state-1].sortName << "." << std::endl;  //обновить текущую строку
            std::cout << "\x1b[0;0m";                                                                         //поменять цвет на обычный
            if (state != sorts.length())    //проверка на то, что был выбран не последний пункт (если последний, нет необходимости переноса курсора)
                std::cout << std::string("\x1B[") + std::to_string(sorts.length() - state) + "B";  //переместиться на строку ввода
            std::cout << "\x1B[K";                                                                            //убрать текущий ввод

            error = false;
        }
    }

    static size_t getItem() {
        char* c = new char[100];
        std::cin.getline(c, 100);
        std::cin.clear();

        if (c[0] < '0' || c[0] > '9')
            return -1;

        size_t res = 0;

        for (size_t i = 0; i < 100; i++) {
            if (c[i] < '0' || c[i] > '9')
                break;
            res *= 10;
            res += c[i] - '0';
        }

        return res;
    }

    static void contextMenuCompareTime(const myArraySequence<mySortList>& sorts, const myArraySequence<bool>& compSorts, bool first) {
//        if (!first) {
//            for (size_t i = 0; i < compSorts.length(); i++) {
//                clear();
//            }

//            std::cout << std::string("\x1B[") + std::to_string(sorts.length() + 2) + "A";
//        }
        std::cout << "4 :: Введите номер сортировки для её включения/выключения или 0 для запуска функции." << std::endl;
        size_t spaceCount = 0;
        size_t nextPoint = 10;
        for (size_t i = compSorts.length() - 1; i > 0; i /= 10, spaceCount += 1);
        for (size_t i = 0; i < sorts.length(); i++) {
            if (compSorts[i])
                std::cout << "\x1B[0;32;40m";
            else
                std::cout << "\x1B[0;31;40m";

            std::cout << "\t" << (i+1) << ".";
            if (i+1 == nextPoint) {
                nextPoint *= 10;
                spaceCount--;
            }

//            for (size_t j = 0; j < spaceCount; j++)
//                std::cout << ' ';

            std::cout << "[" << (compSorts[i] ? "+" : "-") << "]: " << sorts[i].sortName << "." << std::endl;
        }
        std::cout << "\x1b[0;0m";
    }

    static myArraySequence<double> getSortsTime(const myArraySequence<mySortList>& sorts, const myArraySequence<bool>& compSorts, size_t size, size_t count) {
        myArraySequence<myArraySequence<int>> arrays;
        myArraySequence<double> res;
        for (size_t j = 0; j < count; j++) {
            arrays.append(myArraySequence<int>());
            for (size_t i = 0; i < size; i++) {
                arrays[arrays.length() - 1].append(getRandomInt());
            }
        }

        size_t errors;

        for (size_t i = 0; i < compSorts.length(); i++) {
            if (compSorts[i]) {
                double time = 0;
                std::cout << "    " << sorts[i].sortName;
                for (size_t j = 0; j < count; j++) {
                    double tm = getOneSortTime(sorts[i], arrays[j], count, errors);
                    time += tm;
//                    std::cout << tm << std::endl;
                }
                res.append(time / (double)count);
                std::cout << " done!";
                if (errors != 0)
                    std::cout << " (" << errors << " ошибок)";
                std::cout << std::endl;
            }
        }
        return res;
    }

    static double getOneSortTime(const mySortList& sort, const myArraySequence<int>& seq, size_t count, size_t& errors) {
        myTimer timer;
        auto sortArray = sort.sortFunc(seq);
        double time = timer.time();

        errors = checkSort(sortArray);

        delete sortArray;
        return time;
    }

    static size_t checkSort(mySequence<int>* sortSeq) {
        size_t res = 0;
        for (size_t j = 1; j < sortSeq->length(); j++) {
            if (sortSeq->operator[](j-1) > sortSeq->operator[](j)) {
                ++res;
                break;
            }
        }
        return res;
    }

    static std::string getTable(const myArraySequence<mySortList>& sorts,
                                const myArraySequence<bool>& compSorts,
                                const myArraySequence<size_t>& sizes,
                                const myArraySequence<myArraySequence<double>>& values) {
        std::string res;
        myArraySequence<size_t> indexes;
        myArraySequence<std::string> strings;
        size_t maxStrLen;
        strings.append(std::string("|") + "sorts");
        strings.append("+");
        maxStrLen = strings[0].length();

        for (size_t i = 0, j = 2; i < compSorts.length(); i++) {
            if (compSorts[i]) {
                indexes.append(i);
                strings.append("|");
                strings[j] += sorts[i].sortName;
                maxStrLen = (strings[j].length() > maxStrLen) ? strings[j].length() : maxStrLen;
                ++j;
            }
        }

        checkSpaces(strings, maxStrLen);
        for (size_t i = 0; i < values.length(); i++) {
            strings[0] += std::to_string(sizes[i]);
            maxStrLen = strings[0].length();

            for (size_t j = 0; j < values[i].length(); j++) {
                strings[j+2] += std::to_string(values[i][j]);
                if (maxStrLen < strings[j+2].length())
                    maxStrLen = strings[j+2].length();
            }
            checkSpaces(strings, maxStrLen);
        }

        for (auto &i : strings) {
            res += i + '\n';
        }

        return res;
    }

    static void checkSpaces(const myArraySequence<std::string>& strArr, size_t& size) {
        for (auto &i : strArr) {
            if (i[0] == '+') {
                while (i.length() < size)
                    i += '-';
                i += '+';
            }
            else {
                while (i.length() < size)
                    i += ' ';
                i += '|';
            }
        }
        size++;
    }

    static void clear() {
        // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
        std::cout << "\x1B[2J\x1B[H";
    }

    static void clearLastRow(int row) {
        // получаем хэндл окна консоли
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

        // получаем данные из буфера вывода консоли
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        // получаем координаты строки для очистки
        COORD cursorCoords = csbi.dwCursorPosition;
        if (cursorCoords.Y == 0)
            return;

        COORD coord = { 0, static_cast<short>(row)};

        GetConsoleScreenBufferInfo(hStdOut, &csbi);
        // заполняем строку пробелами
        SetConsoleCursorPosition(hStdOut, coord);
        std::cout << "1111111111111";
        FillConsoleOutputCharacter(hStdOut, ' ', 80, coord, nullptr);
        // сбрасываем позицию курсора
        SetConsoleCursorPosition(hStdOut, csbi.dwCursorPosition);
    }
};


#endif //BASE_CLASSES_SORTINGMENU_H
