#include <gtest/gtest.h>

#include <boost/filesystem.hpp>

#include <Options.h>
#include <OptionsManager.h>

#include "TestRequiringOptions.h"

class TestOptions : public TestRequiringOptions
{
protected:
    TestOptions() :
        TestRequiringOptions()
    {
    }
};

TEST_F(TestOptions, TestOptionsValues)
{
    EXPECT_EQ(options.filename, optionsFilename) <<
        "Incorrect options filename";
    boost::filesystem::path expected_output_dir(options.directory);
    expected_output_dir /= "output";
    EXPECT_TRUE(boost::filesystem::equivalent(
        boost::filesystem::path(options.relativeOutputDirectory),
        expected_output_dir)) <<
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
