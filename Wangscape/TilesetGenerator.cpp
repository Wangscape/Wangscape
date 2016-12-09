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
    for (const auto& clique : options.cliques)
    {
        size_t res_x = options.resolution;
        size_t res_y = options.resolution;
        bool x_dimension = true;
        for (int i = 0; i < CORNERS; i++)
        {
            size_t& res_z = x_dimension ? res_x : res_y;
            res_z *= clique.size();
            x_dimension = !x_dimension;
        }
        // prepare a blank image of size res_x*res_y
        sf::RenderTexture output;
        output.create(res_x, res_y);
        output.clear(sf::Color(0,0,0,255));
        generateClique(clique, output, TileGenerator::generate);
        output.display();

        std::stringstream ss;
        for (auto terrain : clique)
        {
            ss << terrain << ".";
        }
        ss << options.fileType;
        std::string filename = ss.str();
        boost::filesystem::path p(options.filename);
        p.remove_filename();
        p.append(options.outputDirectory);
        boost::filesystem::create_directories(p);
        p.append(filename);
        filename = p.string();
        callback(output.getTexture(), filename);
    }
}

void TilesetGenerator::generateClique(const Options::Clique& clique, sf::RenderTexture& image,
                                      TileGenerator::TileGenerateFunction callback)
{
    std::vector<Options::TerrainID> corner_terrains(CORNERS, clique[0]);
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
        stop = true;
        auto zip_begin = boost::make_zip_iterator(boost::make_tuple(corner_terrains.begin(),
                                                                    corner_clique_indices.begin()));
        auto zip_end = boost::make_zip_iterator(boost::make_tuple(corner_terrains.end(),
                                                                  corner_clique_indices.end()));
        for (auto it : boost::make_iterator_range(zip_begin,zip_end))
        {
            size_t& i = it.tail.head;
            Options::TerrainID& t = it.head;
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