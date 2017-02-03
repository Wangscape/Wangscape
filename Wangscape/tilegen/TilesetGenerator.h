#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Options.h"
#include "TileGenerator.h"
#include "partition/TilePartitionerBase.h"
#include "TerrainImages.h"
#include "metaoutput/MetaOutput.h"
#include "CartesianPower.h"

namespace tilegen
{

class TilesetGenerator
{
public:
    typedef CartesianPower<Options::Clique::const_iterator> CornersGenerator;
    TilesetGenerator(const Options& options,
                     std::unique_ptr<partition::TilePartitionerBase> tile_partitioner);
    virtual ~TilesetGenerator() = default;
    void generate(std::function<void(const sf::Texture&, std::string)> callback);
    void generateClique(const Options::Clique& clique, sf::RenderTexture& image, std::string filename);
    const Options& options;
    metaoutput::MetaOutput metaOutput;
    TerrainImages images;
private:
    std::unique_ptr<tilegen::partition::TilePartitionerBase> mTilePartitioner;

    std::string getOutputImageFilename(const Options::Clique& clique) const;
    std::unique_ptr<sf::RenderTexture> getBlankImage(size_t res_x, size_t res_y) const;
    std::pair<size_t, size_t> calculateTilesetResolution(size_t clique_size) const;
};

} // namespace tilegen
