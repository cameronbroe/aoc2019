//
// Created by cameron on 12/6/2019.
//

#include "intcode.h"

#include <iostream>
#include <utility>

int charToInt(char c) {
    return c - '0';
}

std::tuple<int, int, int> IntcodeComputer::parseParameterModes(std::string modes) {
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

void IntcodeComputer::runCycle() {
    int opcode = this->program[program_counter];
    int op1, op2, op3;
    int arg1, arg2;
    int modes = opcode / 100;
    auto parameter_modes = parseParameterModes(std::to_string(modes));
    int instruction = opcode % 100;
    switch (instruction) {
        case 1:
            op1 = this->program[program_counter + 1];
            op2 = this->program[program_counter + 2];
            op3 = this->program[program_counter + 3];
            if(std::get<0>(parameter_modes) == 0) {
                arg1 = this->program[op1];
            } else {
                arg1 = op1;
            }

            if(std::get<1>(parameter_modes) == 0) {
                arg2 = this->program[op2];
            } else {
                arg2 = op2;
            }
            this->program[op3] = arg1 + arg2;
            program_counter += 4;
            break;
        case 2:
            op1 = this->program[program_counter + 1];
            op2 = this->program[program_counter + 2];
            op3 = this->program[program_counter + 3];
            if(std::get<0>(parameter_modes) == 0) {
                arg1 = this->program[op1];
            } else {
                arg1 = op1;
            }

            if(std::get<1>(parameter_modes) == 0) {
                arg2 = this->program[op2];
            } else {
                arg2 = op2;
            }

            this->program[op3] = arg1 * arg2;
            program_counter += 4;
            break;
        case 3:
            op1 = this->program[program_counter + 1];
            this->program[op1] = input_queue.front();
            input_queue.pop();
            program_counter += 2;
            break;
        case 4:
            op1 = this->program[program_counter + 1];
            if(std::get<0>(parameter_modes) == 0) {
                arg1 = this->program[op1];
            } else {
                arg1 = op1;
            }
//            std::cout << "[COMPUTER] => " << arg1 << std::endl;
            output_queue.push(arg1);
            program_counter += 2;
            break;
        case 5:
            op1 = this->program[program_counter + 1];
            op2 = this->program[program_counter + 2];
            if(std::get<0>(parameter_modes) == 0) {
                arg1 = this->program[op1];
            } else {
                arg1 = op1;
            }

            if(std::get<1>(parameter_modes) == 0) {
                arg2 = this->program[op2];
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
            op1 = this->program[program_counter + 1];
            op2 = this->program[program_counter + 2];
            if(std::get<0>(parameter_modes) == 0) {
                arg1 = this->program[op1];
            } else {
                arg1 = op1;
            }

            if(std::get<1>(parameter_modes) == 0) {
                arg2 = this->program[op2];
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
            op1 = this->program[program_counter + 1];
            op2 = this->program[program_counter + 2];
            op3 = this->program[program_counter + 3];
            if(std::get<0>(parameter_modes) == 0) {
                arg1 = this->program[op1];
            } else {
                arg1 = op1;
            }

            if(std::get<1>(parameter_modes) == 0) {
                arg2 = this->program[op2];
            } else {
                arg2 = op2;
            }
            if(arg1 < arg2) {
                this->program[op3] = 1;
            } else {
                this->program[op3] = 0;
            }
            program_counter += 4;
            break;
        case 8:
            op1 = this->program[program_counter + 1];
            op2 = this->program[program_counter + 2];
            op3 = this->program[program_counter + 3];
            if(std::get<0>(parameter_modes) == 0) {
                arg1 = this->program[op1];
            } else {
                arg1 = op1;
            }

            if(std::get<1>(parameter_modes) == 0) {
                arg2 = this->program[op2];
            } else {
                arg2 = op2;
            }
            if(arg1 == arg2) {
                this->program[op3] = 1;
            } else {
                this->program[op3] = 0;
            }
            program_counter += 4;
            break;
        case 99:
//            std::cout << "[COMPUTER] => halt" << std::endl;
            halted = true;
            break;
        default:
            std::cerr << "what'd you screw up this time you idiot?" << std::endl;
            exit(1);
    }
}

bool IntcodeComputer::isHalted() {
    return halted;
}

void IntcodeComputer::pushInput(int input) {
    input_queue.push(input);
}

IntcodeComputer::IntcodeComputer(std::vector<int> program)
    : program_counter(0) {
    this->program = std::move(program);
}

bool IntcodeComputer::hasOutput() {
    return !output_queue.empty();
}

int IntcodeComputer::getNextOutput() {
    int output = output_queue.front();
    output_queue.pop();
    return output;
}
