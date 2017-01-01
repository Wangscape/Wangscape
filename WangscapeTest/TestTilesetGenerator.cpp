#include <gtest/gtest.h>
#include <Options.h>
#include <tilegen/TileGenerator.h>
#include <tilegen/TilesetGenerator.h>
#include <tilegen/partition/TilePartitionerSquares.h>

class TestTilesetGenerator : public ::testing::Test {
protected:
    std::string filename;
    const Options options;
    TilesetGenerator tg;

    TestTilesetGenerator():
        filename("../Wangscape/example/example_options.json"),
        options(filename),
        tg(options, std::move(std::make_unique<TilePartitionerSquares>(options)))
    {

    };
    ~TestTilesetGenerator() {};
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
