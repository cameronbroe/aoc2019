//
// Created by cameron on 11/30/2019.
//

#ifndef AOC2019_UTILS_H
#define AOC2019_UTILS_H

#include <vector>
#include <string>

namespace aoc_utils {
    std::string get_file_from_root(std::string day, std::string filename);
    std::vector<std::string> read_input(std::string filename);
}

#endif //AOC2019_UTILS_H
