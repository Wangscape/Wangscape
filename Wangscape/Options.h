#pragma once
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <rapidjson/document.h>
#include "TerrainSpec.h"
#include "BorderOffsets.h"

class Options
{
public:
    typedef std::map<std::string, TerrainSpec> TerrainSpecMap;
    typedef std::vector<std::string> Clique;
    typedef std::vector<Clique> CliqueList;
    typedef std::pair<std::string, std::string> TerrainNamePair;
    typedef std::map<TerrainNamePair, BorderOffsets> BorderOffsetMap;

    unsigned int resolution;
    std::string colours;
    unsigned int bitDepth;
    std::string fileType;
    std::string outputDirectory;
    TerrainSpecMap terrains;
    CliqueList cliques;
    BorderOffsetMap borderOffsets;

    Options(const rapidjson::Document& d);
    ~Options();
};

