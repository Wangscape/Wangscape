#include <gtest/gtest.h>

#include <boost/filesystem.hpp>

#include <Options.h>
#include <OptionsManager.h>

class TestOptions : public ::testing::Test {
protected:
    std::string filename;
    const Options& options;
    const OptionsManager optionsManager;

    TestOptions() :
        filename("../Wangscape/example/example_options.json"),
        optionsManager(filename),
        options(optionsManager.getOptions())
    {
    };
    ~TestOptions() {};
};

TEST_F(TestOptions, TestOptionsValues)
{
    EXPECT_EQ(options.filename, filename) <<
        "Incorrect options filename";
    EXPECT_TRUE(boost::filesystem::equivalent(
        boost::filesystem::path(options.relativeOutputDirectory),
        boost::filesystem::path("../Wangscape/example/output"))) <<
        "Incorrect relative output directory";
    EXPECT_STREQ(options.outputDirectory.c_str(),
                 "output") <<
        "Incorrect output directory";
    EXPECT_STREQ(options.outputFilenames.tileDataFilename.c_str(),
                 "tiles.json") <<
        "Incorrect tile data filename";
    EXPECT_STREQ(options.outputFilenames.tilesetDataFilename.c_str(),
                 "tilesets.json") <<
        "Incorrect tileset data filename";
    EXPECT_STREQ(options.outputFilenames.tileGroupsFilename.c_str(),
                 "tile_groups.json") <<
        "Incorrect tile groups filename";
    EXPECT_STREQ(options.outputFilenames.terrainHypergraphFilename.c_str(),
                 "terrain_hypergraph.json") <<
        "Incorrect terrain hypergraph filename";
    EXPECT_EQ(options.tileFormat.resolution, 32) <<
        "Incorrect resolution";
    EXPECT_NE(options.terrains.find("g"), options.terrains.cend()) <<
        "Options did not load grass terrain info";
    EXPECT_NE(options.cliques.size(), 0) <<
        "Options did not load any cliques";
}
