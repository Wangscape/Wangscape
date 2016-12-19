#pragma once
#include <vector>
#include <functional>
#include <SFML/Config.hpp>
class AlphaCalculator
{
public:
    AlphaCalculator();
    ~AlphaCalculator();
    static void calculatePixelAlphaLinear(const std::vector<float>& weights, std::vector<sf::Uint8>& alphas);
    static void calculatePixelAlphaMax(const std::vector<float>& weights, std::vector<sf::Uint8>& alphas);
    static void calculatePixelAlphaFunction(const std::vector<float>& weights, std::vector<sf::Uint8>& alphas,
                                     std::function<float(float)> fn);
};

