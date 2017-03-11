#pragma once
#include "Options.h"
#include "metaoutput/TileLocation.h"
#include "metaoutput/Tile.h"
#include "metaoutput/Tileset.h"
#include "metaoutput/TileGroups.h"
#include <map>
#include <set>
#include <vector>
#include <unordered_map>
#include <SFML/System/Vector2.hpp>

namespace metaoutput
{

class MetaOutput
{
public:
    typedef std::vector<TerrainID> TerrainSet;
    typedef std::set<TerrainSet> TerrainSetSet;
    typedef std::map<TerrainID, TerrainSetSet> TerrainHypergraph;
    
    virtual ~MetaOutput() = default;
    
    void addTile(std::vector<TerrainID> corners,
                 std::string filename, size_t offset_x, size_t offset_y);
    void addTileset(TerrainSet terrains,
                    std::string filename, size_t size_x, size_t size_y);
    void setResolution(sf::Vector2u resolution);
    void writeTileData(std::string filename) const;
    void writeTileGroups(std::string filename) const;
    void writeTilesetData(std::string filename) const;
    void writeTerrainHypergraph(std::string filename) const;
    void writeAll(const Options& options) const;
    const std::vector<Tile>& getTileData() const;
    const TileGroups& getTileGroups() const;
    const std::vector<Tileset>& getTilesetData() const;
    const TerrainHypergraph& getTerrainHypergraph() const;
protected:
    std::vector<Tileset> mTilesets;
    std::vector<Tile> mTiles;
    TileGroups mTileGroups;
    TerrainHypergraph mTerrainHypergraph;
private:
    sf::Vector2u mResolution;
};

} // namespace metaoutput
