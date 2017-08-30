#include "CalculatorMode.h"

namespace tilegen
{
namespace alpha
{

namespace
{


}

const std::map<std::string, CalculatorMode> calculatorModeByName = []()
{
    std::map<std::string, CalculatorMode> mapping;
    mapping.insert(std::make_pair(std::string("Max"), CalculatorMode::Max));
    mapping.insert(std::make_pair(std::string("Linear"), CalculatorMode::Linear));
    mapping.insert(std::make_pair(std::string("TopTwo"), CalculatorMode::TopTwo));
    mapping.insert(std::make_pair(std::string("Dither"), CalculatorMode::Dither));
    return mapping;
}();

} // namespace alpha
} // namespace tilegen
