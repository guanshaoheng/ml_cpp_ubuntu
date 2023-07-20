//
// Created by shguan on 7/20/23.
//

#ifndef ML_CPP_UTILS_H
#define ML_CPP_UTILS_H

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;


std::string get_cwd()
{
//    std::cout << "Current path is " << std::filesystem::current_path() << '\n'; // (1)
//    fs::current_path(fs::temp_directory_path()); // (3)
//    std::cout << "Current path is " << fs::current_path() << '\n';

    return std::filesystem::current_path();
}

#endif //ML_CPP_UTILS_H
