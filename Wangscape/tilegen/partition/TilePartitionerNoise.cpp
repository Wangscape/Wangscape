#include "TilePartitionerNoise.h"
#include "noise/RasterValues.h"
#include "noise/module/Pow.h"
#include "tilegen/alpha/CalculatorMax.h"
#include "tilegen/alpha/CalculatorLinear.h"
#include "noise/RasterImage.h"
#include "noise/ModuleGroup.h"

#include <iostream>

namespace tilegen
{
namespace partition
{

noise::module::ModulePtr TilePartitionerNoise::makeCornerModule(const Corners& corners,
                                                                bool left, bool top)
{
    TerrainID corner_id = corners[ (left ? 0 : 1) +  (top ? 0 : 2)];
    TerrainID corner_h =  corners[(!left ? 0 : 1) +  (top ? 0 : 2)];
    TerrainID corner_v =  corners[ (left ? 0 : 1) + (!top ? 0 : 2)];

    noise::ModuleGroup& combiner = mNoiseModuleManager.getCombiner();
    noise::ModuleGroup& central = mNoiseModuleManager.getCentral(corner_id);
    noise::ModuleGroup& border_h = mNoiseModuleManager.getHorizontalBorder(left ? corner_id : corner_h,
                                                                           left ? corner_h : corner_id);
    noise::ModuleGroup& border_v = mNoiseModuleManager.getVerticalBorder(top ? corner_id : corner_v,
                                                                         top ? corner_v : corner_id);
    central.setQuadrant(left, top, false);
    border_h.setQuadrant(left, top, false);
    border_v.setQuadrant(left, top, false);
    combiner.setQuadrant(left, top, false);

    combiner.setInputModuleSource(0, border_h.getOutputModule());
    combiner.setInputModuleSource(1, border_v.getOutputModule());
    combiner.setInputModuleSource(2, central.getOutputModule());
    if (mDebugOutput)
    {
        std::cout << "Writing debug modules for terrains " <<
            corners[0] << ", " <<
            corners[1] << ", " <<
            corners[2] << ", " <<
            corners[3] << ", " <<
            (top ? "top " : "bottom ") <<
            (left ? "left" : "right") <<
            "...\n";
        sf::Image output;
        output.create(256, 256);
        noise::RasterBase::Bounds xy(0, 0, 1, 1);
        noise::RasterImage nmixy(output, xy);
        auto write_map = [&](const noise::module::ModulePtr module,
                             std::string filename,
                             noise::RasterImage& nmi)
        {
            nmi.build(module->getModule());
            output.saveToFile("test/" + filename + ".png");
        };
        auto write_group = [&](const noise::ModuleGroup& mg,
                               std::string mg_name)
        {
            for (auto it : mg.getModules())
            {
                write_map(it.second, mg_name + "_" + it.first, nmixy);
            }
        };
        write_group(central, "central");
        write_group(border_h, "border_h");
        write_group(border_v, "border_v");
        write_group(combiner, "combiner");
        std::cout << "Debug modules written. Press 'q' <ENTER> to stop debugging.\n" <<
            "Press <ENTER> to write the next set...\n";
        int keypress = std::cin.get();
        if (keypress == 'q')
        {
            mDebugOutput = false;
            std::cout << "Debugging cancelled. Generating remaining tilesets as normal...\n";
        }
    }

    return combiner.getOutputModule();
}

void TilePartitionerNoise::noiseToAlpha(std::vector<noise::RasterValues<double>>& noise_values,
                                         std::vector<sf::Image>& outputs,
                                         size_t resolution) const
{
    std::vector<double> weights((int)CORNERS);
    std::unique_ptr<alpha::CalculatorBase> ac;
    switch (mOptions.CalculatorMode)
    {
    case alpha::CalculatorMode::Max:
        ac = std::make_unique<alpha::CalculatorMax>();
        break;
    case alpha::CalculatorMode::Linear:
        ac = std::make_unique<alpha::CalculatorLinear>();
        break;
    default:
        throw std::runtime_error("Invalid CalculatorMode");
    }
    for (size_t x = 0; x < resolution; x++)
    {
        for (size_t y = 0; y < resolution; y++)
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

void TilePartitionerNoise::makePartition(TilePartition & regions, const Corners& corners)
{
    // Prepare noise value storage
    std::vector<noise::RasterValues<double>> noise_values;
    for (int i = 0; i < (int)CORNERS; i++)
    {
        noise_values.emplace_back(mOptions.tileFormat.resolution,
                          mOptions.tileFormat.resolution,
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
        outputs[i].create(mOptions.tileFormat.resolution, mOptions.tileFormat.resolution);
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