#pragma once
#include <rapidjson/document.h>
#include "Options.h"
#include "TileLocation.h"
#include "Tile.h"
#include "Tileset.h"
#include <map>
#include <set>
#include <vector>
#include <unordered_map>

class MetaOutput
{
public:
    typedef std::vector<TerrainID> TerrainSet;
    typedef std::set<TerrainSet> TerrainSetSet;
    typedef std::map<TerrainID, TerrainSetSet> TerrainHypergraph;
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
    const std::vector<Tile>& getTiles() const;
    const std::unordered_map<std::string, std::vector<TileLocation>>& getTileGroups() const;
    const std::vector<Tileset>& getTilesetData() const;
    const TerrainHypergraph& getTerrainHypergraph() const;
protected:
    std::vector<Tileset> mTilesets;
    std::vector<Tile> mTiles;
    std::unordered_map<std::string, std::vector<TileLocation>> mTileGroups;
    TerrainHypergraph mTerrainHypergraph;
private:
    size_t mResolution;
    void writeJsonObjectToFile(const rapidjson::Document& object, std::string filename) const;
};

