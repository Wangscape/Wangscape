#include "Reseedable.h"
#include "MakeReseedable.h"
#include "ModuleGroup.h"
#include "Exp.h"

double Reseedable::getValue(double x, double y, double z)
{
    return module->GetValue(x, y, z);
}

Reseedable Reseedable::abs()
{
    std::shared_ptr<noise::module::Abs> abs_p = std::make_shared<noise::module::Abs>();
    abs_p->SetSourceModule(0, *module);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("source", *this);
    mg->insert("output", makeReseedable(abs_p));
    return makeReseedable(mg);
}

Reseedable Reseedable::clamp(double lower, double upper)
{
    std::shared_ptr<noise::module::Clamp> clamp_p = std::make_shared<noise::module::Clamp>();
    clamp_p->SetSourceModule(0, *module);
    clamp_p->SetBounds(lower, upper);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("source", *this);
    mg->insert("output", makeReseedable(clamp_p));
    return makeReseedable(mg);
}

Reseedable Reseedable::exp(double base)
{
    std::shared_ptr<Exp> exponent_p = std::make_shared<Exp>();
    exponent_p->SetSourceModule(0, *module);
    exponent_p->SetBase(base);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("source", *this);
    mg->insert("output", makeReseedable(exponent_p));
    return makeReseedable(mg);
}

Reseedable Reseedable::invert()
{
    std::shared_ptr<noise::module::Invert> invert_p = std::make_shared<noise::module::Invert>();
    invert_p->SetSourceModule(0, *module);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("source", *this);
    mg->insert("output", makeReseedable(invert_p));
    return makeReseedable(mg);
}

Reseedable Reseedable::scaleBias(double scale, double bias)
{
    std::shared_ptr<noise::module::ScaleBias> scale_bias_p = std::make_shared<noise::module::ScaleBias>();
    scale_bias_p->SetSourceModule(0, *module);
    scale_bias_p->SetScale(scale);
    scale_bias_p->SetBias(bias);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("source", *this);
    mg->insert("output", makeReseedable(scale_bias_p));
    return makeReseedable(mg);
}

Reseedable Reseedable::operator+(Reseedable & other)
{
    std::shared_ptr<noise::module::Add> add_p = std::make_shared<noise::module::Add>();
    add_p->SetSourceModule(0, *module);
    add_p->SetSourceModule(1, *other.module);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("source0", *this);
    mg->insert("source1", other);
    mg->insert("output", makeReseedable(add_p));
    return makeReseedable(mg);
}

Reseedable Reseedable::operator+(double bias)
{
    std::shared_ptr<noise::module::ScaleBias> scale_bias_p = std::make_shared<noise::module::ScaleBias>();
    scale_bias_p->SetSourceModule(0, *module);
    scale_bias_p->SetScale(1.);
    scale_bias_p->SetBias(bias);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("source", *this);
    mg->insert("output", makeReseedable(scale_bias_p));
    return makeReseedable(mg);
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
    std::shared_ptr<noise::module::Max> max_p = std::make_shared<noise::module::Max>();
    max_p->SetSourceModule(0, *module);
    max_p->SetSourceModule(1, *other.module);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("source0", *this);
    mg->insert("source1", other);
    mg->insert("output", makeReseedable(max_p));
    return makeReseedable(mg);
}

Reseedable Reseedable::max(double other)
{
    auto c = std::make_shared<noise::module::Const>();
    c->SetConstValue(other);
    return max(makeReseedable(c));
}


Reseedable Reseedable::min(Reseedable & other)
{
    std::shared_ptr<noise::module::Min> min_p = std::make_shared<noise::module::Min>();
    min_p->SetSourceModule(0, *module);
    min_p->SetSourceModule(1, *other.module);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("source0", *this);
    mg->insert("source1", other);
    mg->insert("output", makeReseedable(min_p));
    return makeReseedable(mg);
}

Reseedable Reseedable::min(double other)
{
    auto c = std::make_shared<noise::module::Const>();
    c->SetConstValue(other);
    return min(makeReseedable(c));
}

Reseedable Reseedable::operator*(Reseedable & other)
{
    std::shared_ptr<noise::module::Multiply> multiply_p = std::make_shared<noise::module::Multiply>();
    multiply_p->SetSourceModule(0, *module);
    multiply_p->SetSourceModule(1, *other.module);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("source0", *this);
    mg->insert("source1", other);
    mg->insert("output", makeReseedable(multiply_p));
    return makeReseedable(mg);
}

