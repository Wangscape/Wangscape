#include "TilesetGenerator.h"
#include <boost/gil/extension/io/png_dynamic_io.hpp>

TilesetGenerator::TilesetGenerator()
{
}


TilesetGenerator::~TilesetGenerator()
{
}

bool TilesetGenerator::generate(const Options& options)
{
    for (auto& it : options.terrains)
    {
        boost::gil::rgb32_image_t input_tile;
        boost::gil::png_read_image(it.second.fileName, input_tile);
    }
}