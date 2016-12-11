#pragma once
#include <vector>
#include <map>
#include <memory>
#include <noise/noise.h>
#include "Options.h"
class BorderInfo
{
public:
    typedef noise::module::Module Module;
    typedef std::unique_ptr<Module> UniqueModule;
    typedef std::pair<UniqueModule, UniqueModule> BorderPair;
    typedef std::pair<TerrainID, TerrainID> TerrainIDPair;

    BorderInfo(const Options& options);
    ~BorderInfo();
    std::map<TerrainIDPair, BorderPair> borders;
    noise::module::ScalePoint flatten_x() const;
    noise::module::ScalePoint flatten_y() const;
};

