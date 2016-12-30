#include "MetaOutput.h"
#include "codecs/TileCodec.h"
#include "codecs/TilesetCodec.h"
#include "codecs/TileLocationCodec.h"

#include <spotify/json.hpp>

#include <boost/filesystem.hpp>

#include <ostream>
#include <sstream>
#include <fstream>

namespace metaoutput
{

void MetaOutput::addTile(std::vector<TerrainID> corners, std::string filename, size_t offset_x, size_t offset_y)
{
    mTiles.push_back(Tile(corners, filename, offset_x, offset_y));

    std::stringstream ss;
    for (size_t i = 0; i < corners.size() - 1; i++)
        ss << corners[i] << ".";
    ss << *corners.rbegin();

    mTileGroups[ss.str()].push_back(TileLocation(filename, offset_x, offset_y));
}

void MetaOutput::addTileset(TerrainSet terrains, std::string filename, size_t size_x, size_t size_y)
{
    for (auto t : terrains)
    {
        auto it = mTerrainHypergraph.insert({ t, TerrainSetSet() });
        (*it.first).second.insert(terrains);
    }

    mTilesets.push_back(Tileset(filename, mResolution, size_x, size_y, terrains));
}

void MetaOutput::setResolution(size_t resolution)
{
    mResolution = resolution;
}

void MetaOutput::writeTileData(std::string filename) const
{
    std::ofstream ofs(filename);
    ofs << spotify::json::encode(getTileData());
}

void MetaOutput::writeTileGroups(std::string filename) const
{
    std::ofstream ofs(filename);
    ofs << spotify::json::encode(getTileGroups());
}

void MetaOutput::writeTilesetData(std::string filename) const
{
    std::ofstream ofs(filename);
    ofs << spotify::json::encode(getTilesetData());
}

void MetaOutput::writeTerrainHypergraph(std::string filename) const
{
    std::ofstream ofs(filename);
    ofs << spotify::json::encode(getTerrainHypergraph());
}

void MetaOutput::writeAll(const Options & options) const
{
    boost::filesystem::path p(options.relativeOutputDirectory);

    p.append(options.outputFilenames.tilesetDataFilename);
    writeTilesetData(p.string());
    p.remove_filename();

    p.append(options.outputFilenames.tileDataFilename);
    writeTileData(p.string());
    p.remove_filename();

    p.append(options.outputFilenames.tileGroupsFilename);
    writeTileGroups(p.string());
    p.remove_filename();

    p.append(options.outputFilenames.terrainHypergraphFilename);
    writeTerrainHypergraph(p.string());
}

const std::vector<Tile>& MetaOutput::getTileData() const
{
    return mTiles;
}

const TileGroups& MetaOutput::getTileGroups() const
{
    return mTileGroups;
}

const std::vector<Tileset> & MetaOutput::getTilesetData() const
{
    return mTilesets;
}

const MetaOutput::TerrainHypergraph & MetaOutput::getTerrainHypergraph() const
{
    return mTerrainHypergraph;
}

} // namespace metaoutput
