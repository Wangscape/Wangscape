#pragma once
#include <vector>
#include <functional>
#include <SFML/Config.hpp>

namespace tilegen
{
namespace alpha
{

class CalculatorBase
{
public:
    typedef std::vector<double> Weights;
    typedef std::vector<sf::Uint8> Alphas;

    CalculatorBase();
    virtual ~CalculatorBase() = default;

    void updateAlphas(const Weights& weights);
    const Alphas& getAlphas() const;
protected:
    // Implement this method to define a new Calculator.
    // The method must set values in mAlphas which sum to 255.
    // The method must not change the length of mAlphas.
    virtual void updateAlphasAux(const Weights& weights) = 0;
    void zeroAlphas();
    sf::Uint8& getAlpha(size_t index);
private:
    Alphas mAlphas;
};


} // namespace alpha
} // namespace tilegen
