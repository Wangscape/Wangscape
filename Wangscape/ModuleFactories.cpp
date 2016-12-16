#include "ModuleFactories.h"
#include "Gradient.h"
#include "NormLPQ.h"
#include "MakeReseedable.h"
#include <stdexcept>

using noise::module::Abs;
using noise::module::ScaleBias;
using noise::module::Clamp;
using noise::module::TranslatePoint;
using noise::module::ScalePoint;
using noise::module::Perlin;

Reseedable makePeak(bool x)
{
    Reseedable gradient = x ? makeX() : makeY();
    return makeX().abs().scaleBias(-1, 1);
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
        .scaleBias(1.-min, min)
        .clamp(min, 1.);
}

Reseedable makeMovingScaleBias(Reseedable& source, Reseedable& min, Reseedable& max)
{
    return ((source + 1)*0.5*(max - min)) + min;
}

Reseedable makeX()
{
    return makeReseedable(std::make_shared<GradientX>());
}

Reseedable makeY()
{
    return makeReseedable(std::make_shared<GradientY>());
}

Reseedable makeZ()
{
    return makeReseedable(std::make_shared<GradientZ>());
}

Reseedable makeLinearMovingScaleBias(Reseedable & source,
                                     bool x, bool positive,
                                     double length, double middle_length)
{
    if (length <= middle_length)
        throw std::domain_error("LinearMovingScaleBias must have length greater than middle_length");
    Reseedable z = x ? makeX() : makeY();
    double slope_length = (length - middle_length) / 2.;
    double slope = 1. / slope_length;
    Reseedable min = (z.abs()*(-slope) + 1).clamp(0, 1);
    Reseedable max = (z.abs()*(-slope) + slope).clamp(0, 1);

    return makeMovingScaleBias(source, min, max);
}

Reseedable makePlaceholder(int seed,
                           int octaves,
                           double frequency,
                           double lacunarity,
                           double persistence,
                           noise::NoiseQuality quality,
                           double origin_x,
                           double origin_y,
                           double origin_z)
{
    std::shared_ptr<Perlin> placeholder = std::make_shared<Perlin>();
    placeholder->SetSeed(seed);
    placeholder->SetOctaveCount(octaves);
    placeholder->SetFrequency(frequency);
    placeholder->SetLacunarity(lacunarity);
    placeholder->SetPersistence(persistence);
    placeholder->SetNoiseQuality(quality);
    return makeReseedable(placeholder).translatePoint(origin_x,origin_y,origin_z);
}