Reseedable Reseedable::operator*(double scale)
{
    std::shared_ptr<noise::module::ScaleBias> scale_bias_p = std::make_shared<noise::module::ScaleBias>();
    scale_bias_p->SetSourceModule(0, *module);
    scale_bias_p->SetScale(scale);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("source", *this);
    mg->insert("output", makeReseedable(scale_bias_p));
    return makeReseedable(mg);
}

Reseedable Reseedable::pow(Reseedable & exponent)
{
    std::shared_ptr<noise::module::Power> power_p = std::make_shared<noise::module::Power>();
    power_p->SetSourceModule(0, *module);
    power_p->SetSourceModule(1, *exponent.module);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("base", *this);
    mg->insert("exponent", exponent);
    mg->insert("output", makeReseedable(power_p));
    return makeReseedable(mg);
}

Reseedable Reseedable::pow(double exponent)
{
    std::shared_ptr<Power> exponent_p = std::make_shared<Power>();
    exponent_p->SetSourceModule(0, *module);
    exponent_p->SetExponent(exponent);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("source", *this);
    mg->insert("output", makeReseedable(exponent_p));
    return makeReseedable(mg);
}

Reseedable Reseedable::blend(Reseedable& source_a, Reseedable& source_b)
{
    std::shared_ptr<noise::module::Blend> blend_p = std::make_shared<noise::module::Blend>();
    blend_p->SetSourceModule(0, *source_a.module);
    blend_p->SetSourceModule(1, *source_b.module);
    blend_p->SetControlModule(*module);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("control", *this);
    mg->insert("source0", source_a);
    mg->insert("source1", source_b);
    mg->insert("output", makeReseedable(blend_p));
    return makeReseedable(mg);
}

Reseedable Reseedable::select(Reseedable& source_a, Reseedable& source_b)
{
    std::shared_ptr<noise::module::Select> select_p = std::make_shared<noise::module::Select>();
    select_p->SetSourceModule(0, *source_a.module);
    select_p->SetSourceModule(1, *source_b.module);
    select_p->SetControlModule(*module);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("control", *this);
    mg->insert("source0", source_a);
    mg->insert("source1", source_b);
    mg->insert("output", makeReseedable(select_p));
    return makeReseedable(mg);
}

Reseedable Reseedable::rotatePoint(double x_angle, double y_angle, double z_angle)
{
    std::shared_ptr<noise::module::RotatePoint> rotate_point_p = std::make_shared<noise::module::RotatePoint>();
    rotate_point_p->SetSourceModule(0, *module);
    rotate_point_p->SetXAngle(x_angle);
    rotate_point_p->SetYAngle(y_angle);
    rotate_point_p->SetZAngle(z_angle);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("source", *this);
    mg->insert("output", makeReseedable(rotate_point_p));
    return makeReseedable(mg);
}

Reseedable Reseedable::scalePoint(double x_scale, double y_scale, double z_scale)
{
    std::shared_ptr<noise::module::ScalePoint> scale_point_p = std::make_shared<noise::module::ScalePoint>();
    scale_point_p->SetSourceModule(0, *module);
    scale_point_p->SetXScale(x_scale);
    scale_point_p->SetYScale(y_scale);
    scale_point_p->SetZScale(z_scale);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("source", *this);
    mg->insert("output", makeReseedable(scale_point_p));
    return makeReseedable(mg);
}

Reseedable Reseedable::translatePoint(double x_displace, double y_displace, double z_displace)
{
    std::shared_ptr<noise::module::TranslatePoint> translate_point_p = std::make_shared<noise::module::TranslatePoint>();
    translate_point_p->SetSourceModule(0, *module);
    translate_point_p->SetXTranslation(x_displace);
    translate_point_p->SetYTranslation(y_displace);
    translate_point_p->SetZTranslation(z_displace);

    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("source", *this);
    mg->insert("output", makeReseedable(translate_point_p));
    return makeReseedable(mg);
}

Reseedable Reseedable::turbulence(double frequency, double power, int roughness, int seed)
{
    auto turbulence_p = std::make_shared<noise::module::Turbulence>();
    turbulence_p->SetFrequency(frequency);
    turbulence_p->SetPower(power);
    turbulence_p->SetRoughness(roughness);
    turbulence_p->SetSeed(seed);
    std::shared_ptr<ModuleGroup> mg = std::make_shared<ModuleGroup>();
    mg->insert("source", *this);
    mg->insert("output", makeReseedable(turbulence_p));
    return makeReseedable(mg);
}


Reseedable Reseedable::displace(Reseedable & x_displace, Reseedable & y_displace, Reseedable & z_displace)
{
    throw;
    return Reseedable();
}
