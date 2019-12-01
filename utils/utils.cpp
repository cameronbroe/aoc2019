//
// Created by cameron on 11/30/2019.
//

#include <iostream>

#include "utils.h"
#include <fstream>
#include <experimental/filesystem>
#include <string>

namespace aoc_utils {

    std::vector<std::string> read_input(std::string filename) {
        auto lines = std::vector<std::string>();
        std::ifstream file(filename);
        std::string line;
        while(std::getline(file, line)) {
            lines.push_back(line);
        }
        return lines;
    }

    std::string get_file_from_root(std::string day, std::string filename) {
        std::experimental::filesystem::path root_dir;
#ifdef PROJECT_ROOT
        root_dir = std::experimental::filesystem::path(std::string(PROJECT_ROOT));
#else
        root_dir = std::experimental::filesystem::current_path();
#endif
        auto filepath = std::experimental::filesystem::absolute(day + "/" + filename, root_dir);
        return filepath.string();
    }
}