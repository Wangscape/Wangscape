#pragma once
#include <memory>
#include <string>
#include <noise/noise.h>
#include <SFML/Graphics.hpp>

namespace noise
{
namespace module
{

// Noise module that takes values from a bitmap.
// The bitmap file should be a greyscale image.
// Only red values will be used.
class Bitmap : public Module
{
public:
    Bitmap();
    virtual int GetSourceModuleCount() const
    {
        return 0;
    }
    const std::string& GetFilename() const;
    void SetFilename(const std::string& filename);

    const sf::Vector2u& GetResolution() const;
    void SetResolution(const sf::Vector2u& resolution);

    sf::Rect<double> GetRegion() const;
    void SetRegion(sf::Rect<double> region);

    double GetDefaultValue() const;
    void SetDefaultValue(double defaultValue);


    virtual double GetValue(double x, double y, double z) const;
private:
    double getPixel(size_t x, size_t y) const;
    std::string  mFilename;
    sf::Vector2u mResolution;
    sf::Rect<double> mRegion;
    double mDefaultValue;
    std::shared_ptr<sf::Image> mImage;
};

} // namespace module
} // namespace noise
