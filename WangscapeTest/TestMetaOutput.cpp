#include <gtest/gtest.h>

#include <OptionsManager.h>
#include <TilesetGenerator.h>
#include <metaoutput/MetaOutput.h>
#include <codecs/OptionsCodec.h>

#include <algorithm>
#include <fstream>

#include <spotify/json.hpp>

class TestMetaOutput : public ::testing::Test {
protected:
    std::string filename;
    std::ifstream ifs;
    const OptionsManager& optionsManager;
    TilesetGenerator tg;
    const metaoutput::MetaOutput& mo;
    TestMetaOutput() :
        filename("../../Wangscape/example/example_options.json"),
        optionsManager(filename),
        tg{optionsManager.getOptions()},
        mo{tg.mo}
    {
        tg.generate([&](const sf::Texture& output, std::string filename) {});
    };
    ~TestMetaOutput() {};
};

TEST_F(TestMetaOutput, TestMetaOutputCorrect)
{
    const auto& td = mo.getTileData();
    for (const auto& corner : td[0].corners)
    {
        EXPECT_EQ(corner, "g") << "Incorrect terrain id in TileData[0].corners";
    }

    for (const auto& corner : td[15].corners)
    {
        EXPECT_EQ(corner, "s") << "Incorrect terrain id in TileData[15].corners";
    }

    const auto& tsd = mo.getTilesetData();
    EXPECT_TRUE(std::any_of(std::cbegin(tsd), std::cend(tsd),
                [](auto& t){return t.filename == "g.s.png";}));
    EXPECT_TRUE(std::all_of(std::begin(tsd), std::end(tsd),
                [](auto& t){return t.resolution == 32;})) << "Incorrect resolution";

    const auto& tgd = mo.getTileGroups();
    EXPECT_TRUE(tgd.find("g.s.g.s") != tgd.end()) << "TileGroups is missing ""g.s.g.s""";
    EXPECT_TRUE(tgd.find("g.s.s.g") != tgd.end()) << "TileGroups is missing ""g.s.s.g""";

    const auto& ta = mo.getTerrainHypergraph();
    EXPECT_NE(ta.find("g"), ta.end()) << R"("TerrainHypergraph is missing "g")";
    auto it = ta.at("g").cbegin();
    EXPECT_NE(std::find((*it).cbegin(), (*it).cend(), "s"), (*it).cend());
}
