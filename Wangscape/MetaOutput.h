#pragma once
#include <rapidjson/document.h>
#include "Options.h"
#include <map>
#include <set>
class MetaOutput
{
public:
    typedef std::set<Options::TerrainID> TerrainSet;
    typedef std::map<Options::TerrainID, TerrainSet> TerrainAdjacency;
    MetaOutput();
    ~MetaOutput();
    void addTile(std::vector<Options::TerrainID> corners,
                 std::string filename, size_t offset_x, size_t offset_y);
    void addTileset(std::vector<Options::TerrainID> terrains,
                    std::string filename, size_t size_x, size_t size_y);
    void setResolution(size_t resolution);
    void writeTileData(std::string filename) const;
    void writeTileGroups(std::string filename) const;
    void writeTilesetData(std::string filename) const;
    void writeTerrainAdjacency(std::string filename) const;
    void writeAll(const Options& options) const;
    const rapidjson::Document& getTileData() const;
    const rapidjson::Document& getTileGroups() const;
    const rapidjson::Document& getTilesetData() const;
    const TerrainAdjacency& getTerrainAdjacency() const;
protected:
    rapidjson::Document mTilesetData;
    rapidjson::Document mTileData;
    rapidjson::Document mTileGroups;
    TerrainAdjacency mTerrainAdjacency;
};

