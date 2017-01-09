#include "ModuleFactories.h"
#include "Gradient.h"
#include "NormLPQ.h"
#include "noise/MakeReseedable.h"
#include <stdexcept>

namespace noise
{
namespace module
{

Reseedable makeQuadrantSelector(Reseedable& source, bool x_positive, bool y_positive)
{
    if (x_positive && y_positive)
        return source;
    return source.translatePoint(x_positive ? 0 : -1,
                                 y_positive ? 0 : -1,
                                 0);
}

Reseedable makeCornerCombiner(bool x_positive, bool y_positive, double power)
{
    Reseedable corner_combiner_base = makeReseedable(std::make_shared<CornerCombinerBase>(power));
    Reseedable ccb_clamped = corner_combiner_base.clamp(-1, 1);
    return corner_combiner_base
        .clamp(-1., 1.)
        .translatePoint(x_positive ? 0. : -1.,
                        y_positive ? 0. : -1.,
                        0.0001); // Not a QuadrantSelector because of the z offset
}

Reseedable makeEdgeFavouringMask(double p, double q, double min)
{
    Reseedable norm_lp_q = makeReseedable(std::make_shared<NormLPQ>(p, q));

    return norm_lp_q
        .translatePoint(-1., -1., 0.) // Has the form of a QuadrantSelector but is semantically different
        .scalePoint(2., 2., 0.)
        .scaleBias(1.-min, min)
        .clamp(min, 1.);
}

Reseedable makeMovingScaleBias(Reseedable source, Reseedable min, Reseedable max)
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

Reseedable makeLinearMovingScaleBias(Reseedable source,
                                     bool x_positive, bool y_positive,
                                     double length, double middle_length)
{
    if (length <= middle_length)
        throw std::domain_error("LinearMovingScaleBias must have length greater than middle_length");
    Reseedable xa = makeX().abs();
    Reseedable ya = makeY().abs();
    double slope_length = (length - middle_length) / 2.;
    double slope = 1. / slope_length;
    double intercept = length*slope;
    Reseedable peak = (xa + ya)*(-slope);
    Reseedable peak_translated = makeQuadrantSelector(peak, x_positive, y_positive);
    Reseedable min = (peak_translated + 1).clamp(0, 1);
    Reseedable max = (peak_translated + intercept).clamp(0, 1);
    return makeMovingScaleBias(source, min, max);
}

Reseedable makePlaceholder(int seed)
{
    std::shared_ptr<Perlin> placeholder = std::make_shared<Perlin>();
    placeholder->SetSeed(seed);
    placeholder->SetOctaveCount(5);
    placeholder->SetFrequency(1.);
    placeholder->SetLacunarity(2.);
    placeholder->SetPersistence(0.5);
    placeholder->SetNoiseQuality(NoiseQuality::QUALITY_FAST);
    return makeReseedable(placeholder).translatePoint(1.1, 2.2, 3.3);
}

Reseedable makeModuleGroup(ModuleGroup::ModuleList modules)
{
    auto result = std::make_shared<module::ModuleGroup>(modules);
    return makeReseedable(result);
}

} // namespace module
} // namespace noise
