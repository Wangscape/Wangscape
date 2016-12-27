#pragma once
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <rapidjson/document.h>
#include "common.h"
#include "OutputFilenames.h"
#include "TerrainSpec.h"
#include "TileFormat.h"

class Options
{
public:
    typedef std::map<TerrainID, TerrainSpec> TerrainSpecMap;
    typedef std::vector<TerrainID> Clique;
    typedef std::vector<Clique> CliqueList;

    const std::string filename;
    TileFormat tileFormat;
    std::string outputDirectory;
    std::string relativeOutputDirectory;
    OutputFilenames outputFilenames;
    TerrainSpecMap terrains;
    CliqueList cliques;

    Options() = default;
    Options(std::string filename);
    void initialise(const rapidjson::Document& d);
    ~Options();
};

