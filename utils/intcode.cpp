//
// Created by cameron on 12/6/2019.
//

#include "intcode.h"

#include <iostream>
#include <utility>

int64_t charToInt(char c) {
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
    int64_t opcode = this->program[program_counter];
    int64_t op1 = 0, op2 = 0, op3 = 0;
    int64_t arg1 = 0, arg2 = 0, arg3 = 0;
    int64_t modes = opcode / 100;
    auto parameter_modes = parseParameterModes(std::to_string(modes));
    int64_t instruction = opcode % 100;
    switch (instruction) {
        case 1: // add
            op1 = this->program[program_counter + 1];
            op2 = this->program[program_counter + 2];
            op3 = this->program[program_counter + 3];
            if(std::get<0>(parameter_modes) == 0) {
                arg1 = this->program[op1];
            } else if(std::get<0>(parameter_modes) == 1) {
                arg1 = op1;
            } else {
                arg1 = this->program[relative_base + op1];
            }

            if(std::get<1>(parameter_modes) == 0) {
                arg2 = this->program[op2];
            } else if(std::get<1>(parameter_modes) == 1) {
                arg2 = op2;
            } else {
                arg2 = this->program[relative_base + op2];
            }

            if(std::get<2>(parameter_modes) == 2) {
                arg3 = relative_base + op3;
            } else {
                arg3 = op3;
            }

            this->program[arg3] = arg1 + arg2;
            program_counter += 4;
            break;
        case 2: // multiply
            op1 = this->program[program_counter + 1];
            op2 = this->program[program_counter + 2];
            op3 = this->program[program_counter + 3];
            if(std::get<0>(parameter_modes) == 0) {
                arg1 = this->program[op1];
            } else if(std::get<0>(parameter_modes) == 1) {
                arg1 = op1;
            } else {
                arg1 = this->program[relative_base + op1];
            }

            if(std::get<1>(parameter_modes) == 0) {
                arg2 = this->program[op2];
            } else if(std::get<1>(parameter_modes) == 1) {
                arg2 = op2;
            } else {
                arg2 = this->program[relative_base + op2];
            }

            if(std::get<2>(parameter_modes) == 2) {
                arg3 = relative_base + op3;
            } else {
                arg3 = op3;
            }

            this->program[arg3] = arg1 * arg2;
            program_counter += 4;
            break;
        case 3: // read input
            op1 = this->program[program_counter + 1];
            if(std::get<0>(parameter_modes) == 2) {
                this->program[relative_base + op1] = input_queue.front();
            } else {
                this->program[op1] = input_queue.front();
            }
            input_queue.pop();
            program_counter += 2;
            break;
        case 4: // output
            op1 = this->program[program_counter + 1];
            if(std::get<0>(parameter_modes) == 0) {
                arg1 = this->program[op1];
            } else if(std::get<0>(parameter_modes) == 1) {
                arg1 = op1;
            } else {
                arg1 = this->program[relative_base + op1];
            }

//            std::cout << "[COMPUTER] => " << arg1 << std::endl;
            output_queue.emplace(arg1);
//            std::cerr << "DBG: queue size: " << output_queue.size() << std::endl;
            program_counter += 2;
            break;
        case 5: // jump ne zero
            op1 = this->program[program_counter + 1];
            op2 = this->program[program_counter + 2];
            if(std::get<0>(parameter_modes) == 0) {
                arg1 = this->program[op1];
            } else if(std::get<0>(parameter_modes) == 1) {
                arg1 = op1;
            } else {
                arg1 = this->program[relative_base + op1];
            }

            if(std::get<1>(parameter_modes) == 0) {
                arg2 = this->program[op2];
            } else if(std::get<1>(parameter_modes) == 1) {
                arg2 = op2;
            } else {
                arg2 = this->program[relative_base + op2];
            }

            if(arg1 != 0) {
                program_counter = arg2;
            } else {
                program_counter += 3;
            }
            break;
        case 6: // jump eq zero
            op1 = this->program[program_counter + 1];
            op2 = this->program[program_counter + 2];
            if(std::get<0>(parameter_modes) == 0) {
                arg1 = this->program[op1];
            } else if(std::get<0>(parameter_modes) == 1) {
                arg1 = op1;
            } else {
                arg1 = this->program[relative_base + op1];
            }

            if(std::get<1>(parameter_modes) == 0) {
                arg2 = this->program[op2];
            } else if(std::get<1>(parameter_modes) == 1) {
                arg2 = op2;
            } else {
                arg2 = this->program[relative_base + op2];
            }

            if(arg1 == 0) {
                program_counter = arg2;
            } else {
                program_counter += 3;
            }
            break;
        case 7: // less than
            op1 = this->program[program_counter + 1];
            op2 = this->program[program_counter + 2];
            op3 = this->program[program_counter + 3];
            if(std::get<0>(parameter_modes) == 0) {
                arg1 = this->program[op1];
            } else if(std::get<0>(parameter_modes) == 1) {
                arg1 = op1;
            } else {
                arg1 = this->program[relative_base + op1];
            }

            if(std::get<1>(parameter_modes) == 0) {
                arg2 = this->program[op2];
            } else if(std::get<1>(parameter_modes) == 1) {
                arg2 = op2;
            } else {
                arg2 = this->program[relative_base + op2];
            }

            if(std::get<2>(parameter_modes) == 2) {
                arg3 = relative_base + op3;
            } else {
                arg3 = op3;
            }

            if(arg1 < arg2) {
                this->program[arg3] = 1;
            } else {
                this->program[arg3] = 0;
            }
            program_counter += 4;
            break;
        case 8: // equal
            op1 = this->program[program_counter + 1];
            op2 = this->program[program_counter + 2];
            op3 = this->program[program_counter + 3];
            if(std::get<0>(parameter_modes) == 0) {
                arg1 = this->program[op1];
            } else if(std::get<0>(parameter_modes) == 1) {
                arg1 = op1;
            } else {
                arg1 = this->program[relative_base + op1];
            }

            if(std::get<1>(parameter_modes) == 0) {
                arg2 = this->program[op2];
            } else if(std::get<1>(parameter_modes) == 1) {
                arg2 = op2;
            } else {
                arg2 = this->program[relative_base + op2];
            }

            if(std::get<2>(parameter_modes) == 2) {
                arg3 = relative_base + op3;
            } else {
                arg3 = op3;
            }

            if(arg1 == arg2) {
                this->program[arg3] = 1;
            } else {
                this->program[arg3] = 0;
            }
            program_counter += 4;
            break;
        case 9: // add to relative
            op1 = this->program[program_counter + 1];
            if(std::get<0>(parameter_modes) == 0) {
                arg1 = this->program[op1];
            } else if(std::get<0>(parameter_modes) == 1) {
                arg1 = op1;
            } else {
                arg1 = this->program[relative_base + op1];
            }

            relative_base += arg1;
            program_counter += 2;
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

void IntcodeComputer::pushInput(int64_t input) {
    input_queue.push(input);
}

IntcodeComputer::IntcodeComputer(std::vector<int64_t> program)
    : program_counter(0) {
    this->program.reserve(1024 * 1024);
    for(int i = 0; i < program.size(); i++) {
        this->program[i] = program[i];
    }
    this->relative_base = 0;
}

bool IntcodeComputer::hasOutput() {
    return !output_queue.empty();
}

int64_t IntcodeComputer::getNextOutput() {
    auto output = output_queue.front();
    output_queue.pop();
    return output;
}
