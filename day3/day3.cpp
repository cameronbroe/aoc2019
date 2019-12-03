#include <iostream>

#include "../utils/utils.h"

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/functional/hash.hpp>
#include <boost/unordered_map.hpp>

struct GridPoint {
    int x, y;
public:
    friend std::ostream &operator<<(std::ostream &os, const GridPoint &point) {
        os << "x: " << point.x << " y: " << point.y;
        return os;
    }

    bool operator ==(const GridPoint& rhs) const {
        return (x == rhs.x) && (y == rhs.y);
    }

    friend std::size_t hash_value(GridPoint const& p) {
        std::size_t seed = 0;
        boost::hash_combine(seed, p.x);
        boost::hash_combine(seed, p.y);

        return seed;
    }
};

struct WireStats {
    int wireId, stepCount;
public:
    friend std::ostream &operator<<(std::ostream &os, const WireStats &stats) {
        os << "wireId: " << stats.wireId << " stepCount: " << stats.stepCount;
        return os;
    }

    bool operator ==(const WireStats& rhs) const {
        return wireId == rhs.wireId;
    }
};

void tracePath(int wireId, boost::unordered_map<GridPoint, std::vector<WireStats>> &grid, std::vector<std::string> &path) {
    GridPoint currentPosition{.x = 0, .y = 0};
    int stepCount = 0;
    for(auto& p : path) {
        // Parse path
        char direction = p[0];
        int length = std::stoi(p.substr(1));
        for(int i = 0; i < length; i++) {
            stepCount++;
            switch(direction) {
                case 'U':
                    currentPosition.y++;
                    break;
                case 'D':
                    currentPosition.y--;
                    break;
                case 'R':
                    currentPosition.x++;
                    break;
                case 'L':
                    currentPosition.x--;
                    break;
            }
            WireStats w{.wireId = wireId, .stepCount = stepCount};
            if(std::find(grid[currentPosition].begin(), grid[currentPosition].end(), w) == grid[currentPosition].end()) {
                grid[currentPosition].emplace_back(w);
            }
        }
    }
}

int main() {
    auto input = aoc_utils::read_input(aoc_utils::get_file_from_root("day3", "input.txt"));
    std::vector<std::string> firstWirePath;
    boost::split(firstWirePath, input[0], boost::is_any_of(","));
    std::vector<std::string> secondWirePath;
    boost::split(secondWirePath, input[1], boost::is_any_of(","));

    boost::unordered_map<GridPoint, std::vector<WireStats>> grid;
    std::vector<GridPoint> intersections;

    // Trace wire paths
    tracePath(1, grid, firstWirePath);
    tracePath(2, grid, secondWirePath);
    for(auto& it : grid) {
        auto key = it.first;
        auto value = it.second;
        if(value.size() >= 2) {
            intersections.emplace_back(key);
        }
    }

    int minimumDistance = INT_MAX;
    for(auto& point : intersections) {
        int mDistance = std::abs(0 - point.x) + std::abs(0 - point.y);
        if(mDistance < minimumDistance) {
            minimumDistance = mDistance;
        }
    }
    std::cout << "part 1 answer: " << minimumDistance << std::endl;

    int minimumSteps = INT_MAX;
    for(auto& point : intersections) {
        auto w1 = grid[point][0];
        auto w2 = grid[point][1];
        int steps = w1.stepCount + w2.stepCount;
        if(steps < minimumSteps) {
            minimumSteps = steps;
        }
    }
    std::cout << "part 2 answer: " << minimumSteps << std::endl;
    return 0;
}
