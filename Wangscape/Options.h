#pragma once
#include <string>
#include <map>
#include <utility>
#include <vector>
#include "common.h"
#include "metaoutput/Filenames.h"
#include "tilegen/alpha/CalculatorMode.h"
#include "TerrainSpec.h"
#include "TileFormat.h"

class Options
{
public:
    typedef std::map<TerrainID, TerrainSpec> TerrainSpecMap;
    typedef std::vector<TerrainID> Clique;
    typedef std::vector<Clique> CliqueList;

    std::string filename;
    TileFormat tileFormat;
    std::string outputDirectory;
    std::string relativeOutputDirectory;
    metaoutput::Filenames outputFilenames;
    TerrainSpecMap terrains;
    CliqueList cliques;
    tilegen::alpha::CalculatorMode CalculatorMode;
    
    virtual ~Options() = default;
};

