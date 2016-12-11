#include <vector>
#include <noise/noise.h>
#include <SFML/Graphics/Rect.hpp>

class NoiseMap
{
public:
    typedef noise::module::Module NoiseModule;
    typedef double Real;
    typedef sf::Rect<Real> Bounds;
    typedef std::vector<Real> Data;
    NoiseMap(size_t x, size_t y);
    NoiseMap(size_t x, size_t y, Bounds bounds);
    NoiseMap(size_t x, size_t y, Bounds bounds, const NoiseModule& module);
    size_t getX() const;
    size_t getY() const;
    const Bounds& bounds() const;
    Bounds& bounds();
    void build(const NoiseModule& module);
    Real get(size_t x, size_t y) const;
protected:
    size_t index(size_t x, size_t y) const;
    size_t mSizeX;
    size_t mSizeY;
    Bounds mBounds;
    Data mData;
};