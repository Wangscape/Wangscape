#include <gtest/gtest.h>

#include <memory>
#include <algorithm>
#include <string>

#include <noise/module/codecs/ModuleCodecs.h>
#include "removeWhitespace.h"
//
//template<typename M>
//class TestModuleCodecT : public ::testing::Test
//{
//public:
//    TestModuleCodecT();
//
//    typedef std::pair<std::string, std::shared_ptr<noise::module::Wrapper<M>>> CodecTestCase;
//    std::vector<CodecTestCase> decodeTestCases;
//    CodecTestCase encodeTestCase;
//
//    void expectModuleEquality(const M& expected, const M& actual);
//};
//
//template<>
//TestModuleCodecT<noise::module::Abs>::TestModuleCodecT()
//{
//    encodeTestCase.first = R"(
//{
//    "type" : "Abs",
//}
//)";
//    encodeTestCase.second = std::make_shared<noise::module::Wrapper<noise::module::Abs>>();
//}
//
//typedef ::testing::Types<
//    noise::module::Abs,
//    noise::module::Perlin,
//    noise::module::Voronoi
//>
//ModuleCodecArgs;
//
//TYPED_TEST_CASE(TestModuleCodecT, ModuleCodecArgs);
//
//TYPED_TEST(TestModuleCodecT, TestDecode)
//{
//    for (const auto& test_case : decodeTestCases)
//    {
//        std::shared_ptr<noise::module::Wrapper<TypeParam>> decoded_module;
//        EXPECT_NO_THROW(decoded_module = spotify::json::decode<std::shared_ptr<noise::module::Wrapper<TypeParam>>>(test_case.first););
//        this->expectModuleEquality(test_case.second->module, decoded_module->module);
//    }
//}
//
//TYPED_TEST(TestModuleCodecT, TestEncode)
//{
//    std::string s;
//    EXPECT_NO_THROW(s = spotify::json::encode<std::shared_ptr<noise::module::Wrapper<TypeParam>>>(this->encodeTestCase.second););
//    removeWhitespace(this->encodeTestCase.first);
//    EXPECT_EQ(this->encodeTestCase.first, s);
//}
//

class TestModuleCodec : public ::testing::Test
{
};

TEST_F(TestModuleCodec, TestAbsEncode)
{
    auto module_p = std::make_shared<noise::module::Wrapper<noise::module::Abs>>();
    std::string s(spotify::json::encode(module_p));
    std::string expected(R"(
{
    "type" : "Abs",
}
)");
    removeWhitespace(expected);
    ASSERT_EQ(expected, s);
}

TEST_F(TestModuleCodec, TestAbsDecode)
{
    std::string s(R"(
{
    "type" : "Abs",
}
)");
    std::shared_ptr<noise::module::Wrapper<noise::module::Abs>> module_p;
    EXPECT_NO_THROW(module_p = spotify::json::decode<std::shared_ptr<noise::module::Wrapper<noise::module::Abs>>>(s););
}

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
