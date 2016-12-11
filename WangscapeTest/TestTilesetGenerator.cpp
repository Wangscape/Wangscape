#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

#include <SFML/Graphics.hpp>

#include "../Wangscape/Options.h"
#include "../Wangscape/TileGenerator.h"
#include "../Wangscape/TilesetGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WangscapeTest
{
    TEST_CLASS(TestTilesetGenerator)
    {
    public:

        TEST_METHOD(TestGenerateClique)
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
                tiles.insert({ {x,y}, terrains });
            });
            const auto& first_tile = tiles.at({ 0,0 });
            for (auto corner : first_tile)
            {
                Assert::AreEqual(corner.c_str(), "g", L"Incorrect corners in first tile");
            }
            const auto& last_tile = tiles.at({ 3,3 });
            for (auto corner : last_tile)
            {
                Assert::AreEqual(corner.c_str(), "s", L"Incorrect corners in last tile");
            }
            for (size_t x = 0; x < 4; x++)
            {
                for (size_t y = 0; y < 4; y++)
                {
                    Assert::IsFalse(tiles.find({ x,y }) == tiles.end(), L"Missing tile");
                }
            }
        }

        TEST_METHOD(TestGenerateTilesets)
        {
            std::string filename("../Wangscape/example/example_options.json");
            const Options options(filename);
            TilesetGenerator tg(options);
            tg.generate([&](const sf::Texture& output, std::string filename)
            {
                sf::Image img = output.copyToImage();
                for (size_t x = 0; x < img.getSize().x; x++)
                {
                    for (size_t y = 0; y < img.getSize().y; y++)
                    {
                        Assert::AreEqual(img.getPixel(x, y).a, (sf::Uint8)255);
                    }
                }
            });
        }
    };
}