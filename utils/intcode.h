//
// Created by cameron on 12/6/2019.
//

#ifndef AOC2019_INTCODE_H
#define AOC2019_INTCODE_H

#include <vector>
#include <tuple>
#include <queue>

class IntcodeComputer {
private:
    std::vector<int> program;
    int program_counter;
    bool halted = false;
    std::queue<int> input_queue;
    std::queue<int> output_queue;

    std::tuple<int, int, int> parseParameterModes(std::string modes);

public:
    IntcodeComputer()=default;
    explicit IntcodeComputer(std::vector<int> program);
    void runCycle();
    bool isHalted();
    void pushInput(int input);
    bool hasOutput();
    int getNextOutput();
};

#endif //AOC2019_INTCODE_H
