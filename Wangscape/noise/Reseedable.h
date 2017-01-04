#pragma once
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <iterator>
#include <noise/noise.h>

namespace noise
{

typedef module::Module Module;
typedef std::shared_ptr<Module> ModulePtr;
typedef std::function<void(int)> SetSeedFn;
// typedef std::pair<ModulePtr, SetSeedFn> Reseedable;
struct Reseedable final
{
    ModulePtr module;
    SetSeedFn setSeed;

    double getValue(double x, double y, double z);

    Reseedable abs();
    Reseedable clamp(double lower, double upper);
    Reseedable pow(Reseedable& exponent);
    Reseedable pow(double exponent);
    Reseedable exp(double base);
    Reseedable invert();
    Reseedable scaleBias(double scale, double bias);
    Reseedable operator+(Reseedable& other);
    Reseedable operator+(double bias);
    Reseedable operator-(Reseedable& other);
    Reseedable operator-(double bias);
    Reseedable operator-();
    Reseedable max(Reseedable& other);
    Reseedable max(double other);
    Reseedable min(Reseedable& other);
    Reseedable min(double other);
    Reseedable operator*(Reseedable& other);
    Reseedable operator*(double scale);
    Reseedable blend(Reseedable& source_a, Reseedable& source_b);
    Reseedable select(Reseedable& source_a, Reseedable& source_b);
    Reseedable displace(Reseedable& x_displace, Reseedable& y_displace, Reseedable& z_displace);
    Reseedable rotatePoint(double x_angle, double y_angle, double z_angle);
    Reseedable scalePoint(double x_scale, double y_scale, double z_scale);
    Reseedable translatePoint(double x_displace, double y_displace, double z_displace);
    Reseedable turbulence(double frequency, double power, int roughness, int seed);
    template<typename InputIt>
    Reseedable terrace(InputIt first, InputIt last, bool inverted = false);
    Reseedable terrace(int controlPointCount, bool inverted = false);
    template<typename InputIt>
    Reseedable curve(InputIt first, InputIt last);
private:
    Reseedable finaliseTerrace(std::shared_ptr<module::Terrace>& terrace_ptr);
    Reseedable finaliseCurve(std::shared_ptr<module::Curve>& curve_ptr);
};

template<typename InputIt>
inline Reseedable Reseedable::terrace(InputIt first, InputIt last, bool inverted)
{
    static_assert(std::is_same<std::iterator_traits<InputIt>::iterator_category::input_iterator_tag,
                  std::input_iterator_tag>::value,
                  "InputIt must have input_iterator_tag");
    static_assert(std::is_same<typename std::iterator_traits<InputIt>::value_type,
                               double>::value,
                  "InputIt must yield values of type double");
    auto terrace_p = std::make_shared<module::Terrace>();
    terrace_p->InvertTerraces(inverted);
    std::for_each(first, last, [&terrace_p](const auto control_point)
    {
        terrace_p->AddControlPoint(control_point);
    });
    return finaliseTerrace(terrace_p);
}

template<typename InputIt>
inline Reseedable Reseedable::curve(InputIt first, InputIt last)
{
    static_assert(std::is_same<std::iterator_traits<InputIt>::iterator_category::input_iterator_tag,
                               std::input_iterator_tag>::value,
                  "InputIt must have input_iterator_tag");
    static_assert(std::is_same<typename std::iterator_traits<InputIt>::value_type,
                               std::pair<double, double>>::value,
                  "InputIt must yield values of type std::pair<double, double>");
    auto curve_p = std::make_shared<module::Curve>();
    std::for_each(first, last, [&curve_p](const auto control_point)
    {
        curve_p->AddControlPoint(control_point.first, control_point.second);
    });
    return finaliseCurve(curve_p);
}

} // namespace noise
