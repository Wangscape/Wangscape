#pragma once
#include <memory>
#include <utility>
#include <functional>
#include <noise/noise.h>

typedef noise::module::Module Module;
typedef std::shared_ptr<Module> ModulePtr;
typedef std::function<void(int)> SetSeedFn;
// typedef std::pair<ModulePtr, SetSeedFn> Reseedable;
struct Reseedable
{
    ModulePtr module;
    SetSeedFn setSeed;
    Reseedable abs();
    Reseedable clamp(double lower, double upper);
    Reseedable pow(double exponent);
    Reseedable invert();
    Reseedable scaleBias(double scale, double bias);
    //Reseedable curve(...?)
    //Reseedable terrace(...?)
    Reseedable operator+(Reseedable& other);
    Reseedable operator+(double bias);
    Reseedable max(Reseedable& other);
    Reseedable min(Reseedable& other);
    Reseedable operator*(Reseedable& other);
    Reseedable operator*(double scale);
    Reseedable pow(Reseedable& exponent);
    Reseedable blend(Reseedable& other, Reseedable& control);
    Reseedable select(Reseedable& other, Reseedable& control);
    Reseedable Displace(Reseedable& x_displace, Reseedable& y_displace, Reseedable& z_displace);
    Reseedable rotatePoint(double x_angle, double y_angle, double z_angle);
    Reseedable scalePoint(double x_scale, double y_scale, double z_scale);
    Reseedable translatePoint(double x_displace, double y_displace, double z_displace);
    Reseedable turbulence();



};