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
public:
    noise::EncodedModuleGroup emg;
    std::shared_ptr<noise::ModuleGroup> decoded_modules;
    const noise::module::Module& input_1() const
    {
        return decoded_modules->getModules().at("INPUT_1")->getModule();
    }
    const noise::module::Module& input_2()const
    { 
        return decoded_modules->getModules().at("INPUT_2")->getModule();
    }
    const noise::module::Module& generator_1()const
    {
        return decoded_modules->getModules().at("generator_1")->getModule();
    }
    const noise::module::Module& generator_2()const
    {
        return decoded_modules->getModules().at("generator_2")->getModule();
    }
    const noise::module::Module& generator_3()const
    {
        return decoded_modules->getModules().at("generator_3")->getModule();
    }
    const noise::module::Module& displace_module()const
    {
        return decoded_modules->getModules().at("displace_module")->getModule();
    }
    const noise::module::Module& blend_module()const
    {
        return decoded_modules->getModules().at("blend_module")->getModule();
    }
    const noise::module::Module& output() const 
    {
        return decoded_modules->getModules().at("OUTPUT")->getModule();
    }
    TestEncodedModuleGroup()
    {
        std::string filename("WangscapeTest/codecs/examples/ModuleGroup.json");
        std::ifstream ifs(filename);
        if (!ifs.good())
        {
            throw std::runtime_error("Could not open example JSON module file");
        }

        std::string str{std::istreambuf_iterator<char>(ifs),
            std::istreambuf_iterator<char>()};

        emg = spotify::json::decode<noise::EncodedModuleGroup>(str);
        emg.decode();
        decoded_modules = emg.moduleGroup;
    }
};

TEST_F(TestEncodedModuleGroup, TestUniqueModules)
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

TEST_F(TestEncodedModuleGroup, TestCorrectSources)
{

    const noise::module::Blend& blend_module_cast = static_cast<const noise::module::Blend&>(blend_module());
    const noise::module::Displace& displace_module_cast = static_cast<const noise::module::Displace&>(displace_module());

    EXPECT_EQ(&input_1(), &displace_module_cast.GetSourceModule(0));
    EXPECT_EQ(&generator_1(), &displace_module_cast.GetXDisplaceModule());
    EXPECT_EQ(&generator_2(), &displace_module_cast.GetYDisplaceModule());
    EXPECT_EQ(&generator_3(), &displace_module_cast.GetZDisplaceModule());

    EXPECT_EQ(&generator_3(), &blend_module_cast.GetSourceModule(0));
    EXPECT_EQ(&generator_2(), &blend_module_cast.GetSourceModule(1));
    EXPECT_EQ(&input_2(), &blend_module_cast.GetControlModule());

    EXPECT_EQ(&displace_module(), &output().GetSourceModule(0));
}
TEST_F(TestEncodedModuleGroup, TestQuadrantSelection)
{

    const noise::module::QuadrantSelector& output_cast = static_cast<const noise::module::QuadrantSelector&>(output());
    EXPECT_EQ(false, output_cast.GetTranslate(0));
    EXPECT_EQ(false, output_cast.GetTranslate(1));
    EXPECT_EQ(false, output_cast.GetTranslate(2));
    decoded_modules->setQuadrant(false, true, false);
    EXPECT_EQ(true, output_cast.GetTranslate(0));
    EXPECT_EQ(false, output_cast.GetTranslate(1));
    EXPECT_EQ(true, output_cast.GetTranslate(2));
}
TEST_F(TestEncodedModuleGroup, TestSeed)
{
    const noise::module::Perlin& generator_1_cast = static_cast<const noise::module::Perlin&>(generator_1());
    int seed = generator_1_cast.GetSeed();
    decoded_modules->setSeeds(394857);
    EXPECT_NE(seed, generator_1_cast.GetSeed());
}
TEST_F(TestEncodedModuleGroup, TestOutput)
{
    EXPECT_EQ(&output(), &decoded_modules->getOutputModule()->getModule());
}
TEST_F(TestEncodedModuleGroup, TestSetInput)
{
    decoded_modules->setInputModuleSource(0, decoded_modules->getModules().at("generator_2"));
    decoded_modules->setInputModuleSource(1, decoded_modules->getModules().at("generator_1"));
    EXPECT_EQ(&generator_2(), &input_1().GetSourceModule(0));
    EXPECT_EQ(&generator_1(), &input_2().GetSourceModule(0));
}