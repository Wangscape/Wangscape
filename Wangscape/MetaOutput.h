#pragma once
#include <rapidjson/document.h>
#include "Options.h"
#include <map>
#include <set>
class MetaOutput
{
public:
    typedef std::vector<TerrainID> TerrainSet;
    typedef std::set<TerrainSet> TerrainSetSet;
    typedef std::map<TerrainID, TerrainSetSet> TerrainHypergraph;
    MetaOutput();
    ~MetaOutput();
    void addTile(std::vector<TerrainID> corners,
                 std::string filename, size_t offset_x, size_t offset_y);
    void addTileset(std::vector<TerrainID> terrains,
                    std::string filename, size_t size_x, size_t size_y);
    void setResolution(size_t resolution);
    void writeTileData(std::string filename) const;
    void writeTileGroups(std::string filename) const;
    void writeTilesetData(std::string filename) const;
    void writeTerrainHypergraph(std::string filename) const;
    void writeAll(const Options& options) const;
    const rapidjson::Document& getTileData() const;
    const rapidjson::Document& getTileGroups() const;
    const rapidjson::Document& getTilesetData() const;
    const TerrainHypergraph& getTerrainHypergraph() const;
protected:
    rapidjson::Document mTilesetData;
    rapidjson::Document mTileData;
    rapidjson::Document mTileGroups;
    TerrainHypergraph mTerrainHypergraph;
};

