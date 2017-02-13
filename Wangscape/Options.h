#pragma once
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <boost/optional.hpp>
#include "common.h"
#include "metaoutput/Filenames.h"
#include "tilegen/alpha/CalculatorMode.h"
#include "TerrainSpec.h"
#include "TileFormat.h"
#include "BorderModuleGroupLocation.h"
#include "TerrainModuleGroupLocation.h"

class Options
{
public:
    typedef std::map<TerrainID, TerrainSpec> TerrainSpecMap;
    typedef std::vector<TerrainID> Clique;
    typedef std::vector<Clique> CliqueList;

    std::string filename;
    std::string directory;
    TileFormat tileFormat;
    std::string outputDirectory;
    std::string relativeOutputDirectory;
    metaoutput::Filenames outputFilenames;
    TerrainSpecMap terrains;
    CliqueList cliques;
    tilegen::alpha::CalculatorMode CalculatorMode;
    std::string combinerModuleGroup;
    boost::optional<std::string> defaultModuleGroup;
    std::vector<TerrainModuleGroupLocation> centralModuleGroups;
    std::vector<BorderModuleGroupLocation> horizontalBorderModuleGroups;
    std::vector<BorderModuleGroupLocation> verticalBorderModuleGroups;
    bool debugOutput;
    
    virtual ~Options() = default;
};

