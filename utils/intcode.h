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
    std::vector<int64_t> program;
    int program_counter;
    bool halted = false;
    std::queue<int64_t> input_queue;
    std::queue<int64_t> output_queue;
    int relative_base;

    std::tuple<int, int, int> parseParameterModes(std::string modes);

public:
    IntcodeComputer()=default;
    explicit IntcodeComputer(std::vector<int64_t> program);
    void runCycle();
    bool isHalted();
    void pushInput(int64_t input);
    bool hasOutput();
    int64_t getNextOutput();
};

#endif //AOC2019_INTCODE_H
