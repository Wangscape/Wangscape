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
    mTilePartitioner(std::move(tile_partitioner))
{
    for (auto& terrain : options.terrains)
    {
        images.addTerrain(terrain.first, terrain.second.fileName, options.filename,
                          terrain.second.offsetX, terrain.second.offsetY, options.tileFormat.resolution);
    }
}

void TilesetGenerator::generate(std::function<void(const sf::Texture&, std::string)> callback)
{
    mo.setResolution(options.tileFormat.resolution);
    boost::filesystem::path p(options.relativeOutputDirectory);
    for (const auto& clique : options.cliques)
    {
        CornersGenerator corners_generator(clique, static_cast<size_t>(CORNERS));
        std::pair<size_t, size_t> tileset_resolution = corners_generator.size_2d(options.tileFormat.resolution);
        size_t res_x = tileset_resolution.first;
        size_t res_y = tileset_resolution.second;
        std::unique_ptr<sf::RenderTexture> output{getBlankImage(res_x, res_y)};

        auto filename = getOutputImageFilename(clique);

        // MetaOutput.addTileset, addTile should use this version of filename;
        // relative to output dir, not options dir!
        mo.addTileset(clique, filename, res_x, res_y);
        generateClique(clique, *output, filename);
        output->display();

        p.append(filename);
        callback(output->getTexture(), p.string());
        p.remove_filename();
    }
}

void TilesetGenerator::generateClique(const Options::Clique& clique, sf::RenderTexture& image, std::string filename)
{
    CornersGenerator corners_generator(clique, static_cast<size_t>(CORNERS));
    for (auto it = corners_generator.cbegin(); it != corners_generator.cend(); ++it)
    {
        const auto& corner_terrains = *it;
        std::pair<size_t, size_t> tile_position = it.coordinates_2d();
        TileGenerator::generate(image, tile_position.first, tile_position.second, corner_terrains,
                                images, options, *mTilePartitioner.get());
        mo.addTile(corner_terrains, filename,
                   tile_position.first*options.tileFormat.resolution,
                   tile_position.second*options.tileFormat.resolution);
    }
}

std::string TilesetGenerator::getOutputImageFilename(const Options::Clique& clique) const
{
    std::stringstream ss;
    for (auto terrain : clique)
    {
        ss << terrain << ".";
    }
    ss << options.tileFormat.fileType;
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
