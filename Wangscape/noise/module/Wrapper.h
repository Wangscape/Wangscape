#pragma once

#include <memory>
#include <vector>
#include <type_traits>
#include "WrapperBase.h"
#include "ModuleGroup.h"

namespace noise
{
namespace module
{

template<typename M>
class Wrapper : public WrapperBase
{
public:
    M module;

    virtual void setSeed(int seed);
    virtual Module& getModule();
    virtual const Module& getModule() const;
    virtual void setControlModule(const Module& source_module);
    virtual void setDisplaceModule(int index, const Module& source_module);
    template<typename N=M>
    typename std::enable_if_t<std::is_same<N, Curve>::value>
        setAllCurveControlPoints(std::vector<std::pair<double, double>> control_points);
    template<typename N = M>
    typename std::enable_if_t<std::is_same<N, Curve>::value, std::vector<std::pair<double, double>>>
        getAllCurveControlPoints();
    template<typename N = M>
    typename std::enable_if_t<std::is_same<N, Terrace>::value>
        setAllTerraceControlPoints(std::vector<double> control_points);
    template<typename N = M>
    typename std::enable_if_t<std::is_same<N, Terrace>::value, std::vector<double>>
        getAllTerraceControlPoints();
};

template<typename M> void Wrapper<M>::setSeed(int seed)
{ }

template<typename M>
inline Module & Wrapper<M>::getModule()
{
    return module;
}

template<typename M>
inline const Module & Wrapper<M>::getModule() const
{
    return module;
}

template<typename M>
void Wrapper<M>::setControlModule(const Module & source_module)
{
    throw std::runtime_error("Tried to set ControlModule of incompatible Module");
}

template<typename M>
void Wrapper<M>::setDisplaceModule(int index, const Module & source_module)
{
    throw std::runtime_error("Tried to set DisplaceModule of incompatible Module");
}

template<>
template<typename N>
inline typename std::enable_if_t<std::is_same<N, Curve>::value> Wrapper<Curve>::setAllCurveControlPoints(std::vector<std::pair<double, double>> control_points)
{
    for (auto it : control_points)
    {
        module.AddControlPoint(it.first, it.second);
    }
}

template<>
template<typename N>
inline typename std::enable_if_t<std::is_same<N, Curve>::value, std::vector<std::pair<double, double>>> Wrapper<Curve>::getAllCurveControlPoints()
{
    std::vector<std::pair<double, double>> control_points;
    const auto raw_control_points = m.GetControlPointArray();
    int control_point_count = m.GetControlPointCount();
    for (int i = 0; i < control_point_count; i++)
    {
        const auto control_point = raw_control_points[i];
        control_points.push_back({control_point.inputValue, control_point.outputValue});
    }
}

template<>
template<typename N>
inline typename std::enable_if_t<std::is_same<N, Terrace>::value, std::vector<double>> Wrapper<Terrace>::getAllTerraceControlPoints()
{
    std::vector<std::pair<double, double>> control_points;
    const auto raw_control_points = m.GetControlPointArray();
    int control_point_count = m.GetControlPointCount();
    for (int i = 0; i < control_point_count; i++)
    {
        control_points.push_back(raw_control_points[i]);
    }
}

template<>
template<typename N>
inline typename std::enable_if_t<std::is_same<N, Terrace>::value> Wrapper<Terrace>::setAllTerraceControlPoints(std::vector<double> control_points)
{
    for (auto it : control_points)
    {
        module.AddControlPoint(it);
    }
}


template<> void Wrapper<ModuleGroup>::setSeed(int seed);
template<> void Wrapper<Billow>::setSeed(int seed);
template<> void Wrapper<Perlin>::setSeed(int seed);
template<> void Wrapper<RidgedMulti>::setSeed(int seed);
template<> void Wrapper<Turbulence>::setSeed(int seed);
template<> void Wrapper<Voronoi>::setSeed(int seed);

template<> void Wrapper<Blend>::setControlModule(const Module& source_module);
template<> void Wrapper<Select>::setControlModule(const Module& source_module);

template<> void Wrapper<Displace>::setDisplaceModule(int index, const Module& source_module);

} // namespace noise
} // namespace module
