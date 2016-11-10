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
    typedef std::map<std::string, TerrainSpec> TerrainSpecMap;
    typedef std::vector<std::string> Clique;
    typedef std::vector<Clique> CliqueList;
    typedef std::pair<std::string, std::string> TerrainNamePair;
    typedef std::map<TerrainNamePair, BorderOffsetSpec> BorderOffsetMap;

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

