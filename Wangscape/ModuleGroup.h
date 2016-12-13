#pragma once
#include <noise/noise.h>
#include <vector>
#include <memory>

// Maybe these typedefs should be elsewhere?
typedef noise::module::Module Module;
typedef std::shared_ptr<Module> ModulePtr;

// A helper class to store related noise modules in one place.
//
// The first noise module in the stored vector is used as the
// output, and the other modules in the vector may be used as
// sources. External modules may also be used as sources,
// but this class will not be responsible for deleting them.
class ModuleGroup : public noise::module::Module
{
public:
    typedef std::vector<ModulePtr> ModuleVector;

    ModuleVector modules;

    ModuleGroup();
    ~ModuleGroup();
    virtual int GetSourceModuleCount() const;
    virtual double GetValue(double x, double y, double z) const;
};

