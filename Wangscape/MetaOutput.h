#pragma once
#include <rapidjson/document.h>
#include "Options.h"
class MetaOutput
{
public:
    MetaOutput();
    ~MetaOutput();
    void addTile(std::vector<Options::TerrainID> corners,
                 std::string filename, size_t offset_x, size_t offset_y);
    void addTileset(std::vector<Options::TerrainID> terrains,
                    std::string filename, size_t size_x, size_t size_y);
    void setResolution(size_t resolution);
    void writeTileData(std::string filename);
    void writeTileGroups(std::string filename);
    void writeTilesetData(std::string filename);
    void writeAll(const Options& options);
    const rapidjson::Document& getTileData() const;
    const rapidjson::Document& getTileGroups() const;
    const rapidjson::Document& getTilesetData() const;
protected:
    rapidjson::Document mTilesetData;
    rapidjson::Document mTileData;
    rapidjson::Document mTileGroups;
};

