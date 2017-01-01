#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Options.h"
#include "TileGenerator.h"
#include "partition/TilePartitionerBase.h"
#include "../TerrainImages.h"
#include "../MetaOutput.h"
class TilesetGenerator
{
public:
    TilesetGenerator(const Options& options,
                     std::unique_ptr<TilePartitionerBase> tile_partitioner);
    virtual ~TilesetGenerator() = default;
    void generate(std::function<void(const sf::Texture&, std::string)> callback);
    void generateClique(const Options::Clique& clique, sf::RenderTexture& image, std::string filename);
    const Options& options;
    MetaOutput mo;
    TerrainImages images;
private:
    std::unique_ptr<TilePartitionerBase> mTilePartitioner;

    std::string getOutputImageFilename(const Options::Clique& clique) const;
    std::unique_ptr<sf::RenderTexture> getBlankImage(size_t res_x, size_t res_y) const;
    std::pair<size_t, size_t> calculateTilesetResolution(size_t clique_size) const;
};
