//
// Created by shguan on 7/21/23.
//

//#ifndef ML_CPP_UTILS_H
//#define ML_CPP_UTILS_H

#include <iostream>

void print_something();

template <typename T>
T add(T i, T j) {
    std::cout<< "This is the example of template function!" << std::endl;
    return i + j;
};

//#endif //ML_CPP_UTILS_H
