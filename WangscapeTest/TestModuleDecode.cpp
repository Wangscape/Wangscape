#include <gtest/gtest.h>

#include <type_traits>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>
#include <boost/filesystem.hpp>
#include "DocumentationPath.h"

#include <noise/noise.h>
#include <noise/module/codecs/ModuleCodecs.h>

template<typename T>
class TestModuleDecode : public ::testing::Test
{
public:
    TestModuleDecode()
    {
        exampleModules.emplace_back();
        exampleSources.emplace_back();
    }
    const static std::string type;
    typedef noise::module::Wrapper<T> Wrapper;
    std::vector<Wrapper> exampleModules;
    std::vector<noise::module::NoiseSources> exampleSources;
    void compareModules(const T& expected, const T& actual) {};
    void compareSources(const noise::module::NoiseSources& expected, const noise::module::NoiseSources& actual)
    {
        EXPECT_EQ(bool(expected.sourceModules), bool(actual.sourceModules));
        EXPECT_EQ(bool(expected.controlModule), bool(actual.controlModule));
        EXPECT_EQ(bool(expected.displaceModules), bool(actual.displaceModules));
        if (expected.sourceModules)
            EXPECT_EQ(expected.sourceModules.get(), actual.sourceModules.get());
        if (expected.controlModule)
            EXPECT_EQ(expected.controlModule.get(), actual.controlModule.get());
        if (expected.displaceModules)
            EXPECT_EQ(expected.displaceModules.get(), actual.displaceModules.get());
    }
};

template<> const std::string TestModuleDecode<noise::module::Abs>::type = "Abs";
template<> const std::string TestModuleDecode<noise::module::Add>::type = "Add";
template<> const std::string TestModuleDecode<noise::module::Billow>::type = "Billow";
template<> const std::string TestModuleDecode<noise::module::Blend>::type = "Blend";
template<> const std::string TestModuleDecode<noise::module::Cache>::type = "Cache";
template<> const std::string TestModuleDecode<noise::module::Checkerboard>::type = "Checkerboard";
template<> const std::string TestModuleDecode<noise::module::Clamp>::type = "Clamp";
template<> const std::string TestModuleDecode<noise::module::Const>::type = "Const";
template<> const std::string TestModuleDecode<noise::module::CornerCombinerBase>::type = "CornerCombinerBase";
template<> const std::string TestModuleDecode<noise::module::Curve>::type = "Curve";
template<> const std::string TestModuleDecode<noise::module::Cylinders>::type = "Cylinders";
template<> const std::string TestModuleDecode<noise::module::Displace>::type = "Displace";
template<> const std::string TestModuleDecode<noise::module::Divide>::type = "Divide";
template<> const std::string TestModuleDecode<noise::module::Exp>::type = "Exp";
template<> const std::string TestModuleDecode<noise::module::Exponent>::type = "Exponent";
template<> const std::string TestModuleDecode<noise::module::Forward>::type = "Forward";
template<> const std::string TestModuleDecode<noise::module::GradientX>::type = "GradientX";
template<> const std::string TestModuleDecode<noise::module::GradientY>::type = "GradientY";
template<> const std::string TestModuleDecode<noise::module::GradientZ>::type = "GradientZ";
template<> const std::string TestModuleDecode<noise::module::Invert>::type = "Invert";
template<> const std::string TestModuleDecode<noise::module::Max>::type = "Max";
template<> const std::string TestModuleDecode<noise::module::Min>::type = "Min";
template<> const std::string TestModuleDecode<noise::module::Multiply>::type = "Multiply";
template<> const std::string TestModuleDecode<noise::module::NormLPQ>::type = "NormLPQ";
template<> const std::string TestModuleDecode<noise::module::Perlin>::type = "Perlin";
template<> const std::string TestModuleDecode<noise::module::Pow>::type = "Pow";
template<> const std::string TestModuleDecode<noise::module::Power>::type = "Power";
template<> const std::string TestModuleDecode<noise::module::QuadrantSelector>::type = "QuadrantSelector";
template<> const std::string TestModuleDecode<noise::module::Reciprocal>::type = "Reciprocal";
template<> const std::string TestModuleDecode<noise::module::RidgedMulti>::type = "RidgedMulti";
template<> const std::string TestModuleDecode<noise::module::RotatePoint>::type = "RotatePoint";
template<> const std::string TestModuleDecode<noise::module::ScaleBias>::type = "ScaleBias";
template<> const std::string TestModuleDecode<noise::module::ScalePoint>::type = "ScalePoint";
template<> const std::string TestModuleDecode<noise::module::Select>::type = "Select";
template<> const std::string TestModuleDecode<noise::module::Spheres>::type = "Spheres";
template<> const std::string TestModuleDecode<noise::module::Terrace>::type = "Terrace";
template<> const std::string TestModuleDecode<noise::module::TranslatePoint>::type = "TranslatePoint";
template<> const std::string TestModuleDecode<noise::module::Turbulence>::type = "Turbulence";
template<> const std::string TestModuleDecode<noise::module::Voronoi>::type = "Voronoi";

