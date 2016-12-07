#include "TilesetGenerator.h"
#include "TileGenerator.h"
#pragma warning(push)
#pragma warning(disable: 4996)
#include <boost/gil/extension/io/png_dynamic_io.hpp>
#pragma warning(pop)
#include <functional>
#include "common.h"

TilesetGenerator::TilesetGenerator()
{
}


TilesetGenerator::~TilesetGenerator()
{
}

void TilesetGenerator::generate(const Options& options,
                                std::function<void(void*, size_t, size_t,
                                                   std::vector<Options::TerrainID>,
                                                   const Options&)> callback)
{
    // read all input tiles/tilesets
    //for (auto& it : options.terrains)
    //{
    //    boost::gil::rgb32_image_t input_tile;
    //    boost::gil::png_read_image(it.second.fileName, input_tile);
    //}
    // prepare a blank image
    // make a tile for each 4-tuple of terrains in the clique
    for (const auto& clique : options.cliques)
    {
        std::vector<Options::TerrainID> corner_terrains(CORNERS, clique[0]);
        std::vector<size_t> corner_clique_indices(CORNERS, 0);
        bool stop = false;
        size_t res_x = options.resolution;
        size_t res_y = options.resolution;
        bool x_dimension = true;
        for (int i = 0; i < CORNERS; i++)
        {
            size_t& res_z = x_dimension ? res_x : res_y;
            res_z *= clique.size();
        }
        // prepare a blank image of size res_x*res_y
        // make a tile for each 4-tuple of terrains in the clique
        while (!stop)
        {

            size_t x = 0; size_t y = 0;
            bool x_dimension = true;
            for (size_t i : corner_clique_indices)
            {
                size_t& z = x_dimension ? x : y;
                z *= clique.size();
                z += corner_clique_indices[i];
                x_dimension = !x_dimension;
            }
            callback(nullptr, x, y, corner_terrains, options);
            for (auto& i : corner_clique_indices)
            {
                i++;
                if (i >= clique.size())
                {
                    i = 0;
                }
                else
                {
                    break;
                }
            }
        }
    }
}