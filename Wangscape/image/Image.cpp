#include "Image.h"
#include <vector>
#include "logging/logging.h"

ImageColour imageFromSFImage(const sf::Image & sf_image)
{
    auto shape = sf_image.getSize();
    ImageColour image(shape.x, shape.y, 4);
    for(size_t y = 0; y < shape.y; y++)
        for (size_t x = 0; x < shape.x; x++)
        {
            auto pixel = sf_image.getPixel(x, y);
            image(x, y, 0) = pixel.r;
            image(x, y, 1) = pixel.g;
            image(x, y, 2) = pixel.b;
            image(x, y, 3) = pixel.a;
        }
    return image;
}

ImageGrey imageToGreyscale(const ImageColour & image)
{
    const auto image_r = image.slice(0);
    const auto image_g = image.slice(1);
    const auto image_b = image.slice(2);
    const auto image_a = image.slice(3);
    if (arma::any(arma::vectorise((image_r != image_g).eval())) ||
        arma::any(arma::vectorise((image_g != image_b).eval())) ||
        arma::any(arma::vectorise((image_a != 255).eval())))
        logWarning() << "Image is not greyscale; using red channel";
    return image_r;
}
