#include "TilePartitionerPerlin.h"
#include "noise/module/ModuleFactories.h"
#include "noise/RasterValues.h"
#include "noise/module/Pow.h"
#include "tilegen/alpha/CalculatorMax.h"
#include "tilegen/alpha/CalculatorLinear.h"

namespace tilegen
{
namespace partition
{

Reseedable TilePartitionerPerlin::makeCornerModule(const Corners& corners,
                                                   bool left, bool top)
{
    TerrainID corner_id = corners[ (left ? 0 : 1) +  (top ? 0 : 2)];
    TerrainID corner_h =  corners[(!left ? 0 : 1) +  (top ? 0 : 2)];
    TerrainID corner_v =  corners[ (left ? 0 : 1) + (!top ? 0 : 2)];

    Reseedable& stochastic_mask = mNoiseModuleManager.getStochastic(corner_id);
    Reseedable border_h = mNoiseModuleManager.getBorderHorizontal(left ? corner_id : corner_h,
                                                                  left ? corner_h : corner_id,
                                                                  top);
    Reseedable border_v = mNoiseModuleManager.getBorderVertical(top ? corner_id : corner_v,
                                                                top ? corner_v : corner_id,
                                                                left);
    Reseedable cc = noise::module::makeCornerCombiner(left,top);
    Reseedable border_xy = cc.blend(border_v, border_h);
    Reseedable deterministic = noise::module::makeLinearMovingScaleBias(border_xy, left, top, 0.85, 0.15);
    Reseedable ef = noise::module::makeEdgeFavouringMask(1.5, 1.);
    Reseedable corner = ef.blend(stochastic_mask, deterministic);
    // postprocess should be customisable
    Reseedable postprocess = corner.pow(5.).clamp(0.,std::numeric_limits<double>::infinity());
    return postprocess;
}

void TilePartitionerPerlin::noiseToAlpha(std::vector<noise::RasterValues<double>>& noise_values,
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

void TilePartitionerPerlin::makePartition(TilePartition & regions, const Corners& corners)
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
    std::vector<Reseedable> corner_modules(4);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
        {
            int k = (2 * i) + j;
            corner_modules[k] = makeCornerModule(corners, i == 0, j == 0);
            noise_values[k].build(*corner_modules[k].module);
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

TilePartitionerPerlin::TilePartitionerPerlin(const Options & options) :
    TilePartitionerBase(options),
    mNoiseModuleManager(options)
{
}

} // namespace partition
} // namespace tilegen
