#include "Reseedable.h"
#include "MakeReseedable.h"
#include "module/ModuleGroup.h"
#include "module/ModuleFactories.h"
#include "module/Exp.h"
#include "module/Pow.h"

namespace noise {

double Reseedable::getValue(double x, double y, double z)
{
    return module->GetValue(x, y, z);
}

Reseedable Reseedable::abs()
{
    auto abs_p = std::make_shared<module::Abs>();
    abs_p->SetSourceModule(0, *module);

    return module::makeModuleGroup({
        {"source", *this},
        {"output", makeReseedable(abs_p)}
    });
}

Reseedable Reseedable::clamp(double lower, double upper)
{
    auto clamp_p = std::make_shared<module::Clamp>();
    clamp_p->SetSourceModule(0, *module);
    clamp_p->SetBounds(lower, upper);

    return module::makeModuleGroup({
        {"source", *this},
        {"output", makeReseedable(clamp_p)}
    });
}

Reseedable Reseedable::exp(double base)
{
    auto exponent_p = std::make_shared<module::Exp>();
    exponent_p->SetSourceModule(0, *module);
    exponent_p->SetBase(base);

    return module::makeModuleGroup({
        {"source", *this},
        {"output", makeReseedable(exponent_p)}
    });
}

Reseedable Reseedable::invert()
{
    auto invert_p = std::make_shared<module::Invert>();
    invert_p->SetSourceModule(0, *module);

    return module::makeModuleGroup({
        {"source", *this},
        {"output", makeReseedable(invert_p)}
    });
}

Reseedable Reseedable::scaleBias(double scale, double bias)
{
    auto scale_bias_p = std::make_shared<module::ScaleBias>();
    scale_bias_p->SetSourceModule(0, *module);
    scale_bias_p->SetScale(scale);
    scale_bias_p->SetBias(bias);

    return module::makeModuleGroup({
        {"source", *this},
        {"output", makeReseedable(scale_bias_p)}
    });
}

Reseedable Reseedable::operator+(Reseedable & other)
{
    auto add_p = std::make_shared<module::Add>();
    add_p->SetSourceModule(0, *module);
    add_p->SetSourceModule(1, *other.module);

    return module::makeModuleGroup({
        {"source0", *this},
        {"source1", other},
        {"output", makeReseedable(add_p)}
    });
}

Reseedable Reseedable::operator+(double bias)
{
    auto scale_bias_p = std::make_shared<module::ScaleBias>();
    scale_bias_p->SetSourceModule(0, *module);
    scale_bias_p->SetScale(1.);
    scale_bias_p->SetBias(bias);

    return module::makeModuleGroup({
        {"source", *this},
        {"output", makeReseedable(scale_bias_p)}
    });
}

Reseedable Reseedable::operator-(Reseedable & other)
{
    return operator+(other.invert());
}

Reseedable Reseedable::operator-(double bias)
{
    return operator+(-bias);
}

Reseedable Reseedable::operator-()
{
    return invert();
}

Reseedable Reseedable::max(Reseedable & other)
{
    auto max_p = std::make_shared<module::Max>();
    max_p->SetSourceModule(0, *module);
    max_p->SetSourceModule(1, *other.module);

    return module::makeModuleGroup({
        {"source0", *this},
        {"source1", other},
        {"output", makeReseedable(max_p)}
    });
}

Reseedable Reseedable::max(double other)
{
    auto c = std::make_shared<module::Const>();
    c->SetConstValue(other);
    return max(makeReseedable(c));
}


Reseedable Reseedable::min(Reseedable & other)
{
    auto min_p = std::make_shared<module::Min>();
    min_p->SetSourceModule(0, *module);
    min_p->SetSourceModule(1, *other.module);

    return module::makeModuleGroup({
        {"source0", *this},
        {"source1", other},
        {"output", makeReseedable(min_p)}
    });
}

Reseedable Reseedable::min(double other)
{
    auto c = std::make_shared<module::Const>();
    c->SetConstValue(other);
    return min(makeReseedable(c));
}

Reseedable Reseedable::operator*(Reseedable & other)
{
    auto multiply_p = std::make_shared<module::Multiply>();
    multiply_p->SetSourceModule(0, *module);
    multiply_p->SetSourceModule(1, *other.module);

    return module::makeModuleGroup({
        {"source0", *this},
        {"source1", other},
        {"output", makeReseedable(multiply_p)}
    });
}

Reseedable Reseedable::operator*(double scale)
{
    auto scale_bias_p = std::make_shared<module::ScaleBias>();
    scale_bias_p->SetSourceModule(0, *module);
    scale_bias_p->SetScale(scale);

    return module::makeModuleGroup({
        {"source", *this},
        {"output", makeReseedable(scale_bias_p)}
    });
}

Reseedable Reseedable::pow(Reseedable & exponent)
{
    auto pow_p = std::make_shared<module::Power>();
    pow_p->SetSourceModule(0, *module);
    pow_p->SetSourceModule(1, *exponent.module);

    return module::makeModuleGroup({
        {"source", *this},
        {"output", makeReseedable(pow_p)}
    });
}

Reseedable Reseedable::pow(double exponent)
{
    auto exponent_p = std::make_shared<module::Pow>();
    exponent_p->SetSourceModule(0, *module);
    exponent_p->SetExponent(exponent);

    return module::makeModuleGroup({
        {"source", *this},
        {"output", makeReseedable(exponent_p)}
    });
}

Reseedable Reseedable::blend(Reseedable& source_a, Reseedable& source_b)
{
    auto blend_p = std::make_shared<noise::module::Blend>();
    blend_p->SetSourceModule(0, *source_a.module);
    blend_p->SetSourceModule(1, *source_b.module);
    blend_p->SetControlModule(*module);

    return module::makeModuleGroup({
        {"control", *this},
        {"source0", source_a},
        {"source1", source_b},
        {"output", makeReseedable(blend_p)}
    });
}

Reseedable Reseedable::select(Reseedable& source_a, Reseedable& source_b)
{
    auto select_p = std::make_shared<module::Select>();
    select_p->SetSourceModule(0, *source_a.module);
    select_p->SetSourceModule(1, *source_b.module);
    select_p->SetControlModule(*module);

    return module::makeModuleGroup({
        {"control", *this},
        {"source0", source_a},
        {"source1", source_b},
        {"output", makeReseedable(select_p)}
    });
}

Reseedable Reseedable::rotatePoint(double x_angle, double y_angle, double z_angle)
{
    auto rotate_point_p = std::make_shared<module::RotatePoint>();
    rotate_point_p->SetSourceModule(0, *module);
    rotate_point_p->SetAngles(x_angle, y_angle, z_angle);

    return module::makeModuleGroup({
        {"source", *this},
        {"output", makeReseedable(rotate_point_p)}
    });
}

Reseedable Reseedable::scalePoint(double x_scale, double y_scale, double z_scale)
{
    auto scale_point_p = std::make_shared<module::ScalePoint>();
    scale_point_p->SetSourceModule(0, *module);
    scale_point_p->SetXScale(x_scale);
    scale_point_p->SetYScale(y_scale);
    scale_point_p->SetZScale(z_scale);

    return module::makeModuleGroup({
        {"source", *this},
        {"output", makeReseedable(scale_point_p)}
    });
}

Reseedable Reseedable::translatePoint(double x_displace, double y_displace, double z_displace)
{
    auto translate_point_p = std::make_shared<module::TranslatePoint>();
    translate_point_p->SetSourceModule(0, *module);
    translate_point_p->SetXTranslation(x_displace);
    translate_point_p->SetYTranslation(y_displace);
    translate_point_p->SetZTranslation(z_displace);

    return module::makeModuleGroup({
        {"source", *this},
        {"output", makeReseedable(translate_point_p)}
    });
}

Reseedable Reseedable::turbulence(double frequency, double power, int roughness, int seed)
{
    auto turbulence_p = std::make_shared<module::Turbulence>();
    turbulence_p->SetFrequency(frequency);
    turbulence_p->SetPower(power);
    turbulence_p->SetRoughness(roughness);
    turbulence_p->SetSeed(seed);
    turbulence_p->SetSourceModule(0, *module);
    return module::makeModuleGroup({
        {"source", *this},
        {"output", makeReseedable(turbulence_p)}
    });
}

Reseedable Reseedable::terrace(int controlPointCount, bool inverted)
{
    auto terrace_p = std::make_shared<module::Terrace>();
    terrace_p->InvertTerraces(inverted);
    terrace_p->MakeControlPoints(controlPointCount);
    terrace_p->SetSourceModule(0, *module);
    return finaliseTerrace(terrace_p);
}

Reseedable Reseedable::finaliseTerrace(std::shared_ptr<module::Terrace> terrace_p)
{
    return module::makeModuleGroup({
        {"source", *this},
        {"output", makeReseedable(terrace_p)}
    });
}

Reseedable Reseedable::finaliseCurve(std::shared_ptr<module::Curve> curve_p)
{
    return module::makeModuleGroup({
        {"source", *this},
        {"output", makeReseedable(curve_p)}
    });
}

Reseedable Reseedable::displace(Reseedable & x_displace, Reseedable & y_displace, Reseedable & z_displace)
{
    auto displace_p = std::make_shared<module::Displace>();
    displace_p->SetSourceModule(0, *module);
    displace_p->SetXDisplaceModule(*x_displace.module);
    displace_p->SetYDisplaceModule(*y_displace.module);
    displace_p->SetZDisplaceModule(*z_displace.module);

    return module::makeModuleGroup({
        {"source", *this},
        {"output", makeReseedable(displace_p)}
    });
}

} // namespace noise
