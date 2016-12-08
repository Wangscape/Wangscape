#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

#include <rapidjson/istreamwrapper.h>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <fstream>
#include <sstream>
#include <istream>

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
            std::ifstream ifs(filename);
            Assert::IsTrue(ifs.good(),L"Couldn't open example json options");
            rapidjson::IStreamWrapper isw(ifs);
            rapidjson::Document options_document;
            options_document.ParseStream(isw);
            if (options_document.HasParseError())
            {
                std::wstringstream ss;
                ss << "Options document has parse error at offset " << (unsigned)options_document.GetErrorOffset() << ":\n";
                ss << GetParseError_En(options_document.GetParseError()) << "\n";
                Assert::IsFalse(options_document.HasParseError(), ss.str().c_str());
            }
            const Options options(options_document, filename);
            TilesetGenerator tg(options);
            std::map<std::pair<size_t, size_t>, std::vector<Options::TerrainID>> tiles;
            const auto& clique = options.cliques[0];
            tg.generateClique(clique, nullptr,
                              [&](void* image, size_t x, size_t y,
                                  std::vector<Options::TerrainID> terrains,
                                  const Options& options)
            {
                tiles.insert({ {x,y}, terrains });
            });
            const auto& first_tile = tiles.at({ 0,0 });
            for (auto corner : first_tile)
            {
                Assert::AreEqual(corner.c_str(), "0", L"Incorrect corners in first tile");
            }
            for (size_t x = 0; x < 4; x++)
            {
                for (size_t y = 0; y < 4; y++)
                {
                    Assert::IsFalse(tiles.find({ x,y }) == tiles.end(), L"Missing tile");
                }
            }
        }

    };
}