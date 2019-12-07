//
// Created by cameron on 12/6/2019.
//

#ifndef AOC2019_INTCODE_H
#define AOC2019_INTCODE_H

#include <vector>
#include <tuple>

class IntcodeComputer {
private:
    std::vector<int> program;
    int program_counter;
    bool halted = false;

    std::tuple<int, int, int> parseParameterModes(std::string modes);

public:
    void runCycle();
    bool isHalted();
};

#endif //AOC2019_INTCODE_H
