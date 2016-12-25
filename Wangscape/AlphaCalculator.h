#pragma once
#include <vector>
#include <functional>
#include <SFML/Config.hpp>
class AlphaCalculator
{
public:
    typedef std::vector<float> WeightVector;
    typedef std::vector<sf::Uint8> AlphaVector;
    typedef std::function<void(WeightVector&, AlphaVector&)> PixelAlphaCalculator;
    virtual ~AlphaCalculator();
    static void calculatePixelAlphaLinear(WeightVector& weights, AlphaVector& alphas);
    static void calculatePixelAlphaMax(WeightVector& weights, AlphaVector& alphas);
    static void calculatePixelAlphaFunction(WeightVector& weights, AlphaVector& alphas,
                                            std::function<float(float)> fn);
    static PixelAlphaCalculator makeCalculatePixelAlphaPower(float power);
    static PixelAlphaCalculator bindCalculatePixelAlphaFunction(std::function<float(float)> fn);
};

