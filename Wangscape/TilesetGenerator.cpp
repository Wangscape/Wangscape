#include "TilesetGenerator.h"
#include "TileGenerator.h"
#include <functional>
#include <stdexcept>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/range.hpp>
#include "common.h"

TilesetGenerator::TilesetGenerator(const Options& options) :
    options(options)
{
    for (auto& terrain : options.terrains)
    {
        images.addTerrain(terrain.first, terrain.second.fileName, options.filename,
                          terrain.second.offsetX, terrain.second.offsetY, options.resolution);
    }
}

TilesetGenerator::~TilesetGenerator()
{
}

void TilesetGenerator::generate(std::function<void(const sf::Texture&, std::string)> callback)
{
    mo.setResolution(options.resolution);
    boost::filesystem::path p(options.relativeOutputDirectory);
    for (const auto& clique : options.cliques)
    {
        size_t res_x = options.resolution * clique.size() * clique.size();
        size_t res_y = options.resolution * clique.size() * clique.size();

        std::unique_ptr<sf::RenderTexture> output{getBlankImage(res_x, res_y)};

        std::stringstream ss;
        for (auto terrain : clique)
        {
            ss << terrain << ".";
        }
        ss << options.fileType;
        std::string filename = ss.str();
        // MetaOutput.addTileset, addTile should use this version of filename;
        // relative to output dir, not options dir!
        mo.addTileset(clique, filename, res_x, res_y);
        generateClique(clique, *output, filename, TileGenerator::generate);
        output->display();

        p.append(filename);
        callback(output->getTexture(), p.string());
        p.remove_filename();
    }
}

void TilesetGenerator::generateClique(const Options::Clique& clique, sf::RenderTexture& image, std::string filename,
                                      TileGenerator::TileGenerateFunction callback)
{
    std::vector<TerrainID> corner_terrains(CORNERS, clique[0]);
    std::vector<size_t> corner_clique_indices(CORNERS, 0);
    bool stop = false;
    while (!stop)
    {
        size_t x = 0; size_t y = 0;
        bool x_dimension = true;
        for (size_t i : corner_clique_indices)
        {
            size_t& z = x_dimension ? x : y;
            z *= clique.size();
            z += i;
            x_dimension = !x_dimension;
        }
        callback(image, x, y, corner_terrains, images, options);
        mo.addTile(corner_terrains, filename, x*options.resolution, y*options.resolution);
        stop = true;
        auto zip_begin = boost::make_zip_iterator(boost::make_tuple(corner_terrains.begin(),
                                                                    corner_clique_indices.begin()));
        auto zip_end = boost::make_zip_iterator(boost::make_tuple(corner_terrains.end(),
                                                                  corner_clique_indices.end()));
        for (auto it : boost::make_iterator_range(zip_begin,zip_end))
        {
            size_t& i = it.tail.head;
            TerrainID& t = it.head;
            i++;
            if (i >= clique.size())
            {
                i = 0;
                t = clique[i];
            }
            else
            {
                stop = false;
                t = clique[i];
                break;
            }
        }
    }
}

std::unique_ptr<sf::RenderTexture> TilesetGenerator::getBlankImage(size_t res_x, size_t res_y) const
{
    std::unique_ptr<sf::RenderTexture> output{std::make_unique<sf::RenderTexture>()};
    output->create(res_x, res_y);
    output->clear(sf::Color(0,0,0,255));
    return output;
}
