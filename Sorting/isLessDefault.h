//
// Created by Grisha on 14.07.2021.
//

#ifndef BASE_CLASSES_ISLESSDEFAULT_H
#define BASE_CLASSES_ISLESSDEFAULT_H

namespace sortFuncPrivate {

    template<typename T>
    bool isLessDefault(const T& obj1, const T& obj2) {
        return obj1 < obj2;
    }

    template<typename T>
    bool isTreeSameFunc(const T& obj1, const T& obj2) {
        return false;
    }
}
#endif //BASE_CLASSES_ISLESSDEFAULT_H
