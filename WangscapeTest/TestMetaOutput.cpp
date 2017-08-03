#include <gtest/gtest.h>

#include <algorithm>
#include <algorithm>

#include <spotify/json.hpp>

#include <OptionsManager.h>
#include <metaoutput/MetaOutput.h>
#include <codecs/OptionsCodec.h>

#include <tilegen/TilesetGenerator.h>
#include <tilegen/partition/TilePartitionerSquares.h>

#include "TestRequiringOptions.h"

class TestMetaOutput : public TestRequiringOptions
{
protected:
    tilegen::TilesetGenerator tg;
    const metaoutput::MetaOutput& metaOutput;
    TestMetaOutput() :
        TestRequiringOptions(),
        tg(options(),
           std::move(std::make_unique<tilegen::partition::TilePartitionerSquares>(options()))),
        metaOutput(tg.metaOutput)
    {
        tg.generate([&](const sf::Texture& output, std::string filename) {});
    };
};

// TODO replace this test with something faster
TEST_F(TestMetaOutput, TestMetaOutputCorrect)
{
    const auto& td = metaOutput.getTileData();
    for (const auto& corner : td[0].corners)
    {
        EXPECT_EQ(corner, "g") << "Incorrect terrain id in TileData[0].corners";
    }

    for (const auto& corner : td[15].corners)
    {
        EXPECT_EQ(corner, "s") << "Incorrect terrain id in TileData[15].corners";
    }

    const auto& tsd = metaOutput.getTilesetData();
    EXPECT_TRUE(std::any_of(std::cbegin(tsd), std::cend(tsd),
                [](auto& t){return t.filename == "g.s.png";}));
    EXPECT_TRUE(std::all_of(std::begin(tsd), std::end(tsd),
                [](auto& t) {return t.resolution == sf::Vector2u(32, 32); })) << "Incorrect resolution";

    const auto& tgd = metaOutput.getTileGroups();
    EXPECT_TRUE(tgd.find("g.s.g.s") != tgd.end()) << "TileGroups is missing ""g.s.g.s""";
    EXPECT_TRUE(tgd.find("g.s.s.g") != tgd.end()) << "TileGroups is missing ""g.s.s.g""";

    const auto& ta = metaOutput.getTerrainHypergraph();
    EXPECT_NE(ta.find("g"), ta.end()) << R"("TerrainHypergraph is missing "g")";
    auto it = ta.at("g").cbegin();
    EXPECT_NE(std::find((*it).cbegin(), (*it).cend(), "s"), (*it).cend());
}
