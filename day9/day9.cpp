#include <iostream>

#include "../utils/utils.h"
#include "../utils/intcode.h"

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <unordered_map>

int main() {
    auto input = aoc_utils::read_input(aoc_utils::get_file_from_root("day9", "input.txt"));
    std::string intcode_program_full = input[0];
    std::vector<std::string> intcode_program_split;
    boost::split(intcode_program_split, intcode_program_full, [](char c) {
        return c == ',';
    });
    std::vector<int64_t> program;
    std::for_each(intcode_program_split.begin(), intcode_program_split.end(),
                  [&program](std::string intcode) {
                      program.push_back(std::stoll(intcode));
                  });
    std::cout << "COMPUTER 1 = PART 1 <-> COMPUTER 2 = PART 2" << std::endl;
    auto computer1 = IntcodeComputer(program);
    computer1.pushInput(1);
    while(!computer1.isHalted()) {
        computer1.runCycle();
        while(computer1.hasOutput()) {
            int64_t output = computer1.getNextOutput();
            std::cout << "[COMPUTER 1] => " << std::to_string(output) << std::endl;
        }
    }

    auto computer2 = IntcodeComputer(program);
    computer2.pushInput(2);
    while(!computer2.isHalted()) {
        computer2.runCycle();
        while(computer2.hasOutput()) {
            int64_t output = computer2.getNextOutput();
            std::cout << "[COMPUTER 2] => " << std::to_string(output) << std::endl;
        }
    }
    return 0;
}

