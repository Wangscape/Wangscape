#pragma once
#include <memory>
#include <string>
#include <noise/noise.h>
#include <SFML/Graphics.hpp>

namespace noise
{
namespace module
{

// Noise module that takes values from a bitmap file.
// The bitmap file should be a greyscale image.
// Only red values will be used.
// The Region attribute specifies the rectangular
// area over which the bitmap values will be used.
// The DefaultValue attribute specifies the value
// used outside of that area.
// The MaxScale attribute specifies whether output
// will use the original integer values, or scale
// by the maximum value in the image.
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

    sf::Rect<double> GetRegion() const;
    void SetRegion(sf::Rect<double> region);

    double GetDefaultValue() const;
    void SetDefaultValue(double default_value);

    bool GetMaxScale() const;
    void SetMaxScale(bool max_scale);

    virtual double GetValue(double x, double y, double z) const;
private:
    double getPixel(size_t x, size_t y) const;
    std::string filePath(const std::string& filename) const;
    void updateMax();

    std::string mFilename;
    sf::Rect<double> mRegion;
    double mDefaultValue;
    bool mMaxScale;
    sf::Uint8 mMaxValue;
    std::shared_ptr<sf::Image> mImage;
};

} // namespace module
} // namespace noise
