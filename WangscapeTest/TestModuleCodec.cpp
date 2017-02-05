#include <gtest/gtest.h>

#include <memory>
#include <algorithm>
#include <string>

#include <noise/module/codecs/ModuleCodecs.h>
#include "removeWhitespace.h"

class TestModuleCodec : public ::testing::Test
{
protected:
    void remove_whitespace(std::string& s)
    {
        s.erase(std::remove_if(s.begin(),
                               s.end(),
                               [](char c) { return std::isspace(c, std::locale()); }),
                s.end());
    }
};

TEST_F(TestModuleCodec, TestPerlinEncode)
{
    auto p = std::make_shared<noise::module::Wrapper<noise::module::Perlin>>();
    std::string s(spotify::json::encode(p));
    std::string expected(R"(
{
    "type" : "Perlin",
    "Seed" : 0,
    "Frequency" : 1,
    "Persistence" : 0.5,
    "Lacunarity" : 2,
    "OctaveCount" : 6,
    "NoiseQuality" : "Standard"
}
)");
    removeWhitespace(expected);
    ASSERT_EQ(expected, s);
}

TEST_F(TestModuleCodec, TestPerlinDecode)
{
    std::string s(R"(
{
    "type" : "Perlin",
    "Frequency" : 1.7,
    "Lacunarity" : 0.999,
    "NoiseQuality" : "Fast",
    "OctaveCount" : 8,
    "Persistence" : 0.001,
    "Seed" : 101
}
)");
    auto p = spotify::json::decode<std::shared_ptr<noise::module::Wrapper<noise::module::Perlin>>>(s);
    EXPECT_EQ(1.7, p->module.GetFrequency());
    EXPECT_EQ(0.999, p->module.GetLacunarity());
    EXPECT_EQ(noise::QUALITY_FAST, p->module.GetNoiseQuality());
    EXPECT_EQ(8, p->module.GetOctaveCount());
    EXPECT_EQ(0.001, p->module.GetPersistence());
    EXPECT_EQ(101, p->module.GetSeed());
}

TEST_F(TestModuleCodec, TestVoronoiEncode)
{
    auto v = std::make_shared<noise::module::Wrapper<noise::module::Voronoi>>();
    std::string s(spotify::json::encode(v));
    std::string expected(R"(
{
    "type" : "Voronoi",
    "Frequency" : 1,
    "Displacement" : 1,
    "DistanceEnabled" : false,
    "Seed" : 0
}
)");
    removeWhitespace(expected);
    ASSERT_EQ(expected, s);
}

TEST_F(TestModuleCodec, TestVoronoiDecode)
{
    std::string s(R"(
{
    "type" : "Voronoi" ,
    "Frequency" : 2.7,
    "Displacement" : 3.1,
    "DistanceEnabled" : true,
    "Seed" : 47
}
)");
    auto v = spotify::json::decode<std::shared_ptr<noise::module::Wrapper<noise::module::Voronoi>>>(s);
    EXPECT_EQ(2.7, v->module.GetFrequency()) << s;
    EXPECT_EQ(3.1, v->module.GetDisplacement()) << s;
    EXPECT_TRUE(v->module.IsDistanceEnabled()) << s;
    EXPECT_EQ(47, v->module.GetSeed()) << s;
}
