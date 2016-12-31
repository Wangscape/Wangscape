#pragma once
#include <memory>
#include <utility>
#include <functional>
#include <noise/noise.h>

namespace noise
{

typedef module::Module Module;
typedef std::shared_ptr<Module> ModulePtr;
typedef std::function<void(int)> SetSeedFn;
// typedef std::pair<ModulePtr, SetSeedFn> Reseedable;
struct Reseedable
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
    //Reseedable curve(...?)
    //Reseedable terrace(...?)
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
};

} // namespace noise
