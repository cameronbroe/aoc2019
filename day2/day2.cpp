#include <iostream>

#include "../utils/utils.h"

#include <iostream>
#include <algorithm>

#include <boost/algorithm/string.hpp>

int main() {
    std::string input_file = aoc_utils::get_file_from_root("day2", "input.txt");
    auto input = aoc_utils::read_input(input_file);
    std::string intcode_program_full = input[0];
    std::vector<std::string> intcode_program_split;
    boost::split(intcode_program_split, intcode_program_full, [](char c) {
        return c == ',';
    });
    std::vector<int> intcode_program_base;
    std::for_each(intcode_program_split.begin(), intcode_program_split.end(),
                  [&intcode_program_base](std::string intcode) {
                      intcode_program_base.push_back(std::stoi(intcode));
                  });
    for(int noun = 0; noun <= 99; noun++) {
        for(int verb = 0; verb <= 99; verb++) {
            std::vector<int> intcode_program = std::vector<int>(intcode_program_base);
            bool is_part_one = (noun == 12 && verb == 2);
            intcode_program[1] = noun;
            intcode_program[2] = verb;
            bool should_halt = false;
            for (int i = 0; i < intcode_program.size(); i += 4) {
                int opcode = intcode_program[i];
                int op1, op2, op3;
                switch (opcode) {
                    case 1:
                        op1 = intcode_program[i + 1];
                        op2 = intcode_program[i + 2];
                        op3 = intcode_program[i + 3];
                        intcode_program[op3] = intcode_program[op1] + intcode_program[op2];
                        break;
                    case 2:
                        op1 = intcode_program[i + 1];
                        op2 = intcode_program[i + 2];
                        op3 = intcode_program[i + 3];
                        intcode_program[op3] = intcode_program[op1] * intcode_program[op2];
                        break;
                    case 99:
                        if(is_part_one) {
                            std::cout << "part 1 answer: " << intcode_program[0] << std::endl;
                        }
                        if(intcode_program[0] == 19690720) {
                            std::cout << "part 2 answer: " << 100 * noun + verb << std::endl;
                        }
                        should_halt = true;
                        goto halt_instruction;
                    default:
                        std::cerr << "what'd you screw up this time you idiot?" << std::endl;
                        exit(1);
                }
halt_instruction:
                if(should_halt)
                    break;
            }
        }
    }
    return 0;
}
