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

Reseedable makeQuadrantSelector(Reseedable& source, bool x, bool y)
{
    return source.translatePoint(x ? 0 : -1, y ? 0 : -1, 0);
}

Reseedable makeCornerCombiner(bool x_positive, bool y_positive, double power)
{
    Reseedable corner_combiner_base = makeReseedable(std::make_shared<CornerCombinerBase>(power));
    Reseedable ccb_clamped = corner_combiner_base.clamp(-1, 1);
    return corner_combiner_base
        .clamp(-1., 1.)
        .translatePoint(x_positive ? 0. : -1.,
                        y_positive ? 0. : -1.,
                        0.0001);
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

Reseedable makeConst(double c)
{
    auto c_p = std::make_shared<noise::module::Const>();
    c_p->SetConstValue(c);
    return makeReseedable(c_p);
}

Reseedable makeLinearMovingScaleBias(Reseedable & source,
                                     bool x_positive, bool y_positive,
                                     double length, double middle_length)
{
    if (length <= middle_length)
        throw std::domain_error("LinearMovingScaleBias must have length greater than middle_length");
    Reseedable x = x_positive ? makeX() : -makeX();
    Reseedable y = y_positive ? makeY() : -makeY();
    double slope_length = (length - middle_length) / 2.;
    double slope = 1. / slope_length;
    double intercept = length*slope;
    Reseedable peak = (x+y).abs()*(-slope);
    Reseedable min = (peak + 1).clamp(0, 1);
    Reseedable max = (peak + intercept).clamp(0, 1);

    return makeQuadrantSelector(makeMovingScaleBias(source, min, max),
                                x_positive,y_positive);
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
