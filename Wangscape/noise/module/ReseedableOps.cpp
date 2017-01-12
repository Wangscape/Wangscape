#include "ReseedableOps.h"
#include "Exp.h"
#include "Pow.h"
#include "Gradient.h"
#include "NormLPQ.h"
#include "CornerCombinerBase.h"

namespace noise
{
namespace module
{

ReseedablePtr operator+(ReseedablePtr left, ReseedablePtr right)
{
    auto add_p = std::make_shared<Reseedable<Add>>();
    add_p->getModule().SetSourceModule(0, left->getModule());
    add_p->getModule().SetSourceModule(1, right->getModule());

    return makeModuleGroup({
        {"source0", left},
        {"source1", right},
        {"output", add_p}
    });
}

ReseedablePtr operator+(ReseedablePtr left, double right)
{
    auto scale_bias_p = std::make_shared<Reseedable<ScaleBias>>();
    scale_bias_p->module.SetSourceModule(0, left->getModule());
    scale_bias_p->module.SetScale(1.);
    scale_bias_p->module.SetBias(right);

    return makeModuleGroup({
        {"source", left},
        {"output", scale_bias_p}
    });
}

ReseedablePtr operator+(double left, ReseedablePtr right)
{
    return right + left;
}

ReseedablePtr& operator+=(ReseedablePtr& left, ReseedablePtr right)
{
    return (left = left + right);
}

ReseedablePtr& operator+=(ReseedablePtr& left, double right)
{
    return (left = left + right);
}

ReseedablePtr operator-(ReseedablePtr left, ReseedablePtr right)
{
    return left + -right;
}

ReseedablePtr operator-(ReseedablePtr left, double right)
{
    return left + -right;
}

ReseedablePtr operator-(ReseedablePtr source)
{
    return invert(source);
}

ReseedablePtr invert(ReseedablePtr source)
{
    auto invert_p = std::make_shared<Reseedable<Invert>>();
    invert_p->module.SetSourceModule(0, source->getModule());

    return makeModuleGroup({
        {"source", source},
        {"output", invert_p}
    });
}

ReseedablePtr& operator-=(ReseedablePtr& left, ReseedablePtr right)
{
    return (left = left + -right);
}

ReseedablePtr& operator-=(ReseedablePtr& left, double right)
{
    return (left = left + -right);
}

ReseedablePtr operator*(ReseedablePtr left, ReseedablePtr right)
{
    auto multiply_p = std::make_shared<Reseedable<Multiply>>();
    multiply_p->module.SetSourceModule(0, left->getModule());
    multiply_p->module.SetSourceModule(1, right->getModule());

    return makeModuleGroup({
        {"source0", left},
        {"source1", right},
        {"output", multiply_p}
    });
}

ReseedablePtr operator*(ReseedablePtr left, double right)
{
    auto scale_bias_p = std::make_shared<Reseedable<ScaleBias>>();
    scale_bias_p->module.SetSourceModule(0, left->getModule());
    scale_bias_p->module.SetScale(right);

    return makeModuleGroup({
        {"source", left},
        {"output", scale_bias_p}
    });
}

ReseedablePtr operator*(double left, ReseedablePtr right)
{
    return right * left;
}

ReseedablePtr& operator*=(ReseedablePtr& left, ReseedablePtr right)
{
    return (left = left * right);
}

ReseedablePtr& operator*=(ReseedablePtr& left, double right)
{
    return (left = left * right);
}

ReseedablePtr operator/(ReseedablePtr left, ReseedablePtr right)
{
    auto multiply_p = std::make_shared<Reseedable<Multiply>>();
    multiply_p->module.SetSourceModule(0, left->getModule());
    multiply_p->module.SetSourceModule(1, right->getModule());

    return makeModuleGroup({
        {"source0", left},
        {"source1", right},
        {"output", multiply_p}
    });
}

ReseedablePtr operator/(ReseedablePtr left, double right)
{
    throw std::runtime_error("Not implemented");
}

ReseedablePtr operator/(double left, ReseedablePtr right)
{
    throw std::runtime_error("Not implemented");
}

ReseedablePtr& operator/=(ReseedablePtr& left, ReseedablePtr right)
{
    throw std::runtime_error("Not implemented");
}

ReseedablePtr& operator/=(ReseedablePtr& left, double right)
{
    throw std::runtime_error("Not implemented");
}

ReseedablePtr pow(ReseedablePtr base, ReseedablePtr exponent)
{
    auto power_p = std::make_shared<Reseedable<Power>>();
    power_p->module.SetSourceModule(0, base->getModule());
    power_p->module.SetSourceModule(1, exponent->getModule());

    return makeModuleGroup({
        {"base", base},
        {"exponent", exponent},
        {"output", power_p}
    });
}

ReseedablePtr pow(ReseedablePtr base, double exponent)
{
    auto pow_p = std::make_shared<Reseedable<Pow>>();
    pow_p->module.SetSourceModule(0, base->getModule());
    pow_p->module.SetExponent(exponent);

    return makeModuleGroup({
        {"source", base},
        {"output", pow_p}
    });
}

ReseedablePtr pow(double base, ReseedablePtr exponent)
{
    auto exp_p = std::make_shared<Reseedable<Exp>>();
    exp_p->module.SetSourceModule(0, exponent->getModule());
    exp_p->module.SetBase(base);

    return makeModuleGroup({
        {"source", exponent},
        {"output", exp_p}
    });
}

ReseedablePtr blend(ReseedablePtr control, ReseedablePtr source_a, ReseedablePtr source_b)
{
    auto blend_p = std::make_shared<Reseedable<Blend>>();
    blend_p->module.SetSourceModule(0, source_a->getModule());
    blend_p->module.SetSourceModule(1, source_b->getModule());
    blend_p->module.SetControlModule(control->getModule());

    return makeModuleGroup({
        {"source0", source_a},
        {"source1", source_b},
        {"output", blend_p}
    });
}

ReseedablePtr select(ReseedablePtr control, ReseedablePtr source_a, ReseedablePtr source_b)
{
    auto select_p = std::make_shared<Reseedable<Select>>();
    select_p->module.SetSourceModule(0, source_a->getModule());
    select_p->module.SetSourceModule(1, source_b->getModule());
    select_p->module.SetControlModule(control->getModule());

    return makeModuleGroup({
        {"source0", source_a},
        {"source1", source_b},
        {"output", select_p}
    });
}

ReseedablePtr translate(ReseedablePtr source, ReseedablePtr x_displace, ReseedablePtr y_displace, ReseedablePtr z_displace)
{
    auto displace_p = std::make_shared<Reseedable<Displace>>();
    displace_p->module.SetSourceModule(0, source->getModule());
    displace_p->module.SetXDisplaceModule(x_displace->getModule());
    displace_p->module.SetYDisplaceModule(y_displace->getModule());
    displace_p->module.SetZDisplaceModule(z_displace->getModule());

    return makeModuleGroup({
        {"source", source},
        {"displaceX", x_displace},
        {"displaceY", y_displace},
        {"displaceZ", z_displace},
        {"output", displace_p}
    });
}

ReseedablePtr translate(ReseedablePtr source, double x_displace, double y_displace, double z_displace)
{
    auto translate_point_p = std::make_shared<Reseedable<TranslatePoint>>();
    translate_point_p->module.SetSourceModule(0, source->getModule());
    translate_point_p->module.SetXTranslation(x_displace);
    translate_point_p->module.SetYTranslation(y_displace);
    translate_point_p->module.SetZTranslation(z_displace);

    return makeModuleGroup({
        {"source", source},
        {"output", translate_point_p}
    });
}

ReseedablePtr scalePoint(ReseedablePtr source, double x_scale, double y_scale, double z_scale)
{
    auto scale_point_p = std::make_shared<Reseedable<ScalePoint>>();
    scale_point_p->module.SetSourceModule(0, source->getModule());
    scale_point_p->module.SetXScale(x_scale);
    scale_point_p->module.SetYScale(y_scale);
    scale_point_p->module.SetZScale(z_scale);

    return makeModuleGroup({
        {"source", source},
        {"output", scale_point_p}
    });
}

ReseedablePtr rotatePoint(ReseedablePtr source, double x_angle, double y_angle, double z_angle)
{
    auto rotate_point_p = std::make_shared<Reseedable<RotatePoint>>();
    rotate_point_p->module.SetSourceModule(0, source->getModule());
    rotate_point_p->module.SetAngles(x_angle, y_angle, z_angle);

    return makeModuleGroup({
        {"source", source},
        {"output", rotate_point_p}
    });
}

ReseedablePtr turbulence(ReseedablePtr source, double frequency, double power, int roughness, int seed)
{
    auto turbulence_p = std::make_shared<Reseedable<Turbulence>>();
    turbulence_p->module.SetFrequency(frequency);
    turbulence_p->module.SetPower(power);
    turbulence_p->module.SetRoughness(roughness);
    turbulence_p->module.SetSeed(seed);
    turbulence_p->module.SetSourceModule(0, source->getModule());

    return makeModuleGroup({
        {"source", source},
        {"output", turbulence_p}
    });
}

ReseedablePtr abs(ReseedablePtr source)
{
    auto abs_p = std::make_shared<Reseedable<Abs>>();
    abs_p->module.SetSourceModule(0, source->getModule());

    return makeModuleGroup({
        {"source", source},
        {"output", abs_p}
    });
}

ReseedablePtr max(ReseedablePtr a, ReseedablePtr b)
{
    auto max_p = std::make_shared<Reseedable<Max>>();
    max_p->module.SetSourceModule(0, a->getModule());
    max_p->module.SetSourceModule(1, b->getModule());

    return makeModuleGroup({
        {"source0", a},
        {"source1", b},
        {"output", max_p}
    });
}

ReseedablePtr max(ReseedablePtr a, double b)
{
    ReseedablePtr c = makeConst(b);
    return max(a, c);
}

ReseedablePtr max(double a, ReseedablePtr b)
{
    return max(b, a);
}

ReseedablePtr min(ReseedablePtr a, ReseedablePtr b)
{
    auto min_p = std::make_shared<Reseedable<Min>>();
    min_p->module.SetSourceModule(0, a->getModule());
    min_p->module.SetSourceModule(1, b->getModule());

    return makeModuleGroup({
        {"source0", a},
        {"source1", b},
        {"output", min_p}
    });
}

ReseedablePtr min(ReseedablePtr a, double b)
{
    ReseedablePtr c = makeConst(b);
    return min(a, c);
}

ReseedablePtr min(double a, ReseedablePtr b)
{
    return min(b, a);
}

ReseedablePtr clamp(ReseedablePtr source, double lower, double upper)
{
    assert(lower <= upper);
    // noise::module::Clamp cannot be used here because it asserts
    // lower < upper
    return max(lower, min(upper, source));
}

ReseedablePtr scaleBias(ReseedablePtr source, double scale, double bias)
{
    auto scale_bias_p = std::make_shared<Reseedable<ScaleBias>>();
    scale_bias_p->module.SetSourceModule(0, source->getModule());
    scale_bias_p->module.SetScale(scale);
    scale_bias_p->module.SetBias(bias);

    return makeModuleGroup({
        {"source", source},
        {"output", scale_bias_p}
    });
}

ReseedablePtr terrace(ReseedablePtr source, int controlPointCount, bool inverted)
{
    auto terrace_p = std::make_shared<Reseedable<Terrace>>();
    terrace_p->module.InvertTerraces(inverted);
    terrace_p->module.MakeControlPoints(controlPointCount);
    terrace_p->module.SetSourceModule(0, source->getModule());
    return makeModuleGroup({
        {"source", source},
        {"output", terrace_p}
    });
}

ReseedablePtr makeModuleGroup(std::initializer_list<std::pair<ModuleGroup::ModuleID, ReseedablePtr>> modules)
{
    auto module_group = std::make_shared<Reseedable<ModuleGroup>>();
    for (auto name_module : modules)
    {
        module_group->module.insert(name_module.first, name_module.second);
    }
    return module_group;
}

ReseedablePtr makeQuadrantSelector(ReseedablePtr source, bool x_positive, bool y_positive)
{
    if (x_positive && y_positive)
        return source;
    return translate(source, 
                    x_positive ? 0. : -1.,
                    y_positive ? 0. : -1.,
                    0.);
}

ReseedablePtr makeCornerCombiner(bool x_positive, bool y_positive, double power)
{
    auto corner_combiner_base = std::make_shared<Reseedable<CornerCombinerBase>>();
    corner_combiner_base->module.power = power;
    ReseedablePtr result = clamp(corner_combiner_base, -1, 1);
    result = translate(result,
                       x_positive ? 0. : -1.,
                       y_positive ? 0. : -1.,
                       0.0001); // Not a QuadrantSelector because of the z offset
    return result;
}

ReseedablePtr makeEdgeFavouringMask(double p, double q, double min)
{
    auto norm_lp_q = std::make_shared<Reseedable<NormLPQ>>();
    norm_lp_q->module.setPQ(p, q);
    ReseedablePtr result = translate(norm_lp_q, -1., -1., 0.);
    result = scalePoint(result, 2., 2., 0.);
    result = scaleBias(result, 1. - min, min);
    result = clamp(result, min, 1.);
    return result;
}

ReseedablePtr makeMovingScaleBias(ReseedablePtr source, ReseedablePtr min, ReseedablePtr max)
{
    return ((source + 1)*0.5*(max - min)) + min;
}

ReseedablePtr makeX()
{
    return std::make_shared<Reseedable<GradientX>>();
}

ReseedablePtr makeY()
{
    return std::make_shared<Reseedable<GradientY>>();
}

ReseedablePtr makeZ()
{
    return std::make_shared<Reseedable<GradientZ>>();
}

ReseedablePtr makeConst(double c)
{
    auto c_p = std::make_shared<Reseedable<Const>>();
    c_p->module.SetConstValue(c);
    return c_p;
}

ReseedablePtr makeLinearMovingScaleBias(ReseedablePtr source,
                                        bool x_positive, bool y_positive,
                                        double length, double middle_length)
{
    if (length <= middle_length)
        throw std::domain_error("LinearMovingScaleBias must have length greater than middle_length");
    ReseedablePtr xa = abs(makeX());
    ReseedablePtr ya = abs(makeY());
    double slope_length = (length - middle_length) / 2.;
    double slope = 1. / slope_length;
    double intercept = length*slope;
    ReseedablePtr peak = (xa + ya)*(-slope);
    ReseedablePtr peak_translated = makeQuadrantSelector(peak, x_positive, y_positive);
    ReseedablePtr min = clamp(peak_translated + 1, 0, 1);
    ReseedablePtr max = clamp(peak_translated + intercept, 0, 1);
    return makeMovingScaleBias(source, min, max);
}

ReseedablePtr makePlaceholder(int seed)
{
    auto placeholder = std::make_shared<Reseedable<Perlin>>();
    placeholder->module.SetSeed(seed);
    placeholder->module.SetOctaveCount(5);
    placeholder->module.SetFrequency(1.);
    placeholder->module.SetLacunarity(2.);
    placeholder->module.SetPersistence(0.5);
    placeholder->module.SetNoiseQuality(NoiseQuality::QUALITY_FAST);
    return translate(placeholder, 1.1, 2.2, 3.3);
}


} // namespace module

} // namespace noise
