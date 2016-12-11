#include <gtest/gtest.h>
#include <Options.h>
#include <TileGenerator.h>
#include <TilesetGenerator.h>

class TestTilesetGenerator : public ::testing::Test {
protected:
    virtual void SetUp()
    {

    }
    virtual void TearDown()
    {
        
    }
};

TEST_F(TestTilesetGenerator, TestGenerateClique)
{
    std::string filename("../Wangscape/example/example_options.json");
    const Options options(filename);
    TilesetGenerator tg(options);
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
        EXPECT_EQ(corner.c_str(), "g") << "Incorrect corners in first tile";
    }
    const auto& last_tile = tiles.at({ 3,3 });
    for (auto corner : last_tile)
    {
        EXPECT_EQ(corner.c_str(), "s") << "Incorrect corners in last tile";
    }
    for (size_t x = 0; x < 4; x++)
    {
        for (size_t y = 0; y < 4; y++)
        {
            EXPECT_FALSE(tiles.find({ x,y }) == tiles.end()) << "Missing tile";
        }
    }
}