template<>
TestModuleDecode<noise::module::Abs>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{"mySourceModule"});
}

template<>
TestModuleDecode<noise::module::Add>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{
        "mySourceModule",
            "myOtherSourceModule"});
}

template<>
TestModuleDecode<noise::module::Billow>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->SetSeed(123);
    this->exampleModules[0].module->SetFrequency(2.2);
    this->exampleModules[0].module->SetPersistence(0.5);
    this->exampleModules[0].module->SetLacunarity(1.8);
    this->exampleModules[0].module->SetOctaveCount(14);
    this->exampleModules[0].module->SetNoiseQuality(noise::QUALITY_BEST);
    this->exampleSources.emplace_back();
}

template<>
TestModuleDecode<noise::module::Blend>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{
        "mySourceModule",
            "myOtherSourceModule"});
    this->exampleSources[0].controlModule.emplace("myControlModule");
}

template<>
TestModuleDecode<noise::module::Cache>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{ "mySourceModule" });
}

template<>
TestModuleDecode<noise::module::Checkerboard>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleSources.emplace_back();
}

template<>
TestModuleDecode<noise::module::Clamp>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->SetBounds(-0.5, 1.5);
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{ "mySourceModule" });
}

template<>
TestModuleDecode<noise::module::Const>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->SetConstValue(0.7);
    this->exampleSources.emplace_back();
}

template<>
TestModuleDecode<noise::module::Curve>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->AddControlPoint(-0.5, 0.3);
    this->exampleModules[0].module->AddControlPoint(1.1, 2.2);
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{ "mySourceModule" });
}

template<>
TestModuleDecode<noise::module::Cylinders>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->SetFrequency(2.2);
    this->exampleSources.emplace_back();
}

template<>
TestModuleDecode<noise::module::Displace>::TestModuleDecode()
{
    for (int i = 0; i < 2; i++)
    {
        this->exampleModules.emplace_back();
        this->exampleSources.emplace_back();
        this->exampleSources[i].sourceModules.emplace(std::initializer_list<std::string>{ "mySourceModule" });
        this->exampleSources[i].displaceModules.emplace(std::initializer_list<std::string>{
            "mySourceModuleX",
                "mySourceModuleY",
                "mySourceModuleZ" });
    }
}

template<>
TestModuleDecode<noise::module::Divide>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{
        "mySourceModule",
            "myOtherSourceModule"});
}

template<>
TestModuleDecode<noise::module::Exponent>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->SetExponent(1.1);
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{ "mySourceModule" });
}

template<>
TestModuleDecode<noise::module::Invert>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{ "mySourceModule" });
}

template<>
TestModuleDecode<noise::module::Max>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{
        "mySourceModule",
            "myOtherSourceModule" });
}

template<>
TestModuleDecode<noise::module::Min>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{
        "mySourceModule",
            "myOtherSourceModule" });
}

template<>
TestModuleDecode<noise::module::Multiply>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{
        "mySourceModule",
            "myOtherSourceModule" });
}

