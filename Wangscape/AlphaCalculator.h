#pragma once
#include <vector>
#include <functional>
#include <SFML/Config.hpp>
class AlphaCalculator
{
public:
    AlphaCalculator();
    ~AlphaCalculator();
    static void calculatePixelAlphaLinear(std::vector<float>& weights, std::vector<sf::Uint8>& alphas);
    static void calculatePixelAlphaMax(std::vector<float>& weights, std::vector<sf::Uint8>& alphas);
    static void calculatePixelAlphaFunction(std::vector<float>& weights, std::vector<sf::Uint8>& alphas,
                                     std::function<float(float)> fn);
};

