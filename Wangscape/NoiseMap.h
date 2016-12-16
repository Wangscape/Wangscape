#include <vector>
#include <noise/noise.h>
#include <SFML/Graphics.hpp>
#include <functional>

class NoiseMapBase
{
public:
    typedef noise::module::Module NoiseModule;
    typedef double Real;
    typedef sf::Rect<Real> Bounds;

    NoiseMapBase();
    NoiseMapBase(Bounds bounds);

    const Bounds& bounds() const;
    Bounds& bounds();
    void build(const NoiseModule& module);

    virtual size_t sizeX() const = 0;
    virtual size_t sizeY() const = 0;
protected:
    virtual void set(size_t x, size_t y, Real value) = 0;
    Bounds mBounds;
};

class NoiseMapVector : public NoiseMapBase
{
public:
    typedef std::vector<Real> Data;
    NoiseMapVector(size_t x, size_t y);
    NoiseMapVector(size_t x, size_t y, Bounds bounds);
    NoiseMapVector(size_t x, size_t y, Bounds bounds, const NoiseModule& module);

    virtual size_t sizeX() const;
    virtual size_t sizeY() const;
    Real get(size_t x, size_t y) const;
protected:
    virtual void set(size_t x, size_t y, Real value);
    size_t index(size_t x, size_t y) const;
    size_t mSizeX;
    size_t mSizeY;
    Data mData;
};

class NoiseMapImage : public NoiseMapBase
{
    typedef sf::Color Colour;
    typedef std::function<Colour(Real)> ColourMaker;
    typedef sf::Image Image;

    NoiseMapImage(Image& image);
    NoiseMapImage(Image& image, Bounds bounds);
    NoiseMapImage(Image& image, Bounds bounds, const NoiseModule& module);

    virtual size_t sizeX() const;
    virtual size_t sizeY() const;
    Colour get(size_t x, size_t y) const;
    virtual Colour makeColour(Real value);
protected:
    virtual void set(size_t x, size_t y, Real value);
    sf::Image& mImage;
};