template<>
TestModuleDecode<noise::module::Perlin>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->SetSeed(123);
    this->exampleModules[0].module->SetFrequency(2.2);
    this->exampleModules[0].module->SetPersistence(0.5);
    this->exampleModules[0].module->SetLacunarity(1.8);
    this->exampleModules[0].module->SetOctaveCount(14);
    this->exampleModules[0].module->SetNoiseQuality(noise::QUALITY_BEST);
    this->exampleSources.emplace_back();
}

template<>
TestModuleDecode<noise::module::Power>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{
        "mySourceModule",
            "myOtherSourceModule" });
}

template<>
TestModuleDecode<noise::module::Reciprocal>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{ "mySourceModule" });
}

template<>
TestModuleDecode<noise::module::RidgedMulti>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->SetSeed(123);
    this->exampleModules[0].module->SetFrequency(2.2);
    this->exampleModules[0].module->SetLacunarity(1.8);
    this->exampleModules[0].module->SetOctaveCount(14);
    this->exampleModules[0].module->SetNoiseQuality(noise::QUALITY_BEST);
    this->exampleSources.emplace_back();
}

template<>
TestModuleDecode<noise::module::RotatePoint>::TestModuleDecode()
{
    for (int i = 0; i < 2; i++)
    {
        this->exampleModules.emplace_back();
        this->exampleModules[i].module->SetAngles(10.0, 25.5, -45.4);
        this->exampleSources.emplace_back();
        this->exampleSources[i].sourceModules.emplace(std::initializer_list<std::string>{ "mySourceModule" });
    }

}

template<>
TestModuleDecode<noise::module::ScaleBias>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->SetBias(-0.75);
    this->exampleModules[0].module->SetScale(1.1);
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{ "mySourceModule" });
}

template<>
TestModuleDecode<noise::module::ScalePoint>::TestModuleDecode()
{
    for (int i = 0; i < 3; i++)
    {
        this->exampleModules.emplace_back();
        this->exampleModules[i].module->SetScale(2.0, 3.5, -1.4);
        this->exampleSources.emplace_back();
        this->exampleSources[i].sourceModules.emplace(std::initializer_list<std::string>{ "mySourceModule" });
    }
    this->exampleModules[2].module->SetScale(1.4);
}

template<>
TestModuleDecode<noise::module::Voronoi>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->SetSeed(123);
    this->exampleModules[0].module->SetFrequency(2.2);
    this->exampleModules[0].module->SetDisplacement(0.5);
    this->exampleModules[0].module->EnableDistance(true);
    this->exampleSources.emplace_back();
}

template<>
TestModuleDecode<noise::module::Turbulence>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->SetFrequency(2.2);
    this->exampleModules[0].module->SetPower(1.3);
    this->exampleModules[0].module->SetRoughness(3);
    this->exampleModules[0].module->SetSeed(133);
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{ "mySourceModule" });
}

template<>
TestModuleDecode<noise::module::TranslatePoint>::TestModuleDecode()
{
    for (int i = 0; i < 3; i++)
    {
        this->exampleModules.emplace_back();
        this->exampleModules[i].module->SetTranslation(2.0, 3.5, -1.4);
        this->exampleSources.emplace_back();
        this->exampleSources[i].sourceModules.emplace(std::initializer_list<std::string>{ "mySourceModule" });
    }
    this->exampleModules[2].module->SetTranslation(4.3);
}

template<>
TestModuleDecode<noise::module::Terrace>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->AddControlPoint(-0.5);
    this->exampleModules[0].module->AddControlPoint(0.25);
    this->exampleModules[0].module->AddControlPoint(0.7);
    this->exampleModules[0].module->AddControlPoint(0.9);
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{ "mySourceModule" });
}

template<>
TestModuleDecode<noise::module::Spheres>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->SetFrequency(2.2);
    this->exampleSources.emplace_back();
}

template<>
TestModuleDecode<noise::module::Select>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->SetBounds(0.2, 0.87);
    this->exampleModules[0].module->SetEdgeFalloff(0.25);
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{
        "mySourceModule",
            "myOtherSourceModule" });
    this->exampleSources[0].controlModule.emplace("myControlModule");
}

