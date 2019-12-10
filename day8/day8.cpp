#include <iostream>

#include "../utils/utils.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <boost/range/algorithm.hpp>

int charToInt(char c) { return c - '0'; }

struct ImageLayer {
    std::vector<int> data;
    int width;
    int height;

    int countOfDigit(int digit) {
        int count = 0;
        for(const auto& p: data) {
            if(p == digit) {
                count++;
            }
        }
        return count;
    }
};

int main() {
    auto input = aoc_utils::read_input(aoc_utils::get_file_from_root("day8", "input.txt"));
    auto imageStr = input[0];
    auto image = std::vector<int>();
    std::for_each(imageStr.begin(), imageStr.end(), [&image](auto c) {
       image.emplace_back(charToInt(c));
    });
    int image_width = 25, image_height = 6;
    // Iterating through each layer and collecting into a vector
    std::vector<ImageLayer> layers;
    for(int i = 0; i < image.size(); i += (image_width * image_height)) {
        std::vector<int> layer = std::vector<int>(image.begin() + i, (image.begin() + i) + (image_width * image_height));
        ImageLayer newLayer;
        newLayer.height = image_height;
        newLayer.width = image_width;
        newLayer.data = std::vector<int>(layer);
        layers.emplace_back(newLayer);
    }
    auto layerWithLeastZeroes = *std::min_element(layers.begin(), layers.end(), [](auto a, auto b) {
        return a.countOfDigit(0) < b.countOfDigit(0);
    });
    std::cout << "part 1 answer: " << layerWithLeastZeroes.countOfDigit(1) * layerWithLeastZeroes.countOfDigit(2) << std::endl;

    ImageLayer renderedLayer;
    renderedLayer.width = image_width;
    renderedLayer.height = image_height;
    renderedLayer.data.reserve(image_width * image_height);
    for(int i = 0; i < (image_width * image_height); i++) {
        for(const auto& l : layers) {
            if(l.data[i] != 2) {
                renderedLayer.data.emplace_back(l.data[i]);
                break;
            }
        }
    }
    std::cout << "part 2 answer (below): " << std::endl;
    for(int i = 0; i < renderedLayer.data.size(); i++) {
        if(i > 0 && i % renderedLayer.width == 0) {
            std::cout << std::endl;
        }
        if(renderedLayer.data[i] == 1)
            std::cout << renderedLayer.data[i];
        else
            std::cout << " ";
    }
    return 0;
}
