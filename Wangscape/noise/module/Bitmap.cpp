#include "Bitmap.h"
#include "logging/Logging.h"
#include "OptionsManager.h"
#include <boost/filesystem.hpp>

namespace noise
{
namespace module
{

namespace {
static std::map<std::string, std::shared_ptr<ImageGreyFloat>> loadedImages;
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
    sf::Image sf_bitmap;
    logInfo() << "Loading image at " << file_path << "into Bitmap module";
    if (!sf_bitmap.loadFromFile(file_path))
    {
        logError() << "Could not load image";
        throw std::runtime_error("Invalid Bitmap filename");
    }
    auto bitmap = imageFromSFImage(sf_bitmap);
    auto bitmap_gs = imageToGreyscale(bitmap);
    auto bitmap_d = std::make_shared<ImageGreyFloat>(arma::conv_to<ImageGreyFloat>::from(bitmap_gs));
    loadedImages.insert({filename, bitmap_d});
    mImage = bitmap_d;
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
    if (mImage->n_rows == 0 || mImage->n_cols == 0)
    {
        logError() << "Tried to call Bitmap::GetValue with zero-pixel resolution";
        throw std::runtime_error("Invalid Bitmap module configuration");
    }
    sf::Vector2<double> offset = {x, y};

    offset.x -= mRegion.left;
    offset.y -= mRegion.top;

    offset.x /= mRegion.width;
    offset.y /= mRegion.height;

    offset.x *= mImage->n_cols;
    offset.y *= mImage->n_rows;

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
    return (*mImage)(y,x);
}

std::string Bitmap::filePath(const std::string& filename) const
{
    const auto& base_path = getOptionsManager().getOptions().paths.directory;
    return (boost::filesystem::path(base_path) / filename).string();
}

void Bitmap::updateMax()
{
    mMaxValue = mImage->max();
}

} // namespace module
} // namespace noise
