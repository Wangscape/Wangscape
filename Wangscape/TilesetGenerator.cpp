#include "TilesetGenerator.h"
#include "TileGenerator.h"
#include <functional>
#include "common.h"

TilesetGenerator::TilesetGenerator(const Options& options) :
    options(options)
{
    // read all input tiles/tilesets
    //for (auto& it : options.terrains)
    //{

    //}
}


TilesetGenerator::~TilesetGenerator()
{
}

void TilesetGenerator::generate()
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
        }
        // prepare a blank image of size res_x*res_y
        generateClique(clique, nullptr, TileGenerator::generate);
        // write tileset image to disk
    }
}

void TilesetGenerator::generateClique(const Options::Clique& clique,
                                      void* image, TileGenerator::TileGenerateFunction callback)
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
        callback(nullptr, x, y, corner_terrains, options);
        stop = true;
        for (auto& i : corner_clique_indices)
        {
            i++;
            if (i >= clique.size())
            {
                i = 0;
            }
            else
            {
                stop = false;
                break;
            }
        }
    }
}