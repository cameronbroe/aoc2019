#include <iostream>

#include "../utils/utils.h"

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <boost/algorithm/string.hpp>

int main() {
    auto input = aoc_utils::read_input(aoc_utils::get_file_from_root("day6", "input.txt"));
    auto orbits = std::unordered_map<std::string, std::string>();
    for(auto& map: input) {
        std::vector<std::string> split;
        boost::split(split, map, boost::is_any_of(")"));
        orbits[split[1]] = split[0];
    }
    int orbit_count = 0;
    std::vector<std::string> keys;
    std::transform(orbits.begin(), orbits.end(), std::back_inserter(keys), [](auto &p) { return p.first; });
    for(auto& o: orbits) {
        std::string currentPlanet = o.second;
        orbit_count++;
        while(std::find(keys.begin(), keys.end(), currentPlanet) != keys.end()) {
            currentPlanet = orbits[currentPlanet];
            orbit_count++;
        }
    }
    std::cout << "part 1 answer: " << orbit_count << std::endl;

    std::string currentPlanetFromYou = orbits["YOU"];
    std::string currentPlanetFromSan = orbits["SAN"];
    std::vector<std::string> youVisited;
    std::vector<std::string> sanVisited;
    while(std::find(keys.begin(), keys.end(), currentPlanetFromYou) != keys.end()) {
        youVisited.emplace_back(currentPlanetFromYou);
        currentPlanetFromYou = orbits[currentPlanetFromYou];
    }
    while(std::find(keys.begin(), keys.end(), currentPlanetFromSan) != keys.end()) {
        sanVisited.emplace_back(currentPlanetFromSan);
        currentPlanetFromSan = orbits[currentPlanetFromSan];
    }

    int inYouNotSan = 0;
    for(auto& p: youVisited) {
        if(std::find(sanVisited.begin(), sanVisited.end(), p) == sanVisited.end()) {
            inYouNotSan++;
        }
    }
    int inSanNotYou = 0;
    for(auto& p: sanVisited) {
        if(std::find(youVisited.begin(), youVisited.end(), p) == youVisited.end()) {
            inSanNotYou++;
        }
    }
    std::cout << "part 2 answer: " << inYouNotSan + inSanNotYou << std::endl;
    return 0;
}