#include <gtest/gtest.h>

#include <noise/module/codecs/PerlinCodec.h>

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
