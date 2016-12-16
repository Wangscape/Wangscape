#include "ModuleFactories.h"
#include "Gradient.h"
#include "NormLPQ.h"
#include "MakeReseedable.h"

using noise::module::Abs;
using noise::module::ScaleBias;
using noise::module::Clamp;
using noise::module::TranslatePoint;
using noise::module::ScalePoint;
using noise::module::Perlin;

Reseedable makePeak(bool x)
{
    Reseedable gradient;
    if (x)
        gradient = makeReseedable(std::make_shared<GradientX>());
    else
        gradient = makeReseedable(std::make_shared<GradientY>());
    return gradient.abs().scaleBias(-1, 1);
}

Reseedable makeCornerCombiner(bool x_positive, bool y_positive, double power)
{
    Reseedable corner_combiner_base = makeReseedable(std::make_shared<CornerCombinerBase>(power));
    return corner_combiner_base.clamp(-1, 1);
}

Reseedable makeEdgeFavouringMask(double p, double q, double min)
{
    Reseedable norm_lp_q = makeReseedable(std::make_shared<NormLPQ>(p, q));

    return norm_lp_q
        .translatePoint(-1., -1., 0.)
        .scalePoint(2., 2., 0.)
        .scaleBias(2., -1)
        .clamp(-1., 1.);
}

Reseedable makePlaceholder(int seed,
                           int octaves,
                           double frequency,
                           double lacunarity,
                           double persistence,
                           noise::NoiseQuality quality)
{
    std::shared_ptr<Perlin> placeholder = std::make_shared<Perlin>();
    placeholder->SetSeed(seed);
    placeholder->SetOctaveCount(octaves);
    placeholder->SetFrequency(frequency);
    placeholder->SetLacunarity(lacunarity);
    placeholder->SetPersistence(persistence);
    placeholder->SetNoiseQuality(quality);
    return makeReseedable(placeholder);
}
