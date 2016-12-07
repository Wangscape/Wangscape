#pragma once
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <rapidjson/document.h>
#include "TerrainSpec.h"
#include "BorderOffsetSpec.h"

class Options
{
public:
    typedef std::string TerrainID;
    typedef std::map<TerrainID, TerrainSpec> TerrainSpecMap;
    typedef std::vector<TerrainID> Clique;
    typedef std::vector<Clique> CliqueList;
    typedef std::pair<TerrainID, TerrainID> TerrainIDPair;
    typedef std::map<TerrainIDPair, BorderOffsetSpec> BorderOffsetMap;

    unsigned int resolution;
    std::string colours = "RGB";
    unsigned int bitDepth = 24;
    std::string fileType = "PNG";

    std::string outputDirectory;

    TerrainSpecMap terrains;

    CliqueList cliques;

    BorderOffsetMap borderOffsets;

    Options(const rapidjson::Document& d);
    ~Options();
};