template<>
TestModuleDecode<noise::module::CornerCombinerBase>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->SetPower(3.5);
    this->exampleSources.emplace_back();
}

template<>
TestModuleDecode<noise::module::Exp>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->SetBase(2.2);
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{
        "mySourceModule"});
}

template<>
TestModuleDecode<noise::module::Forward>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{
        "mySourceModule"});
}

template<>
TestModuleDecode<noise::module::NormLPQ>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->SetP(2.3);
    this->exampleModules[0].module->SetQ(1.4);
    this->exampleSources.emplace_back();
}

template<>
TestModuleDecode<noise::module::Pow>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->SetExponent(3.3);
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{
        "mySourceModule"});
}

template<>
TestModuleDecode<noise::module::QuadrantSelector>::TestModuleDecode()
{
    this->exampleModules.emplace_back();
    this->exampleModules[0].module->SetTranslateIgnored(false, false, true);
    this->exampleSources.emplace_back();
    this->exampleSources[0].sourceModules.emplace(std::initializer_list<std::string>{
        "mySourceModule"});
}

template<>
void TestModuleDecode<noise::module::Billow>::compareModules(const noise::module::Billow& expected, const noise::module::Billow& actual)
{
    EXPECT_EQ(expected.GetFrequency(), actual.GetFrequency());
    EXPECT_EQ(expected.GetLacunarity(), actual.GetLacunarity());
    EXPECT_EQ(expected.GetNoiseQuality(), actual.GetNoiseQuality());
    EXPECT_EQ(expected.GetOctaveCount(), actual.GetOctaveCount());
    EXPECT_EQ(expected.GetPersistence(), actual.GetPersistence());
    EXPECT_EQ(expected.GetSeed(), actual.GetSeed());
}

template<>
void TestModuleDecode<noise::module::Clamp>::compareModules(const noise::module::Clamp& expected, const noise::module::Clamp& actual)
{
    EXPECT_EQ(expected.GetLowerBound(), actual.GetLowerBound());
    EXPECT_EQ(expected.GetUpperBound(), actual.GetUpperBound());
}

template<>
void TestModuleDecode<noise::module::CornerCombinerBase>::compareModules(const noise::module::CornerCombinerBase& expected, const noise::module::CornerCombinerBase& actual)
{
    EXPECT_EQ(expected.GetPower(), actual.GetPower());
}

bool operator==(noise::module::ControlPoint lhs, noise::module::ControlPoint rhs)
{
    return std::tie(lhs.inputValue, lhs.outputValue) == std::tie(rhs.inputValue, rhs.outputValue);
}

template<>
void TestModuleDecode<noise::module::Curve>::compareModules(const noise::module::Curve& expected, const noise::module::Curve& actual)
{
    EXPECT_EQ(expected.GetControlPointCount(), actual.GetControlPointCount());
    for (int i = 0; i < expected.GetControlPointCount(); i++)
    {
        EXPECT_TRUE(expected.GetControlPointArray()[i] == actual.GetControlPointArray()[i]);
    }
}

template<>
void TestModuleDecode<noise::module::Cylinders>::compareModules(const noise::module::Cylinders& expected, const noise::module::Cylinders& actual)
{
    EXPECT_EQ(expected.GetFrequency(), actual.GetFrequency());
}

template<>
void TestModuleDecode<noise::module::Exp>::compareModules(const noise::module::Exp& expected, const noise::module::Exp& actual)
{
    EXPECT_EQ(expected.GetBase(), actual.GetBase());
}

template<>
void TestModuleDecode<noise::module::Exponent>::compareModules(const noise::module::Exponent& expected, const noise::module::Exponent& actual)
{
    EXPECT_EQ(expected.GetExponent(), actual.GetExponent());
}

