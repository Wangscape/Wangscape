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

    void setXDisplaceModule(std::string module)
    {
        setDisplaceModuleImp<0>(module);
    }
    void setYDisplaceModule(std::string module)
    {
        setDisplaceModuleImp<1>(module);
    }
    void setZDisplaceModule(std::string module)
    {
        setDisplaceModuleImp<2>(module);
    }
private:
    template<int dimension>
    void setDisplaceModuleImp(std::string module)
    {
        if (!displaceModules)
            displaceModules.emplace(3, "");
        displaceModules.get()[dimension] = module;
    }
};

} // namespace noise
} // namespace module
