#include "TilesetGenerator.h"
#include "TileGenerator.h"
#include <boost/gil/extension/io/png_dynamic_io.hpp>

TilesetGenerator::TilesetGenerator()
{
}


TilesetGenerator::~TilesetGenerator()
{
}

bool TilesetGenerator::generate(const Options& options)
{
    // read all input tiles/tilesets

    //for (auto& it : options.terrains)
    //{
    //    boost::gil::rgb32_image_t input_tile;
    //    boost::gil::png_read_image(it.second.fileName, input_tile);
    //}

    // make a tileset for each clique
    for (const auto& clique : options.cliques)
    {
        size_t tileset_resolution = options.resolution*clique.size()*clique.size();
        // prepare a blank image
        // make a tile for each 4-tuple of terrains in the clique
        size_t x1 = 0;
        for (auto t1 : clique)
        {
            size_t x2 = 0;
            for (auto t2 : clique)
            {
                size_t y1 = 0;
                for (auto t3 : clique)
                {
                    size_t y2 = 0;
                    for (auto t4 : clique)
                    {
                        size_t x = options.resolution*(clique.size()*x2 + x1);
                        size_t y = options.resolution*(clique.size()*y2 + y1);
                        TileGenerator::generate(nullptr, x, y, { t1,t2,t3,t4 }, options);
                        y2++;
                    }
                    y1++;
                }
                x2++;
            }
            x1++;
        }
    }
}