template<>
void TestModuleDecode<noise::module::Perlin>::compareModules(const noise::module::Perlin& expected, const noise::module::Perlin& actual)
{
    EXPECT_EQ(expected.GetFrequency(), actual.GetFrequency());
    EXPECT_EQ(expected.GetLacunarity(), actual.GetLacunarity());
    EXPECT_EQ(expected.GetNoiseQuality(), actual.GetNoiseQuality());
    EXPECT_EQ(expected.GetOctaveCount(), actual.GetOctaveCount());
    EXPECT_EQ(expected.GetPersistence(), actual.GetPersistence());
    EXPECT_EQ(expected.GetSeed(), actual.GetSeed());
}

template<>
void TestModuleDecode<noise::module::QuadrantSelector>::compareModules(const noise::module::QuadrantSelector& expected, const noise::module::QuadrantSelector& actual)
{
    EXPECT_EQ(expected.GetTranslate(0), actual.GetTranslate(0));
    EXPECT_EQ(expected.GetTranslate(1), actual.GetTranslate(1));
    EXPECT_EQ(expected.GetTranslate(2), actual.GetTranslate(2));
    EXPECT_EQ(expected.GetTranslateIgnored(0), actual.GetTranslateIgnored(0));
    EXPECT_EQ(expected.GetTranslateIgnored(1), actual.GetTranslateIgnored(1));
    EXPECT_EQ(expected.GetTranslateIgnored(2), actual.GetTranslateIgnored(2));
}

template<>
void TestModuleDecode<noise::module::RidgedMulti>::compareModules(const noise::module::RidgedMulti& expected, const noise::module::RidgedMulti& actual)
{
    EXPECT_EQ(expected.GetFrequency(), actual.GetFrequency());
    EXPECT_EQ(expected.GetLacunarity(), actual.GetLacunarity());
    EXPECT_EQ(expected.GetNoiseQuality(), actual.GetNoiseQuality());
    EXPECT_EQ(expected.GetOctaveCount(), actual.GetOctaveCount());
    EXPECT_EQ(expected.GetSeed(), actual.GetSeed());
}

template<>
void TestModuleDecode<noise::module::RotatePoint>::compareModules(const noise::module::RotatePoint& expected, const noise::module::RotatePoint& actual)
{
    EXPECT_EQ(expected.GetXAngle(), actual.GetXAngle());
    EXPECT_EQ(expected.GetYAngle(), actual.GetYAngle());
    EXPECT_EQ(expected.GetZAngle(), actual.GetZAngle());
}

template<>
void TestModuleDecode<noise::module::ScaleBias>::compareModules(const noise::module::ScaleBias& expected, const noise::module::ScaleBias& actual)
{
    EXPECT_EQ(expected.GetScale(), actual.GetScale());
    EXPECT_EQ(expected.GetBias(), actual.GetBias());
}

template<>
void TestModuleDecode<noise::module::ScalePoint>::compareModules(const noise::module::ScalePoint& expected, const noise::module::ScalePoint& actual)
{
    EXPECT_EQ(expected.GetXScale(), actual.GetXScale());
    EXPECT_EQ(expected.GetYScale(), actual.GetYScale());
    EXPECT_EQ(expected.GetZScale(), actual.GetZScale());
}

template<>
void TestModuleDecode<noise::module::Select>::compareModules(const noise::module::Select& expected, const noise::module::Select& actual)
{
    EXPECT_EQ(expected.GetLowerBound(), actual.GetLowerBound());
    EXPECT_EQ(expected.GetUpperBound(), actual.GetUpperBound());
    EXPECT_EQ(expected.GetEdgeFalloff(), actual.GetEdgeFalloff());
}

template<>
void TestModuleDecode<noise::module::Terrace>::compareModules(const noise::module::Terrace& expected, const noise::module::Terrace& actual)
{
    EXPECT_EQ(expected.GetControlPointCount(), actual.GetControlPointCount());
    EXPECT_EQ(expected.IsTerracesInverted(), actual.IsTerracesInverted());
    for (int i = 0; i < expected.GetControlPointCount(); i++)
    {
        EXPECT_EQ(expected.GetControlPointArray()[i], actual.GetControlPointArray()[i]);
    }
}

