#include <iostream>

#include "../utils/utils.h"

#include <iostream>
#include <algorithm>

int main() {
    std::cout << "AOC 2019 Day 1" << std::endl;
    auto input = aoc_utils::read_input(aoc_utils::get_file_from_root("day1", "input.txt"));
    int64_t sum_of_fuel_required = 0;
    std::for_each(input.begin(), input.end(), [&sum_of_fuel_required](std::string line) {
        int mass = std::stoi(line);
        int fuel_required = (mass / 3)  - 2;
        sum_of_fuel_required += fuel_required;
    });
    std::cout << "fuel required (part 1): " << sum_of_fuel_required << std::endl;
    int64_t part2_fuel = 0;
    std::for_each(input.begin(), input.end(), [&part2_fuel](std::string line) {
        int mass = std::stoi(line);
        int fuel_required = (mass / 3) - 2;
        part2_fuel += fuel_required;
        while(fuel_required > 0) {
            fuel_required = (fuel_required / 3) - 2;
            if(fuel_required > 0) {
                part2_fuel += fuel_required;
            }
        }
    });
    std::cout << "fuel required (part 2): " << part2_fuel << std::endl;
    return 0;
}