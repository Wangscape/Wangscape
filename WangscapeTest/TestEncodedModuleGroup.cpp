#include <gtest/gtest.h>

#include <memory>

#include <noise/module/codecs/NoiseSourcesCodec.h>
#include <noise/EncodedModuleGroup.h>

class TestEncodedModuleGroup : public ::testing::Test {
protected:
};

TEST_F(TestEncodedModuleGroup, TestFullGroupDecode)
{
    std::string s =
R"({
    "perlin_example":{
        "type":"Perlin",
        "Frequency" : 1.7,
        "Lacunarity" : 0.999,
        "NoiseQuality" : "Fast",
        "OctaveCount" : 8,
        "Persistence" : 0.001,
        "Seed" : 101
    },
    "voronoi_example":{
        "type":"Voronoi",
        "Frequency" : 2.7,
        "Displacement" : 3.1,
        "DistanceEnabled" : true,
        "Seed" : 47
    },
    "add_example":{
        "type":"Add",
        "SourceModule":[
            "voronoi_example",
            "perlin_example"
        ]
    }
})";
    noise::EncodedModuleGroup emg;
    emg.encodedModules = spotify::json::decode<noise::EncodedModuleGroup::EncodedModuleMap>(s);
    auto decoded_modules = emg.decode();

    const noise::module::ModulePtr perlin_p = decoded_modules.at("perlin_example");
    const noise::module::Perlin& perlin_cast = static_cast<noise::module::Perlin&>(perlin_p->getModule());
    EXPECT_EQ(1.7, perlin_cast.GetFrequency());
    EXPECT_EQ(0.999, perlin_cast.GetLacunarity());
    EXPECT_EQ(noise::QUALITY_FAST, perlin_cast.GetNoiseQuality());
    EXPECT_EQ(8, perlin_cast.GetOctaveCount());
    EXPECT_EQ(0.001, perlin_cast.GetPersistence());
    EXPECT_EQ(101, perlin_cast.GetSeed());

    const noise::module::ModulePtr voronoi_p = decoded_modules.at("voronoi_example");
    const noise::module::Voronoi& voronoi_cast = static_cast<noise::module::Voronoi&>(voronoi_p->getModule());
    EXPECT_EQ(2.7, voronoi_cast.GetFrequency());
    EXPECT_EQ(3.1, voronoi_cast.GetDisplacement());
    EXPECT_TRUE(voronoi_cast.IsDistanceEnabled());
    EXPECT_EQ(47, voronoi_cast.GetSeed());

    const noise::module::ModulePtr add_p = decoded_modules.at("add_example");

    const noise::module::Module* add_source_0 = &(add_p->getModule().GetSourceModule(0));
    const noise::module::Module* add_source_1 = &(add_p->getModule().GetSourceModule(1));
    const noise::module::Module* perlin_module = &(perlin_p->getModule());
    const noise::module::Module* voronoi_module = &(voronoi_p->getModule());

    EXPECT_TRUE(add_source_0 == perlin_module ||
                add_source_0 == voronoi_module);
    EXPECT_TRUE(add_source_1 == perlin_module ||
                add_source_1 == voronoi_module);

    double pv = perlin_p->getValue(1.1, 2.2, 3.3);
    double vv = voronoi_p->getValue(1.1, 2.2, 3.3);
    double av = add_p->getValue(1.1, 2.2, 3.3);
    EXPECT_EQ(pv + vv, av);
}

TEST_F(TestEncodedModuleGroup, TestNoiseSourcesDecodeEmpty)
{
    noise::module::NoiseSources ns;
    ns = spotify::json::decode<noise::module::NoiseSources>(R"({})");
    EXPECT_FALSE(ns.sourceModules);
    EXPECT_FALSE(ns.controlModule);
    EXPECT_FALSE(ns.displaceModules);
}

TEST_F(TestEncodedModuleGroup, TestNoiseSourcesDecodeFull)
{
    noise::module::NoiseSources ns;
    ns = spotify::json::decode<noise::module::NoiseSources>(
        R"({
            "SourceModule":["a", "b", "c"],
            "ControlModule":"z",
            "DisplaceModule":["s", "t", "u"]
        })");
    EXPECT_TRUE(ns.sourceModules);
    EXPECT_TRUE(ns.controlModule);
    EXPECT_TRUE(ns.displaceModules);
    EXPECT_EQ("c", ns.sourceModules.get()[2]);
    EXPECT_EQ("z", ns.controlModule.get());
    EXPECT_EQ("t", ns.displaceModules.get()[1]);
}

TEST_F(TestEncodedModuleGroup, TestNoiseSourcesEncodeEmpty)
{
    noise::module::NoiseSources ns;
    std::string s = spotify::json::encode<noise::module::NoiseSources>(ns);
    EXPECT_EQ(R"({})", s);
}

TEST_F(TestEncodedModuleGroup, TestNoiseSourcesEncodeFull)
{
    noise::module::NoiseSources ns;
    ns.sourceModules.emplace(std::initializer_list<std::string>({"a", "b", "c"}));
    ns.controlModule.emplace("z");
    ns.displaceModules.emplace(std::initializer_list<std::string>({"s", "t", "u"}));
    std::string s = spotify::json::encode<noise::module::NoiseSources>(ns);
    EXPECT_EQ(R"({"SourceModule":["a","b","c"],"ControlModule":"z","DisplaceModule":["s","t","u"]})", s);
}
