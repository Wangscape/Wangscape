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

    explicit RasterImage(Image& image);
    RasterImage(Image& image, Bounds bounds);
    RasterImage(Image& image, Bounds bounds, const module::Module& module);

    virtual size_t sizeX() const;
    virtual size_t sizeY() const;
    Colour get(size_t x, size_t y) const;

    // Converts a noise value to a colour for debug visualisation.
    // The output of this function is used to set pixels in the image provided.
    // Can be overridden in derived classes.
    // Default colour map:
    // Red at -1, Black at 0, Blue at +1.
    virtual Colour makeColour(Real value);
protected:
    virtual void set(size_t x, size_t y, Real value);
    sf::Image& mImage;
};
} // namespace noise
