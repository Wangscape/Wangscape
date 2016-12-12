#pragma once
#include <memory>
#include <map>
#include <noise/noise.h>
#include "common.h"
#include "CornerCombinerGroup.h"
#include "Gradient.h"
#include "ModuleGroup.h"
class NoiseModuleManager
{
public:
    typedef noise::module::Module Module;
    typedef std::pair<TerrainID, TerrainID> TerrainIDPair;
    NoiseModuleManager();
    ~NoiseModuleManager();
    const Module& getGradient(bool x, bool increasing) const;
    
protected:
    std::map<TerrainIDPair, ModulePtr> mBordersHorizontal;
    std::map<TerrainIDPair, ModulePtr> mBordersVertical;

};

