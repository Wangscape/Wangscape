#pragma once

#include <unordered_map>

namespace tilegen
{
namespace alpha
{

enum class CalculatorMode
{
    Max,
    Linear,
    TopTwo,
    Dither
};

extern const std::unordered_map<std::string, CalculatorMode> calculatorModeByName;

} // namespace alpha
} // namespace tilegen
