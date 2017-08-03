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
    Module::Module(GetSourceModuleCount()),
    mRegion(0.0, 0.0, 1.0, 1.0),
    mMaxScale(false)
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
    if (it != loadedImages.cend())
    {
        mFilename = filename;
        mImage = it->second;
        if (mMaxScale)
            updateMax();
        return;
    }
    auto file_path = filePath(filename);
    auto bitmap = std::make_shared<sf::Image>();
    if (!bitmap->loadFromFile(file_path))
    {
        logError() << "Bitmap module: Could not load image from " << file_path;
        throw std::runtime_error("Invalid Bitmap filename");
    }
    for (size_t y = 0; y < bitmap->getSize().y; y++)
    {
        for (size_t x = 0; x < bitmap->getSize().x; x++)
        {
            auto pixel = bitmap->getPixel(x, y);
            if (pixel.r != pixel.g || pixel.g != pixel.b)
            {
                logWarning() << "Image at " << file_path << " loaded into Bitmap module is not greyscale at " <<
                    x << ", " << y << ".";
            }
        }
    }
    loadedImages.insert({filename, bitmap});
    mImage = bitmap;
    mFilename = filename;
    if (mMaxScale)
        updateMax();
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

void Bitmap::SetDefaultValue(double default_value)
{
    mDefaultValue = default_value;
}

bool Bitmap::GetMaxScale() const
{
    return mMaxScale;
}

void Bitmap::SetMaxScale(bool max_scale)
{
    mMaxScale = max_scale;
    if (mImage && max_scale)
        updateMax();
}

double Bitmap::GetValue(double x, double y, double z) const
{
    if (!mRegion.contains(x, y))
        return mDefaultValue;
    if (mImage->getSize().x == 0 || mImage->getSize().y == 0)
    {
        logError() << "Tried to call Bitmap::GetValue with zero-pixel resolution";
        throw std::runtime_error("Invalid Bitmap module configuration");
    }
    sf::Vector2<double> offset = {x, y};

    offset.x -= mRegion.left;
    offset.y -= mRegion.top;

    offset.x /= mRegion.width;
    offset.y /= mRegion.height;

    offset.x *= mImage->getSize().x;
    offset.y *= mImage->getSize().y;

    size_t x_image = static_cast<size_t>(offset.x);
    size_t y_image = static_cast<size_t>(offset.y);

    if (mMaxScale)
        return getPixel(x_image, y_image) / mMaxValue;
    else
        return getPixel(x_image, y_image);
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

void Bitmap::updateMax()
{
    // This could also be automatically cached in loadedImages.
    mMaxValue = 0;
    for (size_t y = 0; y < mImage->getSize().y; y++)
    {
        for (size_t x = 0; x < mImage->getSize().x; x++)
        {
            mMaxValue = std::max(mMaxValue, mImage->getPixel(x, y).r);
        }
    }
}

} // namespace module
} // namespace noise
