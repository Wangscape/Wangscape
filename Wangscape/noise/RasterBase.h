#pragma once
#include <vector>
#include <noise/noise.h>
#include <SFML/Graphics.hpp>
#include <functional>

namespace noise
{

class RasterBase
{
public:
    typedef module::Module NoiseModule;
    typedef double Real;
    typedef sf::Rect<Real> Bounds;

    RasterBase() = default;
    RasterBase(Bounds bounds);

    virtual ~RasterBase() = default;

    const Bounds& bounds() const;
    Bounds& bounds();
    void build(const NoiseModule& module);

    virtual size_t sizeX() const = 0;
    virtual size_t sizeY() const = 0;
protected:
    virtual void set(size_t x, size_t y, Real value) = 0;
    Bounds mBounds;
};

} // namespace noise
