#pragma once
#include <memory>
#include <map>
#include <noise/noise.h>
#include "common.h"
#include "Gradient.h"
#include "ModuleGroup.h"
class NoiseModuleManager
{
public:
    typedef noise::module::Module Module;
    typedef std::pair<TerrainID, TerrainID> TerrainIDPair;
    NoiseModuleManager();
    ~NoiseModuleManager();
    
protected:
    std::map<TerrainIDPair, ModulePtr> mBordersHorizontal;
    std::map<TerrainIDPair, ModulePtr> mBordersVertical;

};

