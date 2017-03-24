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
#include "OptionsPaths.h"

class Options
{
public:
    typedef std::map<TerrainID, TerrainSpec> TerrainSpecMap;
    typedef std::vector<TerrainID> Clique;
    typedef std::vector<Clique> CliqueList;

    OptionsPaths paths;
    TileFormat tileFormat;
    std::string outputDirectory;
    std::string relativeOutputDirectory;
    metaoutput::Filenames outputFilenames;
    TerrainSpecMap terrains;
    CliqueList cliques;
    boost::optional<double> alphaCalculatorTopTwoPower;
    tilegen::alpha::CalculatorMode calculatorMode;
    std::string combinerModuleGroup;
    boost::optional<std::string> defaultModuleGroup;
    std::vector<TerrainModuleGroupLocation> centralModuleGroups;
    std::vector<BorderModuleGroupLocation> leftBorderModuleGroups;
    std::vector<BorderModuleGroupLocation> topBorderModuleGroups;
    bool debugOutput;
    std::pair<size_t, size_t> debugTileResolution;
    
    virtual ~Options() = default;
};

