#include <gtest/gtest.h>

#include <Options.h>

class TestOptions : public ::testing::Test {
protected:
    std::string filename;
    const Options options;

    TestOptions() :
        filename("../Wangscape/example/example_options.json"),
        options(filename)
    {

    };
    ~TestOptions() {};
};

TEST_F(TestOptions, TestOptionsValues)
{
    EXPECT_EQ(options.filename, filename) <<
        "Incorrect options filename";
    EXPECT_STREQ(options.relativeOutputDirectory.c_str(),
                 "../Wangscape/example/output") <<
        "Incorrect relative output directory";
    EXPECT_STREQ(options.outputDirectory.c_str(),
                 "output") <<
        "Incorrect output directory";
    EXPECT_STREQ(options.tileDataFilename.c_str(),
                 "tile_data.json") <<
        "Incorrect tile data filename";
    EXPECT_STREQ(options.tilesetDataFilename.c_str(),
                 "tileset_data.json") <<
        "Incorrect tileset data filename";
    EXPECT_STREQ(options.tileGroupsFilename.c_str(),
                 "tile_groups.json") <<
        "Incorrect tile groups filename";
    EXPECT_STREQ(options.terrainHypergraphFilename.c_str(),
                 "terrain_hypergraph.json") <<
        "Incorrect terrain hypergraph filename";
    EXPECT_EQ(options.resolution, 32) <<
        "Incorrect resolution";
    EXPECT_NE(options.terrains.find("g"), options.terrains.cend()) <<
        "Options did not load grass terrain info";
    EXPECT_NE(options.cliques.size(), 0) <<
        "Options did not load any cliques";
}