template<>
void TestModuleDecode<noise::module::TranslatePoint>::compareModules(const noise::module::TranslatePoint& expected, const noise::module::TranslatePoint& actual)
{
    EXPECT_EQ(expected.GetXTranslation(), actual.GetXTranslation());
    EXPECT_EQ(expected.GetYTranslation(), actual.GetYTranslation());
    EXPECT_EQ(expected.GetZTranslation(), actual.GetZTranslation());
}

template<>
void TestModuleDecode<noise::module::Turbulence>::compareModules(const noise::module::Turbulence& expected, const noise::module::Turbulence& actual)
{
    EXPECT_EQ(expected.GetFrequency(), actual.GetFrequency());
    EXPECT_EQ(expected.GetPower(), actual.GetPower());
    EXPECT_EQ(expected.GetRoughnessCount(), actual.GetRoughnessCount());
    EXPECT_EQ(expected.GetSeed(), actual.GetSeed());
}

template<>
void TestModuleDecode<noise::module::Voronoi>::compareModules(const noise::module::Voronoi& expected, const noise::module::Voronoi& actual)
{
    EXPECT_EQ(expected.GetFrequency(), actual.GetFrequency());
    EXPECT_EQ(expected.IsDistanceEnabled(), actual.IsDistanceEnabled());
}



typedef ::testing::Types<
    noise::module::Abs,
    noise::module::Add,
    noise::module::Billow,
    noise::module::Blend,
    noise::module::Cache,
    noise::module::Checkerboard,
    noise::module::Clamp,
    noise::module::Const,
    noise::module::CornerCombinerBase,
    noise::module::Curve,
    noise::module::Cylinders,
    noise::module::Displace,
    noise::module::Divide,
    noise::module::Exp,
    noise::module::Exponent,
    noise::module::Forward,
    noise::module::GradientX,
    noise::module::GradientY,
    noise::module::GradientZ,
    noise::module::Invert,
    noise::module::Max,
    noise::module::Min,
    noise::module::Multiply,
    noise::module::NormLPQ,
    noise::module::Perlin,
    noise::module::Pow,
    noise::module::Power,
    noise::module::QuadrantSelector,
    noise::module::Reciprocal,
    noise::module::RidgedMulti,
    noise::module::RotatePoint,
    noise::module::ScaleBias,
    noise::module::ScalePoint,
    noise::module::Select,
    noise::module::Spheres,
    noise::module::Terrace,
    noise::module::TranslatePoint,
    noise::module::Turbulence,
    noise::module::Voronoi
>
ModuleDecodeArgs;

TYPED_TEST_CASE(TestModuleDecode, ModuleDecodeArgs);

TYPED_TEST(TestModuleDecode, TestModuleDecode)
{
    int count = 0;
    EXPECT_EQ(this->exampleModules.size(), this->exampleSources.size());
    auto examples_dir = boost::filesystem::path(getDocumentationPath()) / "tests";
    for (size_t i = 0; i < this->exampleModules.size(); i++)
    {
        std::string filename = (examples_dir / (this->type + std::to_string(i + 1) + ".json")).string();
        std::ifstream ifs(filename);
        if (!ifs.good())
        {
            throw std::runtime_error("Could not open example JSON module file:" + filename);
        }

        std::shared_ptr<noise::module::Wrapper<TypeParam>> decoded_module;
        noise::module::NoiseSources decoded_sources;
        std::string str{std::istreambuf_iterator<char>(ifs),
            std::istreambuf_iterator<char>()};
        try
        {
            decoded_module = spotify::json::decode<std::shared_ptr<noise::module::Wrapper<TypeParam>>>(str.c_str());
            decoded_sources = spotify::json::decode<noise::module::NoiseSources>(str.c_str());
        }
        catch (const spotify::json::decode_exception& e)
        {
            std::cout << "spotify::json::decode_exception encountered at "
                << e.offset()
                << ": "
                << e.what();
            throw;
        }
        this->compareModules(*this->exampleModules[i].module, *decoded_module->module);
        this->compareSources(this->exampleSources[i], decoded_sources);
    }
}
