//
// Created by Grisha on 04.09.2021.
//

#ifndef BASE_CLASSES_SORTINGMENU_H
#define BASE_CLASSES_SORTINGMENU_H

#include "../allSorts.h"

class mySortMenuClass {
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
                        mySortList{"SheikerSort", SheikerSort, SheikerSort},
                        mySortList{"ShellSort", ShellSort, ShellSort}
                };

        myArraySequence<myArraySequence<int>*> memory;
        myArraySequence<bool> compareArray;


        size_t state;

        for (size_t i = 0; i < allSorts.length(); i++) {
            compareArray.append(false);
        }

        while (true) {
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
        mySequence<int>& (*sortFunc)(mySequence<int>& sequence) = nullptr;
        mySequence<int>& (*sortFuncIndex)(mySequence<int>& sequence, size_t from, size_t to) = nullptr;
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
    static void getArray(myArraySequence<myArraySequence<T>*>& memory, T (*randomFunc)()) {
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
    static void checkArray(myArraySequence<myArraySequence<T>*>& memory, T (*randFunc)()) {
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
    static void printArray(myArraySequence<myArraySequence<T>*>& memory) {
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
    static void swapArray(myArraySequence<myArraySequence<T>*>& memory) {
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
    static void deleteArray(myArraySequence<myArraySequence<T>*>& memory) {
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
    static void editArray(myArraySequence<myArraySequence<T>*> memory, T (*randFunc)()) {
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

            if (state > 7 || state == 0) {
                stateError();
                continue;
            }

            if (state == 7)
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
                    removeIndexItem(*memory[index]);
                    break;
                case 5:
                    swapIndexItem(*memory[index]);
                    break;
                case 6:
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
                  "\t4: Удалить один элемент из массива." << std::endl <<
                  "\t5: Поменять элементы в массиве местами." << std::endl <<
                  "\t6: Перемешать массив" << std::endl <<
                  "\t7: Выход из редактирования массива" << std::endl;
    }

    template<typename T>
    static void getIndexItem(const myArraySequence<T>& sequence) {
        if (sequence.length() == 0) {
            std::cout << "Пустой массив!" << std::endl;
            return;
        }

        std::cout << "В массиве храниться \"" << sequence.length() << "\" элементов. ";
        std::cout << "Введите индекс элемента" << std::endl << ": ";
        size_t index;
        std::cin >> index;
        if (index >= sequence.length()) {
            std::cout << "Индекс за пределами массива!" << std::endl;
            return;
        }

        std::cout << sequence[index] << std::endl;
    }

    template<typename T>
    static void removeIndexItem(myArraySequence<T>& sequence) {
        if (sequence.length() == 0) {
            std::cout << "Пустой массив!" << std::endl;
            return;
        }

        std::cout << "В массиве храниться \"" << sequence.length() << "\" элементов. ";
        std::cout << "Введите индекс элемента" << std::endl << ": ";
        size_t index;
        std::cin >> index;
        if (index >= sequence.length()) {
            std::cout << "Индекс за пределами массива!" << std::endl;
            return;
        }

        sequence.pop(index);
    }

    template<typename T>
    static void swapIndexItem(myArraySequence<T>& sequence) {
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
            std::cout << "Индекс за пределами массива!" << std::endl;
            return;
        }

        std::cout << "Введите индекс второго элемента" << std::endl << ": ";
        std::cin >> index2;
        if (index2 >= sequence.length()) {
            std::cout << "Индекс за пределами массива!" << std::endl;
            return;
        }

        if (index1 == index2) {
            std::cout << "Индексы совпадают!" << std::endl;
            return;
        }

        sequence.swap(index1, index2);
    }

    static size_t getRandomIndex(size_t maxIndex) {
        return static_cast<size_t>(random())%maxIndex;
    }

    template<typename T>
    static void mixSequence(myArraySequence<T>& sequence) {
        for (size_t i = 0; i < sequence.length(); i++) {
            sequence.swap(getRandomIndex(sequence.length()), getRandomIndex(sequence.length()));
        }
    }

    template<typename T>
    static void copyArray(myArraySequence<myArraySequence<T>*>& memory) {
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

        memory.pop(index);
        std::cout << "Массив скопирован." << std::endl;
    }

    //3
    template<typename T>
    static void sortSequence(myArraySequence<myArraySequence<T>*> memory, const myArraySequence<mySortList>& sorts) {
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
            sorts[indexSort].sortFuncIndex(*memory[index], indexFrom, indexTo);
            std::cout << "Массив отсортирован." << std::endl;
            return;
        }

        ShellSortMenu(*memory[index], indexFrom, indexTo);
        std::cout << "Массив отсортирован." << std::endl;

    }

    template<typename T>
    static void ShellSortMenu(myArraySequence<T>& sequence, size_t indexFrom, size_t indexTo) {
        std::cout << "Хотите задать вручную интервалы для ShellSort? (0 - нет, 1 - да)" << std::endl;
        size_t state = 2;
        while (state > 1) {
            std::cout << ": ";
            std::cin >> state;
            if (state > 1)
                stateError();
        }

        if (state == 0) {
            ShellSort(sequence, indexFrom, indexTo);
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

        ShellSort(sequence, intervals, indexFrom, indexTo);
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
};


#endif //BASE_CLASSES_SORTINGMENU_H
