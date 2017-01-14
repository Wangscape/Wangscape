#include <gtest/gtest.h>

#include <noise/module/codecs/PerlinCodec.h>
#include <noise/module/codecs/VoronoiCodec.h>

class TestModuleCodec : public ::testing::Test {
protected:
    TestModuleCodec()
    {

    };
    ~TestModuleCodec() {};
};

TEST_F(TestModuleCodec, TestPerlinCodec)
{
    noise::module::Perlin p;
    std::string s(spotify::json::encode(p));
    ASSERT_FALSE(true) << s;
}

TEST_F(TestModuleCodec, TestVoronoiCodec)
{
    noise::module::Voronoi v;
    std::string s(spotify::json::encode(v));
    ASSERT_FALSE(true) << s;
}