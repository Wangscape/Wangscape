#pragma once
#include <vector>
#include <noise/noise.h>
#include <SFML/Graphics.hpp>
#include <functional>
#include "RasterBase.h"

namespace noise
{

class RasterImage : public RasterBase
{
public:
    typedef sf::Color Colour;
    typedef std::function<Colour(Real)> ColourMaker;
    typedef sf::Image Image;

    RasterImage(Image& image);
    RasterImage(Image& image, Bounds bounds);
    RasterImage(Image& image, Bounds bounds, const NoiseModule& module);

    virtual size_t sizeX() const;
    virtual size_t sizeY() const;
    Colour get(size_t x, size_t y) const;
    virtual Colour makeColour(Real value);
protected:
    virtual void set(size_t x, size_t y, Real value);
    sf::Image& mImage;
};
} // namespace noise
