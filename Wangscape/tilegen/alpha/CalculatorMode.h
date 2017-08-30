#pragma once

#include <map>
#include <string>

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

extern const std::map<std::string, CalculatorMode> calculatorModeByName;

} // namespace alpha
} // namespace tilegen
