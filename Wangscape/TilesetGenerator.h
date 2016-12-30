#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Options.h"
#include "TileGenerator.h"
#include "TerrainImages.h"
#include "metaoutput/MetaOutput.h"
class TilesetGenerator
{
public:
    TilesetGenerator(const Options& options);
    ~TilesetGenerator();
    void generate(std::function<void(const sf::Texture&, std::string)> callback);
    void generateClique(const Options::Clique& clique, sf::RenderTexture& image, std::string filename,
                        TileGenerator::TileGenerateFunction callback);
    const Options& options;
    metaoutput::MetaOutput mo;
    TerrainImages images;

private:
    std::string getOutputImageFilename(const Options::Clique& clique) const;
    std::unique_ptr<sf::RenderTexture> getBlankImage(size_t res_x, size_t res_y) const;
    std::pair<size_t, size_t> calculateTilesetResolution(size_t clique_size) const;
};
