#include "TilePartitionerPerlin.h"
#include "noise/module/ModuleFactories.h"
#include "noise/RasterValues.h"
#include "AlphaCalculatorLinear.h"
#include "noise/module/Pow.h"

void TilePartitionerPerlin::makeCorner(noise::RasterValues<float>& noise_map_vector,
                                       const Corners& corners,
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
    Reseedable postprocess = corner.pow(5.).clamp(0.,std::numeric_limits<float>::infinity());
    noise_map_vector.build(*postprocess.module);
}

void TilePartitionerPerlin::makePartition(TilePartition & regions, const Corners& corners)
{
    std::vector<noise::RasterValues<float>> nmvs;
    // This whole function needs to depend on CORNERS,
    // not the magic number 4
    for (int i = 0; i < 4; i++)
    {
        nmvs.emplace_back(mOptions.resolution,
                          mOptions.resolution,
                          sf::Rect<double>{0, 0, 1, 1});
    }
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            makeCorner(nmvs[(2 * i) + j], corners, i == 0, j == 0);
    // post-processing steps
    std::vector<sf::Image> outputs(4);
    for (int i = 0; i < 4; i++)
        outputs[i].create(mOptions.resolution, mOptions.resolution);
    std::vector<float> weights(4);
    std::vector<sf::Uint8> alphas(4);
    AlphaCalculatorLinear ac;
    for (size_t x = 0; x < mOptions.resolution; x++)
    {
        for (size_t y = 0; y < mOptions.resolution; y++)
        {
            for (int i = 0; i < 4; i++)
            {
                weights[i] = nmvs[i].get(x, y);
            }

            ac.updateAlphas(weights);
            const auto& alphas = ac.getAlphas();
            for (int i = 0; i < 4; i++)
            {
                 outputs[i].setPixel(x, y, sf::Color(255, 255, 255, alphas[i]));
            }
        }
    }
    for (int i = 0; i < 4; i++)
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
