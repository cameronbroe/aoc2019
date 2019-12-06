#include <iostream>

#include "../utils/utils.h"

#include <algorithm>

#include <boost/algorithm/string.hpp>

/*
 * For part 1, set the following variable to 1
 * For part 2, set the following variable to 5
 * Output is STDOUT
 */
int program_input = 5;

int charToInt(char c) {
    return c - '0';
}

std::tuple<int, int, int> parseParameterModes(std::string modes) {
    if(modes.length() == 1) {
        return std::make_tuple(charToInt(modes[0]), 0, 0);
    }
    if(modes.length() == 2) {
        return std::make_tuple(charToInt(modes[1]), charToInt(modes[0]), 0);
    }
    if(modes.length() == 3) {
        return std::make_tuple(charToInt(modes[2]), charToInt(modes[1]), charToInt(modes[0]));
    }
    return std::make_tuple(0, 0, 0);
}

int main() {
    std::string input_file = aoc_utils::get_file_from_root("day5", "input.txt");
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
    std::vector<int> intcode_program = std::vector<int>(intcode_program_base);
    bool should_halt = false;
    int program_counter = 0;
    while (program_counter < intcode_program.size()) {
        int opcode = intcode_program[program_counter];
        int op1, op2, op3;
        int arg1, arg2;
        int modes = opcode / 100;
        auto parameter_modes = parseParameterModes(std::to_string(modes));
        int instruction = opcode % 100;
        switch (instruction) {
            case 1:
                op1 = intcode_program[program_counter + 1];
                op2 = intcode_program[program_counter + 2];
                op3 = intcode_program[program_counter + 3];
                if(std::get<0>(parameter_modes) == 0) {
                    arg1 = intcode_program[op1];
                } else {
                    arg1 = op1;
                }

                if(std::get<1>(parameter_modes) == 0) {
                    arg2 = intcode_program[op2];
                } else {
                    arg2 = op2;
                }
                intcode_program[op3] = arg1 + arg2;
                program_counter += 4;
                break;
            case 2:
                op1 = intcode_program[program_counter + 1];
                op2 = intcode_program[program_counter + 2];
                op3 = intcode_program[program_counter + 3];
                if(std::get<0>(parameter_modes) == 0) {
                    arg1 = intcode_program[op1];
                } else {
                    arg1 = op1;
                }

                if(std::get<1>(parameter_modes) == 0) {
                    arg2 = intcode_program[op2];
                } else {
                    arg2 = op2;
                }

                intcode_program[op3] = arg1 * arg2;
                program_counter += 4;
                break;
            case 3:
                op1 = intcode_program[program_counter + 1];
                intcode_program[op1] = program_input;
                program_counter += 2;
                break;
            case 4:
                op1 = intcode_program[program_counter + 1];
                if(std::get<0>(parameter_modes) == 0) {
                    arg1 = intcode_program[op1];
                } else {
                    arg1 = op1;
                }
                std::cout << "[COMPUTER] => " << arg1 << std::endl;
                program_counter += 2;
                break;
            case 5:
                op1 = intcode_program[program_counter + 1];
                op2 = intcode_program[program_counter + 2];
                if(std::get<0>(parameter_modes) == 0) {
                    arg1 = intcode_program[op1];
                } else {
                    arg1 = op1;
                }

                if(std::get<1>(parameter_modes) == 0) {
                    arg2 = intcode_program[op2];
                } else {
                    arg2 = op2;
                }
                if(arg1 != 0) {
                    program_counter = arg2;
                } else {
                    program_counter += 3;
                }
                break;
            case 6:
                op1 = intcode_program[program_counter + 1];
                op2 = intcode_program[program_counter + 2];
                if(std::get<0>(parameter_modes) == 0) {
                    arg1 = intcode_program[op1];
                } else {
                    arg1 = op1;
                }

                if(std::get<1>(parameter_modes) == 0) {
                    arg2 = intcode_program[op2];
                } else {
                    arg2 = op2;
                }
                if(arg1 == 0) {
                    program_counter = arg2;
                } else {
                    program_counter += 3;
                }
                break;
            case 7:
                op1 = intcode_program[program_counter + 1];
                op2 = intcode_program[program_counter + 2];
                op3 = intcode_program[program_counter + 3];
                if(std::get<0>(parameter_modes) == 0) {
                    arg1 = intcode_program[op1];
                } else {
                    arg1 = op1;
                }

                if(std::get<1>(parameter_modes) == 0) {
                    arg2 = intcode_program[op2];
                } else {
                    arg2 = op2;
                }
                if(arg1 < arg2) {
                    intcode_program[op3] = 1;
                } else {
                    intcode_program[op3] = 0;
                }
                program_counter += 4;
                break;
            case 8:
                op1 = intcode_program[program_counter + 1];
                op2 = intcode_program[program_counter + 2];
                op3 = intcode_program[program_counter + 3];
                if(std::get<0>(parameter_modes) == 0) {
                    arg1 = intcode_program[op1];
                } else {
                    arg1 = op1;
                }

                if(std::get<1>(parameter_modes) == 0) {
                    arg2 = intcode_program[op2];
                } else {
                    arg2 = op2;
                }
                if(arg1 == arg2) {
                    intcode_program[op3] = 1;
                } else {
                    intcode_program[op3] = 0;
                }
                program_counter += 4;
                break;
            case 99:
                std::cout << "[COMPUTER] => halt" << std::endl;
                should_halt = true;
                break;
            default:
                std::cerr << "what'd you screw up this time you idiot?" << std::endl;
                exit(1);
        }
        if(should_halt)
            break;
    }
    return 0;
}
