#include <gtest/gtest.h>
#include <OptionsManager.h>
#include <tilegen/TileGenerator.h>
#include <tilegen/TilesetGenerator.h>
#include <tilegen/partition/TilePartitionerSquares.h>

#include "TestRequiringOptions.h"

class TestTilesetGenerator : public TestRequiringOptions
{
protected:
    tilegen::TilesetGenerator tg;
    TestTilesetGenerator():
        TestRequiringOptions(),
        tg(options, std::move(std::make_unique<tilegen::partition::TilePartitionerSquares>(options)))
    {

    };
};

// TODO test TilesetGenerator::generateClique

// TODO replace this test with something faster
TEST_F(TestTilesetGenerator, TestGenerateTilesets)
{
    tg.generate([&](const sf::Texture& output, std::string filename)
    {
        sf::Image img = output.copyToImage();
        for (size_t x = 0; x < img.getSize().x; x++)
        {
            for (size_t y = 0; y < img.getSize().y; y++)
            {
                EXPECT_EQ(img.getPixel(x, y).a, (sf::Uint8)255) << "Non-opaque pixel in output";
            }
        }
    });
}
