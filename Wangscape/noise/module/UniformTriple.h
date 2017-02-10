#pragma once
#include <tuple>
namespace noise
{
namespace module
{
struct UniformTriple
{
    double x;
    double y;
    double z;

    UniformTriple(double x_, double y_, double z_) :
        x(x_),
        y(y_),
        z(z_)
    {
    }
    explicit UniformTriple(double xyz_) :
        x(xyz_),
        y(xyz_),
        z(xyz_)
    {
    }
    UniformTriple(std::tuple<double, double, double> xyz_) :
    x(std::get<0>(xyz_)),
    y(std::get<1>(xyz_)),
    z(std::get<2>(xyz_))
    {
    }
    std::tuple<double, double, double> asTuple() const
    {
        return{x, y, z};
    }
};
} // namespace module
} // namespace noise