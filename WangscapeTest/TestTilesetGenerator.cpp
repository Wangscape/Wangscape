#include <gtest/gtest.h>
#include <Options.h>
#include <TileGenerator.h>
#include <TilesetGenerator.h>

class TestTilesetGenerator : public ::testing::Test {
protected:
    std::string filename;
    const Options options;
    TilesetGenerator tg;

    TestTilesetGenerator():
        filename("../Wangscape/example/example_options.json"),
        options(filename),
        tg(options)
    {

    };
    ~TestTilesetGenerator() {};
};

TEST_F(TestTilesetGenerator, TestGenerateClique)
{
    std::map<std::pair<size_t, size_t>, std::vector<TerrainID>> tiles;
    const auto& clique = options.cliques[0];
    sf::RenderTexture image;
    tg.generateClique(clique, image, "nope.png",
                      [&](sf::RenderTexture& image, size_t x, size_t y,
                          std::vector<TerrainID> terrains,
                          const TerrainImages& images,
                          const Options& options)
    {
        tiles.insert({ { x,y }, terrains });
    });
    const auto& first_tile = tiles.at({ 0,0 });
    for (auto corner : first_tile)
    {
        EXPECT_STREQ(corner.c_str(), "g") << "Incorrect corner in first tile";
    }
    const auto& last_tile = tiles.at({ 3,3 });
    for (auto corner : last_tile)
    {
        EXPECT_STREQ(corner.c_str(), "s") << "Incorrect corner in last tile";
    }
    for (size_t x = 0; x < 4; x++)
    {
        for (size_t y = 0; y < 4; y++)
        {
            EXPECT_FALSE(tiles.find({ x,y }) == tiles.end()) << "Missing tile";
        }
    }
}

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
