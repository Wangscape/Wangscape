#include "TilePartitionerNoise.h"
#include "logging/Logging.h"
#include "noise/RasterValues.h"
#include "noise/module/Pow.h"
#include "tilegen/alpha/CalculatorMax.h"
#include "tilegen/alpha/CalculatorLinear.h"
#include "tilegen/alpha/CalculatorTopTwo.h"
#include "tilegen/alpha/CalculatorDither.h"
#include "noise/RasterImage.h"
#include "noise/ModuleGroup.h"
#include <boost/filesystem.hpp>

#include <iostream>

namespace tilegen
{
namespace partition
{

noise::module::ModulePtr TilePartitionerNoise::makeCornerModule(const Corners& corners,
                                                                bool left, bool top)
{
    TerrainID corner_id = corners[ (left ? 0 : 2) +  (top ? 0 : 1)];
    TerrainID corner_h =  corners[(!left ? 0 : 2) +  (top ? 0 : 1)];
    TerrainID corner_v =  corners[ (left ? 0 : 2) + (!top ? 0 : 1)];

    noise::ModuleGroup& combiner = mNoiseModuleManager.getCombiner();
    noise::ModuleGroup& central = mNoiseModuleManager.getCentral(corner_id);
    noise::ModuleGroup& border_h = 
        left
        ? mNoiseModuleManager.getLeftBorder(left ? corner_id : corner_h,
                                            left ? corner_h : corner_id)
        : mNoiseModuleManager.getBottomRightBorder();
    noise::ModuleGroup& border_v =
        top
        ? mNoiseModuleManager.getTopBorder(top ? corner_id : corner_v,
                                           top ? corner_v : corner_id)
        : mNoiseModuleManager.getBottomRightBorder();
    central.setQuadrant(left, top, false);
    border_h.setQuadrant(left, top, false);
    border_v.setQuadrant(left, top, false);
    combiner.setQuadrant(left, top, false);

    combiner.setInputModuleSource(0, border_h.getOutputModule());
    combiner.setInputModuleSource(1, border_v.getOutputModule());
    combiner.setInputModuleSource(2, central.getOutputModule());
    if (mDebugOutput)
    {
        writeDebugGroup(combiner, Combiner, top, left);
        writeDebugGroup(border_h, HorizontalBorder, top, left);
        writeDebugGroup(border_v, VerticalBorder, top, left);
        writeDebugGroup(central, Central, top, left);
    }
    return combiner.getOutputModule();
}

void TilePartitionerNoise::noiseToAlpha(std::vector<noise::RasterValues<double>>& noise_values,
                                        std::vector<sf::Image>& outputs,
                                        sf::Vector2u resolution) const
{
    std::vector<double> weights((int)CORNERS);
    std::unique_ptr<alpha::CalculatorBase> ac;
    switch (mOptions.calculatorMode)
    {
    case alpha::CalculatorMode::Max:
        ac = std::make_unique<alpha::CalculatorMax>();
        break;
    case alpha::CalculatorMode::Linear:
        ac = std::make_unique<alpha::CalculatorLinear>();
        break;
    case alpha::CalculatorMode::TopTwo:
    {
        auto ac_top_two = std::make_unique<alpha::CalculatorTopTwo>();
        if (mOptions.alphaCalculatorTopTwoPower)
            ac_top_two->power = mOptions.alphaCalculatorTopTwoPower.get();
        ac = std::move(ac_top_two);
        break;
    }
    case alpha::CalculatorMode::Dither:
    {
        auto ac_dither = std::make_unique<alpha::CalculatorDither>();
        if (mOptions.alphaCalculatorTopTwoPower)
            ac_dither->power = mOptions.alphaCalculatorTopTwoPower.get();
        ac = std::move(ac_dither);
        break;
    }
    default:
        throw std::runtime_error("Invalid CalculatorMode");
    }
    for (size_t x = 0; x < resolution.x; x++)
    {
        for (size_t y = 0; y < resolution.y; y++)
        {
            for (int i = 0; i < (int)CORNERS; i++)
            {
                weights[i] = noise_values[i].get(x, y);
            }

            ac->updateAlphas(weights);
            const auto& alphas = ac->getAlphas();
            for (int i = 0; i < (int)CORNERS; i++)
            {
                outputs[i].setPixel(x, y, sf::Color(255, 255, 255, alphas[i]));
            }
        }
    }
}

void TilePartitionerNoise::writeDebugGroup(const noise::ModuleGroup& module_group, tilegen::ModuleGroupRole module_group_role, bool top, bool left)
{
    if (!mDebugModuleWriter)
    {
        logError() << "Requested debug data but didn't provide a debug module writer function!\n";
        throw std::runtime_error("Unable to write debug data");
    }
    for (auto it : module_group.getModules())
    {
        mDebugModuleWriter(tilegen::DebugTilesetID(module_group_role, it.first, top, left), it.second);
    }
}

void TilePartitionerNoise::makePartition(TilePartition & regions, const Corners& corners)
{
    // Prepare noise value storage
    std::vector<noise::RasterValues<double>> noise_values;
    for (int i = 0; i < (int)CORNERS; i++)
    {
        noise_values.emplace_back(mOptions.tileFormat.resolution.x,
                          mOptions.tileFormat.resolution.y,
                          sf::Rect<double>{0, 0, 1, 1});
    }
    // Construct noise modules and render them.
    // Construction and rendering must be done in the same step,
    // because module seeds will be overwritten.
    noise::module::ModulePtr corner_module;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
        {
            corner_module = makeCornerModule(corners, i == 0, j == 0);
            int k = (2 * i) + j;
            noise_values[k].build(corner_module->getModule());
        }
    // Prepare output storage
    std::vector<sf::Image> outputs((int)CORNERS);
    for (int i = 0; i < (int)CORNERS; i++)
        outputs[i].create(mOptions.tileFormat.resolution.x, mOptions.tileFormat.resolution.y);
    // Convert noise values to alpha values
    noiseToAlpha(noise_values, outputs, mOptions.tileFormat.resolution);
    // Convert output images to required format
    for (int i = 0; i < (int)CORNERS; i++)
    {
        sf::Texture t;
        t.loadFromImage(outputs[i]);
        regions.push_back({t, corners[i]});
    }
}

TilePartitionerNoise::TilePartitionerNoise(const Options & options) :
    TilePartitionerBase(options),
    mNoiseModuleManager(options),
    mDebugOutput(options.debugOutput)
{
}

} // namespace partition
} // namespace tilegen
