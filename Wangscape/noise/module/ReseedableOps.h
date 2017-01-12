#pragma once
#include "ReseedablePtr.h"
#include "Reseedable.h"
#include "ModuleGroup.h"
#include <noise/noise.h>

namespace noise
{
namespace module
{

ReseedablePtr operator+(ReseedablePtr left, ReseedablePtr right);
ReseedablePtr operator+(ReseedablePtr left, double right);
ReseedablePtr operator+(double left, ReseedablePtr right);
ReseedablePtr& operator+=(ReseedablePtr& left, ReseedablePtr right);
ReseedablePtr& operator+=(ReseedablePtr& left, double right);

ReseedablePtr operator-(ReseedablePtr left, ReseedablePtr right);
ReseedablePtr operator-(ReseedablePtr left, double right);
ReseedablePtr operator-(ReseedablePtr source);
ReseedablePtr invert(ReseedablePtr source);
ReseedablePtr& operator-=(ReseedablePtr& left, ReseedablePtr right);
ReseedablePtr& operator-=(ReseedablePtr& left, double right);

ReseedablePtr operator*(ReseedablePtr left, ReseedablePtr right);
ReseedablePtr operator*(ReseedablePtr left, double right);
ReseedablePtr operator*(double left, ReseedablePtr right);
ReseedablePtr& operator*=(ReseedablePtr& left, ReseedablePtr right);
ReseedablePtr& operator*=(ReseedablePtr& left, double right);

ReseedablePtr operator/(ReseedablePtr left, ReseedablePtr right);
ReseedablePtr operator/(ReseedablePtr left, double right);
ReseedablePtr operator/(double left, ReseedablePtr right);
ReseedablePtr& operator/=(ReseedablePtr& left, ReseedablePtr right);
ReseedablePtr& operator/=(ReseedablePtr& left, double right);

ReseedablePtr pow(ReseedablePtr base, ReseedablePtr exponent);
ReseedablePtr pow(ReseedablePtr base, double exponent);
ReseedablePtr pow(double base, ReseedablePtr exponent);

ReseedablePtr blend(ReseedablePtr control, ReseedablePtr source_a, ReseedablePtr source_b);
ReseedablePtr select(ReseedablePtr control, ReseedablePtr source_a, ReseedablePtr source_b);

ReseedablePtr translate(ReseedablePtr source, ReseedablePtr x_displace, ReseedablePtr y_displace, ReseedablePtr z_displace);
ReseedablePtr translate(ReseedablePtr source, double x_displace, double y_displace, double z_displace);
ReseedablePtr scalePoint(ReseedablePtr source, double x_scale, double y_scale, double z_scale);
ReseedablePtr rotatePoint(ReseedablePtr source, double x_angle, double y_angle, double z_angle);
ReseedablePtr turbulence(ReseedablePtr source, double frequency, double power, int roughness, int seed);

ReseedablePtr abs(ReseedablePtr source);
ReseedablePtr max(ReseedablePtr a, ReseedablePtr b);
ReseedablePtr max(ReseedablePtr a, double b);
ReseedablePtr max(double a, ReseedablePtr b);
ReseedablePtr min(ReseedablePtr a, ReseedablePtr b);
ReseedablePtr min(ReseedablePtr a, double b);
ReseedablePtr min(double a, ReseedablePtr b);
ReseedablePtr clamp(ReseedablePtr source, double lower, double upper);
ReseedablePtr scaleBias(ReseedablePtr source, double scale, double bias);
ReseedablePtr terrace(ReseedablePtr source, int controlPointCount, bool inverted = false);

template<typename InputIt>
ReseedablePtr terrace(ReseedablePtr source, InputIt first, InputIt last, bool inverted = false);

template<typename InputIt>
ReseedablePtr curve(ReseedablePtr source, InputIt first, InputIt last);

// Makes a ModuleGroup with concise syntax.
ReseedablePtr makeModuleGroup(std::initializer_list<std::pair<ModuleGroup::ModuleID, ReseedablePtr>> modules);

// Makes a TranslatePoint module with x and y displacements 0 or -1.
ReseedablePtr makeQuadrantSelector(ReseedablePtr source, bool x_positive, bool y_positive);

// Makes a CornerCombiner scaled and clamped to the interval [-1., 1.].
ReseedablePtr makeCornerCombiner(bool x_positive, bool y_positive, double power = 2.);

// Makes a NormLPQ clamped to the interval [min, 1.].
ReseedablePtr makeEdgeFavouringMask(double p, double q = 1., double min = -1.);

// Makes a noise module that rescales a module from range [-1,1] to range [min,max].
ReseedablePtr makeMovingScaleBias(ReseedablePtr source, ReseedablePtr min, ReseedablePtr max);

// Makes a noise module with value equal to x.
ReseedablePtr makeX();

// Makes a noise module with value equal to y.
ReseedablePtr makeY();

// Makes a noise module with value equal to z.
ReseedablePtr makeZ();

// Makes a constant noise module with value c.
ReseedablePtr makeConst(double c);

// Makes a MovingScaleBias instance with ranges:
// [1,1] when d((x,y),origin) == 0,
// [0,0] when d((x,y),origin) >= length,
// [0,1] when d((x,y),origin) == length/2,
// where origin is determined by the *_positive parameters.
// The middle_length parameter controls the size
// of the region with range [0,1].
// It must be less than length.
ReseedablePtr makeLinearMovingScaleBias(ReseedablePtr source,
                                        bool x_positive, bool y_positive,
                                        double length = 1., double middle_length = 0.);

// Makes a placeholder noise module (a Perlin noise module with typical parameters).
ReseedablePtr makePlaceholder(int seed = 0);

template<typename InputIt>
ReseedablePtr terrace(ReseedablePtr source, InputIt first, InputIt last, bool inverted)
{
    static_assert(std::is_base_of<std::input_iterator_tag,
                  typename std::iterator_traits<InputIt>::iterator_category>::value,
                  "InputIt must have input_iterator_tag");
    static_assert(std::is_same<typename std::iterator_traits<InputIt>::value_type,
                  double>::value,
                  "InputIt must yield values of type double");
    auto terrace_p = std::make_shared<Reseedable<Terrace>>();
    terrace_p->module.InvertTerraces(inverted);
    std::for_each(first, last, [&terrace_p](const auto control_point)
    {
        terrace_p->module.AddControlPoint(control_point);
    });
    terrace_p->module.SetSourceModule(0, source->getModule());
    return makeModuleGroup({
        {"source", source},
        {"output", terrace_p}
    });
}

template<typename InputIt>
ReseedablePtr curve(ReseedablePtr source, InputIt first, InputIt last)
{
    static_assert(std::is_base_of<std::input_iterator_tag,
                  typename std::iterator_traits<InputIt>::iterator_category>::value,
                  "InputIt must have input_iterator_tag");
    static_assert(std::is_same<typename std::iterator_traits<InputIt>::value_type,
                  std::pair<double, double>>::value,
                  "InputIt must yield values of type std::pair<double, double>");
    auto curve_p = std::make_shared<Reseedable<module::Curve>>();
    std::for_each(first, last, [&curve_p](const auto control_point)
    {
        curve_p->module.AddControlPoint(control_point.first, control_point.second);
    });
    curve_p->module.SetSourceModule(0, source->getModule());
    return makeModuleGroup({
        {"source", source},
        {"output", curve_p}
    });
}

} // namespace module

} // namespace noise