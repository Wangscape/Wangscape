#pragma once
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <rapidjson/document.h>
#include "common.h"
#include "TerrainSpec.h"

class Options
{
public:
    typedef std::map<TerrainID, TerrainSpec> TerrainSpecMap;
    typedef std::vector<TerrainID> Clique;
    typedef std::vector<Clique> CliqueList;

    const std::string filename;

    unsigned int resolution;
    std::string fileType = "png";

    std::string outputDirectory;
    std::string relativeOutputDirectory;

    std::string tileDataFilename;
    std::string tileGroupsFilename;
    std::string tilesetDataFilename;
    std::string terrainHypergraphFilename;

    TerrainSpecMap terrains;

    CliqueList cliques;

    Options(std::string filename);
    void initialise(const rapidjson::Document& d);
    virtual ~Options() = default;
};

