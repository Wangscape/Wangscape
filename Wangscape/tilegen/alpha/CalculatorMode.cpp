#include "CalculatorMode.h"

namespace tilegen
{
namespace alpha
{

const std::unordered_map<std::string, CalculatorMode> calculatorModeByName{
    {"Max", CalculatorMode::Max},
    {"Linear", CalculatorMode::Linear},
    {"TopTwo", CalculatorMode::TopTwo},
    {"Dither", CalculatorMode::Dither}
};

} // namespace alpha
} // namespace tilegen
