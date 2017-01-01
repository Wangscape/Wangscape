#pragma once
#include <vector>
#include <functional>
#include <SFML/Config.hpp>

class AlphaCalculatorBase
{
public:
    typedef std::vector<float> Weights;
    typedef std::vector<sf::Uint8> Alphas;

    virtual ~AlphaCalculatorBase() = default;
    void calculateAlphas(Weights& weights, Alphas& alphas) const;
protected:
    virtual void calculateAlphasAux(Weights& weights, Alphas& alphas) const = 0;
};

