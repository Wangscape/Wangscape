#include <gtest/gtest.h>

#include <memory>

#include <noise/module/codecs/PerlinWrapperCodec.h>
#include <noise/module/codecs/VoronoiWrapperCodec.h>
#include <noise/module/codecs/NoiseSourcesCodec.h>

class TestModuleCodec : public ::testing::Test {
protected:
};

TEST_F(TestModuleCodec, TestPerlinEncode)
{
    auto p = std::make_shared<noise::module::Wrapper<noise::module::Perlin>>();
    std::string s(spotify::json::encode(p));
    ASSERT_EQ(s, "{\"type\":\"Perlin\",\"Frequency\":1,\"Lacunarity\":2,"
              "\"NoiseQuality\":\"Standard\",\"OctaveCount\":6,\"Persistence\":0.5,\"Seed\":0}");
}

TEST_F(TestModuleCodec, TestVoronoiEncode)
{
    auto v = std::make_shared<noise::module::Wrapper<noise::module::Voronoi>>();
    std::string s(spotify::json::encode(v));
    ASSERT_EQ(s, "{\"type\":\"Voronoi\",\"Frequency\":1,"
              "\"Displacement\":1,\"DistanceEnabled\":false,\"Seed\":0}");
}

TEST_F(TestModuleCodec, TestPerlinDecode)
{
    std::string s("{\"type\":\"Perlin\", \"Frequency\" : 1.7, \"Lacunarity\" : 0.999, "
                  "\"NoiseQuality\" : \"Fast\", \"OctaveCount\" : 8, "
                  "\"Persistence\" : 0.001, \"Seed\" : 101}");
    auto p = spotify::json::decode<std::shared_ptr<noise::module::Wrapper<noise::module::Perlin>>>(s);
    EXPECT_EQ(1.7, p->module.GetFrequency()) << s;
    EXPECT_EQ(0.999, p->module.GetLacunarity()) << s;
    EXPECT_EQ(noise::QUALITY_FAST, p->module.GetNoiseQuality()) << s;
    EXPECT_EQ(8, p->module.GetOctaveCount()) << s;
    EXPECT_EQ(0.001, p->module.GetPersistence()) << s;
    EXPECT_EQ(101, p->module.GetSeed()) << s;
}

TEST_F(TestModuleCodec, TestVoronoiDecode)
{
    std::string s("{\"type\":\"Voronoi\", \"Frequency\" : 2.7, \"Displacement\" : 3.1, "
                  "\"DistanceEnabled\" : true, \"Seed\" : 47}");
    auto v = spotify::json::decode<std::shared_ptr<noise::module::Wrapper<noise::module::Voronoi>>>(s);
    EXPECT_EQ(2.7, v->module.GetFrequency()) << s;
    EXPECT_EQ(3.1, v->module.GetDisplacement()) << s;
    EXPECT_TRUE(v->module.IsDistanceEnabled()) << s;
    EXPECT_EQ(47, v->module.GetSeed()) << s;
}
