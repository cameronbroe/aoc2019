#include <iostream>

#include "../utils/utils.h"
#include "../utils/intcode.h"

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <unordered_map>

void partOne(std::vector<int64_t> program) {
    std::vector<int> phase_sequences = { 0, 1, 2, 3, 4 };
    std::vector<int> thruster_outputs;

    do {
        auto ampA = IntcodeComputer(program);
        ampA.pushInput(phase_sequences[0]);
        ampA.pushInput(0);
        int ampAOutput = 0;
        while (!ampA.isHalted()) {
            ampA.runCycle();
            if (ampA.hasOutput()) {
                ampAOutput = ampA.getNextOutput();
            }
        }

        auto ampB = IntcodeComputer(program);
        ampB.pushInput(phase_sequences[1]);
        ampB.pushInput(ampAOutput);
        int ampBOutput = 0;
        while (!ampB.isHalted()) {
            ampB.runCycle();
            if (ampB.hasOutput()) {
                ampBOutput = ampB.getNextOutput();
            }
        }

        auto ampC = IntcodeComputer(program);
        ampC.pushInput(phase_sequences[2]);
        ampC.pushInput(ampBOutput);
        int ampCOutput = 0;
        while (!ampC.isHalted()) {
            ampC.runCycle();
            if (ampC.hasOutput()) {
                ampCOutput = ampC.getNextOutput();
            }
        }

        auto ampD = IntcodeComputer(program);
        ampD.pushInput(phase_sequences[3]);
        ampD.pushInput(ampCOutput);
        int ampDOutput = 0;
        while (!ampD.isHalted()) {
            ampD.runCycle();
            if (ampD.hasOutput()) {
                ampDOutput = ampD.getNextOutput();
            }
        }

        auto ampE = IntcodeComputer(program);
        ampE.pushInput(phase_sequences[4]);
        ampE.pushInput(ampDOutput);
        int ampEOutput = 0;
        while (!ampE.isHalted()) {
            ampE.runCycle();
            if (ampE.hasOutput()) {
                ampEOutput = ampE.getNextOutput();
            }
        }
        thruster_outputs.emplace_back(ampEOutput);
    } while(std::next_permutation(phase_sequences.begin(), phase_sequences.end()));
    std::cout << "part 1 answer: " << *std::max_element(thruster_outputs.begin(), thruster_outputs.end()) << std::endl;
}

void partTwo(std::vector<int64_t> program) {
    std::vector<int> phase_sequences = { 5, 6, 7, 8, 9 };
    std::vector<int> thruster_outputs;

    do {
        std::unordered_map<char, int> amplifierInput;
        amplifierInput['A'] = 0;

        auto amplifiersA = IntcodeComputer(program);
        amplifiersA.pushInput(phase_sequences[0]);
        auto amplifiersB = IntcodeComputer(program);
        amplifiersB.pushInput(phase_sequences[1]);
        auto amplifiersC = IntcodeComputer(program);
        amplifiersC.pushInput(phase_sequences[2]);
        auto amplifiersD = IntcodeComputer(program);
        amplifiersD.pushInput(phase_sequences[3]);
        auto amplifiersE = IntcodeComputer(program);
        amplifiersE.pushInput(phase_sequences[4]);

        while (!(amplifiersA.isHalted() && amplifiersB.isHalted() && amplifiersC.isHalted() &&
                 amplifiersD.isHalted() && amplifiersE.isHalted())) {
            amplifiersA.pushInput(amplifierInput['A']);
            while (!amplifiersA.isHalted()) {
                amplifiersA.runCycle();
                if (amplifiersA.hasOutput()) {
                    amplifierInput['B'] = amplifiersA.getNextOutput();
                    break;
                }
            }

            amplifiersB.pushInput(amplifierInput['B']);
            while (!amplifiersB.isHalted()) {
                amplifiersB.runCycle();
                if (amplifiersB.hasOutput()) {
                    amplifierInput['C'] = amplifiersB.getNextOutput();
                    break;
                }
            }

            amplifiersC.pushInput(amplifierInput['C']);
            while (!amplifiersC.isHalted()) {
                amplifiersC.runCycle();
                if (amplifiersC.hasOutput()) {
                    amplifierInput['D'] = amplifiersC.getNextOutput();
                    break;
                }
            }

            amplifiersD.pushInput(amplifierInput['D']);
            while (!amplifiersD.isHalted()) {
                amplifiersD.runCycle();
                if (amplifiersD.hasOutput()) {
                    amplifierInput['E'] = amplifiersD.getNextOutput();
                    break;
                }
            }

            amplifiersE.pushInput(amplifierInput['E']);
            while (!amplifiersE.isHalted()) {
                amplifiersE.runCycle();
                if (amplifiersE.hasOutput()) {
                    amplifierInput['A'] = amplifiersE.getNextOutput();
                    break;
                }
            }
        }
        thruster_outputs.emplace_back(amplifierInput['A']);
    } while(std::next_permutation(phase_sequences.begin(), phase_sequences.end()));
    std::cout << "part 2 answer: " << *std::max_element(thruster_outputs.begin(), thruster_outputs.end()) << std::endl;
}

int main() {
    auto input = aoc_utils::read_input(aoc_utils::get_file_from_root("day7", "input.txt"));
    std::string intcode_program_full = input[0];
    std::vector<std::string> intcode_program_split;
    boost::split(intcode_program_split, intcode_program_full, [](char c) {
        return c == ',';
    });
    std::vector<int64_t> program;
    std::for_each(intcode_program_split.begin(), intcode_program_split.end(),
                  [&program](std::string intcode) {
                      program.push_back(std::stoi(intcode));
                  });
    partOne(program);
    partTwo(program);
    return 0;
}
