#include <gtest/gtest.h>

#include <Options.h>
#include <TilesetGenerator.h>
#include <MetaOutput.h>
#include <algorithm>

class TestMetaOutput : public ::testing::Test {
protected:
    std::string filename;
    const Options options;
    TilesetGenerator tg;
    const MetaOutput& mo;
    TestMetaOutput() :
        filename("../Wangscape/example/example_options.json"),
        options(filename),
        tg(options),
        mo(tg.mo)
    {
        tg.generate([&](const sf::Texture& output, std::string filename) {});
    };
    ~TestMetaOutput() {};
};

// TODO replace this test with something faster
TEST_F(TestMetaOutput, TestMetaOutputCorrect)
{
    const auto& td = mo.getTileData();
    // A lot of tests are not implemented because they are better situated in JSON schema validation.
    {
        EXPECT_TRUE(td.IsArray()) << "TileData is not an array";
        const auto& td_item = td[0];
        EXPECT_TRUE(td_item.IsObject())<< L"TileData[0] is not an object";
        EXPECT_TRUE(td_item.HasMember("corners")) << L"TileData[0] does not have corners";
        const auto& td_item_corners = (*td_item.FindMember("corners")).value;
        EXPECT_TRUE(td_item_corners.IsArray()) << "TileData[0][""corners""] is not an array";
        for (int i = 0; i < 4; i++)
            EXPECT_STREQ(td_item_corners[i].GetString(), "g") << "Incorrect terrain id in TileData[0][""corners""]";
    }
    {
        const auto& td_item = td[15];
        EXPECT_TRUE(td_item.IsObject()) << "TileData[15] is not an object";
        EXPECT_TRUE(td_item.HasMember("corners")) << "TileData[15] does not have corners";
        const auto& td_item_corners = (*td_item.FindMember("corners")).value;
        EXPECT_TRUE(td_item_corners.IsArray()) << "TileData[15][""corners""] is not an array";
        for (int i = 0; i < 4; i++)
            EXPECT_STREQ(td_item_corners[i].GetString(), "s") << "Incorrect terrain id in TileData[0][""corners""]";

        const auto& tsd = mo.getTilesetData();
        //Assert::IsTrue(tsd.IsObject());
        EXPECT_TRUE(tsd.HasMember("g.s.png"));

        const auto& tgd = mo.getTileGroups();
        EXPECT_TRUE(tgd.IsObject()) << "TileGroups is not an object";
        EXPECT_TRUE(tgd.HasMember("g.s.g.s")) << "TileGroups is missing ""g.s.g.s""";
        EXPECT_TRUE(tgd.HasMember("g.s.s.g")) << "TileGroups is missing ""g.s.s.g""";
    }
    const auto& ta = mo.getTerrainHypergraph();
    auto it = ta.at("g").cbegin();
    EXPECT_NE(std::find((*it).cbegin(), (*it).cend(), "s"), (*it).cend());
    EXPECT_EQ(32, (*mo.getTilesetData().FindMember("resolution")).value.GetInt()) << "Incorrect resolution";
}