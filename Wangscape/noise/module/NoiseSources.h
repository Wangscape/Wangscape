#pragma once
#include <string>
#include <vector>
#include <boost/optional.hpp>

namespace noise
{
namespace module
{

struct NoiseSources
{
    boost::optional<std::vector<std::string>> sourceModules;
    boost::optional<std::string> controlModule;
    boost::optional<std::vector<std::string>> displaceModules;
};

} // namespace noise
} // namespace module
