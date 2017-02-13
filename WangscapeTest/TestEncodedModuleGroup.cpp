#include <gtest/gtest.h>

#include <memory>

#include <noise/ModuleGroup.h>
#include <noise/codecs/EncodedModuleGroupCodec.h>
#include <noise/EncodedModuleGroup.h>
#include <fstream>
#include <iostream>

#include "removeWhitespace.h"

class TestEncodedModuleGroup : public ::testing::Test
{
};

TEST_F(TestEncodedModuleGroup, TestFullGroupDecode)
{
    std::string filename("WangscapeTest/codecs/examples/ModuleGroup.json");
    std::ifstream ifs(filename);
    if (!ifs.good())
    {
        throw std::runtime_error("Could not open example JSON module file");
    }

    std::string str{std::istreambuf_iterator<char>(ifs),
        std::istreambuf_iterator<char>()};

    noise::EncodedModuleGroup emg;
    emg = spotify::json::decode<noise::EncodedModuleGroup>(str);
    emg.decode();
    auto decoded_modules = emg.moduleGroup;
    {
        std::set<noise::module::Module*, std::less<noise::module::Module*>> unique_modules;
        std::transform(decoded_modules->getModules().cbegin(),
                       decoded_modules->getModules().cend(),
                       std::inserter(unique_modules, unique_modules.begin()),
                       [](const auto& m)
        {
            return &m.second->getModule();
        });
        EXPECT_EQ(8, unique_modules.size());
    }
    const noise::module::Module& input_1 = decoded_modules->getModules().at("INPUT_1")->getModule();
    const noise::module::Module& input_2 = decoded_modules->getModules().at("INPUT_2")->getModule();
    const noise::module::Module& generator_1 = decoded_modules->getModules().at("generator_1")->getModule();
    const noise::module::Module& generator_2 = decoded_modules->getModules().at("generator_2")->getModule();
    const noise::module::Module& generator_3 = decoded_modules->getModules().at("generator_3")->getModule();
    const noise::module::Module& displace_module = decoded_modules->getModules().at("displace_module")->getModule();
    const noise::module::Module& blend_module = decoded_modules->getModules().at("blend_module")->getModule();
    const noise::module::Module& output = decoded_modules->getModules().at("OUTPUT")->getModule();

    const noise::module::Blend& blend_module_cast = static_cast<const noise::module::Blend&>(blend_module);
    const noise::module::Displace& displace_module_cast = static_cast<const noise::module::Displace&>(displace_module);

    EXPECT_EQ(&input_1, &displace_module_cast.GetSourceModule(0));
    EXPECT_EQ(&generator_1, &displace_module_cast.GetXDisplaceModule());
    EXPECT_EQ(&generator_2, &displace_module_cast.GetYDisplaceModule());
    EXPECT_EQ(&generator_3, &displace_module_cast.GetZDisplaceModule());

    EXPECT_EQ(&generator_3, &blend_module_cast.GetSourceModule(0));
    EXPECT_EQ(&generator_2, &blend_module_cast.GetSourceModule(1));
    EXPECT_EQ(&input_2, &blend_module_cast.GetControlModule());

    EXPECT_EQ(&displace_module, &output.GetSourceModule(0));

    const noise::module::QuadrantSelector& output_cast = static_cast<const noise::module::QuadrantSelector&>(output);
    EXPECT_EQ(false, output_cast.GetTranslate(0));
    EXPECT_EQ(false, output_cast.GetTranslate(1));
    EXPECT_EQ(false, output_cast.GetTranslate(2));
    decoded_modules->setQuadrant(false, true, false);
    EXPECT_EQ(true, output_cast.GetTranslate(0));
    EXPECT_EQ(false, output_cast.GetTranslate(1));
    EXPECT_EQ(true, output_cast.GetTranslate(2));

    const noise::module::Perlin& generator_1_cast = static_cast<const noise::module::Perlin&>(generator_1);
    int seed = generator_1_cast.GetSeed();
    decoded_modules->setSeeds(394857);
    EXPECT_NE(seed, generator_1_cast.GetSeed());

}
