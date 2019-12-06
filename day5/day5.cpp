#include <iostream>

#include "../utils/utils.h"

#include <algorithm>

#include <boost/algorithm/string.hpp>

std::tuple<int, int, int> parseParameterModes(std::string modes) {

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
    int program_input = 1; // Ship input because I am lazy
    while (program_counter < intcode_program.size()) {
        int opcode = intcode_program[program_counter];
        int op1, op2, op3;
        int modes = opcode / 100;
        std::string parameter_modes = std::to_string(modes);
        int instruction = opcode % 100;
        switch (instruction) {
            case 1:
                op1 = intcode_program[program_counter + 1];
                op2 = intcode_program[program_counter + 2];
                op3 = intcode_program[program_counter + 3];
                intcode_program[op3] = intcode_program[op1] + intcode_program[op2];
                program_counter += 4;
                break;
            case 2:
                op1 = intcode_program[program_counter + 1];
                op2 = intcode_program[program_counter + 2];
                op3 = intcode_program[program_counter + 3];
                intcode_program[op3] = intcode_program[op1] * intcode_program[op2];
                program_counter += 4;
                break;
            case 3:
                op1 = intcode_program[program_counter + 1];
                intcode_program[op1] = program_input;
                program_counter += 2;
                break;
            case 4:
                op1 = intcode_program[program_counter + 1];
                std::cout << "[COMPUTER] => " << intcode_program[op1];
                program_counter += 2;
                break;
            case 99:
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
