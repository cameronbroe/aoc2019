#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <boost/assert.hpp>

int charToInt(char c) {
    return c - '0';
}

bool validatePartOneAdjacent(std::string passwordStr) {
    // Check if there is a double adjacent digit
    bool hasDoubleAdjacent = false;
    for(int i = 0; i < passwordStr.length() - 1; i++) {
        if(charToInt(passwordStr[i]) == charToInt(passwordStr[i+1])) {
            hasDoubleAdjacent = true;
        }
    }
    return hasDoubleAdjacent;
}

bool validatePartTwoAdjacent(std::string passwordStr) {
    auto occurrenceCounts = std::unordered_map<int, int>();
    for(int i = 0; i <= 9; i++) {
        occurrenceCounts[i] = 0;
    }
    for(auto& c : passwordStr) {
        occurrenceCounts[charToInt(c)] = occurrenceCounts[charToInt(c)] + 1;
    }

    return std::any_of(occurrenceCounts.begin(), occurrenceCounts.end(), [](auto& pair) {
        return pair.second == 2;
    });
}

bool isValidPassword(int password, bool isPartOne) {
    // Check if 6 digit number
    std::string passwordStr = std::to_string(password);
    if(passwordStr.length() != 6) {
        return false;
    }

    // If part one, naively check for double adjacent
    if(isPartOne) {
        if(!validatePartOneAdjacent(passwordStr)) {
            return false;
        }
    } else {
        if(!validatePartTwoAdjacent(passwordStr)) {
            return false;
        }
    }

    // Check that there are no descending digits
    for(int i = 0; i < passwordStr.length() - 1; i++) {
        if(charToInt(passwordStr[i]) > charToInt(passwordStr[i+1])) {
            return false;
        }
    }

    return true;
}

int main() {
    assert(isValidPassword(111111, true));
    assert(!isValidPassword(223450, true));
    assert(!isValidPassword(123789, true));
    assert(isValidPassword(112233, false));
    assert(!isValidPassword(123444, false));
    assert(isValidPassword(111122, false));

    int rangeStart = 272091;
    int rangeEnd = 815432;
    int partOneValidCount = 0;
    int partTwoValidCount = 0;
    for(int i = rangeStart; i <= rangeEnd; i++) {
        if(isValidPassword(i, true)) {
            partOneValidCount++;
        }

        if(isValidPassword(i, false)) {
            partTwoValidCount++;
        }
    }
    std::cout << "part 1 answer: " << partOneValidCount << std::endl;
    std::cout << "part 2 answer: " << partTwoValidCount << std::endl;
    return 0;
}