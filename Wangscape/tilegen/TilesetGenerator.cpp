#include "Corners.h"
#include "TilesetGenerator.h"
#include "TileGenerator.h"
#include <functional>
#include <stdexcept>
#include <sstream>
#include <boost/filesystem.hpp>
#include "common.h"

namespace tilegen
{

TilesetGenerator::TilesetGenerator(const Options& options,
                                   std::unique_ptr<partition::TilePartitionerBase> tile_partitioner) :
    options(options),
    mTilePartitioner(std::move(tile_partitioner)),
    mDebugTileBuilder(mDebugTile, {0., 0., 1., 1.})
    // TODO (Serin) this sf::Rect is repeated in TilePartitionerNoise, factor it out
{
    if (options.debugOutput)
    {
        mDebugTile.create(options.tileFormat.resolution.x, options.tileFormat.resolution.y);
        partition::TilePartitionerBase::DebugModuleWriter bound_debug_tile_writer = 
            std::bind(&TilesetGenerator::writeDebugTile, this,
                      std::placeholders::_1, std::placeholders::_2,
                      std::placeholders::_3, std::placeholders::_4);
        tile_partitioner->setDebugModuleWriter(bound_debug_tile_writer);
    }
    for (auto& terrain : options.terrains)
    {
        images.addTerrain(terrain.first, terrain.second.fileName, options.paths.filename,
                          terrain.second.offsetX, terrain.second.offsetY, options.tileFormat.resolution);
    }
}

void TilesetGenerator::generate(std::function<void(const sf::Texture&, std::string)> callback)
{
    metaOutput.setResolution(options.tileFormat.resolution);
    boost::filesystem::path p(options.relativeOutputDirectory);
    for (const auto& clique : options.cliques)
    {
        CornersGenerator corners_generator(clique, static_cast<size_t>(CORNERS));
        std::pair<size_t, size_t> tileset_resolution = corners_generator.size2D(options.tileFormat.resolution);
        mResX = tileset_resolution.first;
        mResY = tileset_resolution.second;
        std::unique_ptr<sf::RenderTexture> output{getBlankImage(mResX, mResY)};
        mDebugTilesets.clear();

        auto filename_base = getOutputImageFilename(clique);
        auto filename = filename_base + options.tileFormat.fileType;

        // MetaOutput.addTileset, addTile should use this version of filename;
        // relative to output dir, not options dir!
        metaOutput.addTileset(clique, filename, mResX, mResY);
        generateClique(clique, *output, filename);
        output->display();

        p.append(filename);
        callback(output->getTexture(), p.string());
        p.remove_filename();
        for (auto& it : mDebugTilesets)
        {
            it.second->display();
            std::stringstream debug_filename_ss;
            debug_filename_ss << filename_base << it.first.description() << "." << options.tileFormat.fileType;
            auto debug_file_path = (p / "debug" / debug_filename_ss.str()).string();
            callback(it.second->getTexture(), debug_file_path);
        }
    }
}

void TilesetGenerator::generateClique(const Options::Clique& clique, sf::RenderTexture& image, std::string filename)
{
    CornersGenerator corners_generator(clique, static_cast<size_t>(CORNERS));
    for (auto it = corners_generator.cbegin(); it != corners_generator.cend(); ++it)
    {
        const auto& corner_terrains = *it;
        std::pair<size_t, size_t> tile_position = it.coordinates2D();
        TileGenerator::generate(image, tile_position.first, tile_position.second, corner_terrains,
                                images, options, *mTilePartitioner.get());
        metaOutput.addTile(corner_terrains, filename,
                   tile_position.first*options.tileFormat.resolution.x,
                   tile_position.second*options.tileFormat.resolution.y);
    }
}

void TilesetGenerator::writeDebugTile(const DebugTilesetID& debugTilesetID, noise::module::ModulePtr module, size_t x, size_t y)
{
    if (mDebugTilesets.find(debugTilesetID) == mDebugTilesets.end())
    {
        mDebugTilesets.emplace(std::make_pair(DebugTilesetID(debugTilesetID), std::move(getBlankImage(mResX, mResY)))).first;
    }
    sf::RenderTexture& tileset = *mDebugTilesets.at(debugTilesetID).get();
    // There are far more map lookups here than necessary.

    mDebugTileBuilder.build(module.get()->getModule());
    sf::Texture tile_texture;
    tile_texture.loadFromImage(mDebugTile);
    sf::Sprite tile_sprite(tile_texture);
    tile_sprite.setPosition((float)x, (float)y);
    tileset.draw(tile_sprite);
}

std::string TilesetGenerator::getOutputImageFilename(const Options::Clique& clique) const
{
    std::stringstream ss;
    for (auto terrain : clique)
    {
        ss << terrain << ".";
    }
    return ss.str();
}

std::unique_ptr<sf::RenderTexture> TilesetGenerator::getBlankImage(size_t res_x, size_t res_y) const
{
    std::unique_ptr<sf::RenderTexture> output{std::make_unique<sf::RenderTexture>()};
    output->create(res_x, res_y);
    output->clear(sf::Color(0,0,0,255));
    return output;
}

} // namespace tilegen
