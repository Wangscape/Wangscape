#include "Bitmap.h"
#include "logging/Logging.h"
#include "OptionsManager.h"
#include <boost/filesystem.hpp>

namespace noise
{
namespace module
{

namespace {
// TODO (Serin): extract the data format from noise::RasterBase into a separate class and use it here
static std::map<std::string, std::shared_ptr<sf::Image>> loadedImages;
}


Bitmap::Bitmap() : 
    Module::Module(GetSourceModuleCount())
{
}

const std::string & Bitmap::GetFilename() const
{
    return mFilename;
}

void Bitmap::SetFilename(const std::string & filename)
{
    // Load and process file if not already done
    auto it = loadedImages.find(filename);
    if (it == loadedImages.cend())
        return;
    auto bitmap = std::make_shared<sf::Image>();
    bitmap->loadFromFile(filePath(filename));
    for (size_t y = 0; y < bitmap->getSize().y; y++)
    {
        for (size_t x = 0; x < bitmap->getSize().x; x++)
        {
            auto pixel = bitmap->getPixel(x, y);
            if (pixel.r != pixel.g || pixel.g != pixel.b)
            {
                logWarning() << "Image at " << filename << " loaded into Bitmap module is not greyscale at " <<
                    x << ", " << y << ".";
            }
        }
    }
    loadedImages.insert({filename, bitmap});
    mImage = bitmap;
    mFilename = filename;
}

const sf::Vector2u & Bitmap::GetResolution() const
{
    return mResolution;
}

void Bitmap::SetResolution(const sf::Vector2u & resolution)
{
    mResolution = resolution;
}

sf::Rect<double> Bitmap::GetRegion() const
{
    return sf::Rect<double>();
}

void Bitmap::SetRegion(sf::Rect<double> region)
{
    mRegion = region;
}

double Bitmap::GetDefaultValue() const
{
    return mDefaultValue;
}

void Bitmap::SetDefaultValue(double defaultValue)
{
    mDefaultValue = defaultValue;
}

double Bitmap::GetValue(double x, double y, double z) const
{
    if (mRegion.contains(x, y))
        return mDefaultValue;
    if (mResolution.x == 0 || mResolution.y == 0)
    {
        logError() << "Tried to call Bitmap::GetValue with zero-pixel resolution";
        throw std::runtime_error("Invalid Bitmap module configuration");
    }
    sf::Vector2<double> offset = {x, y};

    offset.x -= mRegion.left;
    offset.y -= mRegion.top;

    offset.x /= mRegion.width;
    offset.y /= mRegion.height;

    offset.x *= mResolution.x;
    offset.y *= mResolution.y;

    return getPixel(static_cast<size_t>(offset.x), static_cast<size_t>(offset.y));
}

double Bitmap::getPixel(size_t x, size_t y) const
{
    if (!mImage)
    {
        logError() << "Tried to call Bitmap::getPixel without valid image";
        throw std::runtime_error("Bitmap not initialised");
    }
    return mImage->getPixel(x, y).r;
}

std::string Bitmap::filePath(const std::string& filename) const
{
    const auto& base_path = getOptionsManager().getOptions().paths.directory;
    return (boost::filesystem::path(base_path) / filename).string();

}

} // namespace module
} // namespace noise