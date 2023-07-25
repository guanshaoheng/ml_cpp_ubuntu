//
// Created by shguan on 7/21/23.
//

#include <pybind11/pybind11.h>
#include "./include/utils.h"
#include <iostream>

//int main(){
//    std::cout << add<int>(1, 1) << std:: endl;
//    std::cout << add<double>(1.1, 1.1) << std:: endl;
//    std::cout << add<std::string>("Hello ", "shguan") << std:: endl;
//
//    print_something();
//
//    return 0;
//}

namespace py= pybind11;
PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add<int>, "A function that adds two numbers");
    m.def("add", &add<double>, "A function that adds two numbers");
    m.def("add", &add<float>, "A function that adds two numbers");
    m.def("add", &add<std::string>, "A function that adds two numbers");

    // 第一个字符串就是在python中调用的名字！！
    m.def("print_something", &print_something, "Print something");
}