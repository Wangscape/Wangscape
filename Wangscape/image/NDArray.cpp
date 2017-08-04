#include "NDArray.h"
#include <vector>
#include "logging/logging.h"
#include <xtensor/xview.hpp>

typename NDArray<sf::Uint8> imageFromSFImage(const sf::Image& sf_image)
{
    std::vector<size_t> shape{sf_image.getSize().x, sf_image.getSize().y, 4};
    NDArray<sf::Uint8> image(shape);
    for(size_t y = 0; y < shape[1]; y++)
        for (size_t x = 0; x < shape[0]; x++)
        {
            auto pixel = sf_image.getPixel(x, y);
            image[0, y, x] = pixel.r;
            image[1, y, x] = pixel.g;
            image[2, y, x] = pixel.b;
            image[3, y, x] = pixel.a;
        }
    return image;
}

NDArray<sf::Uint8> imageToGreyscale(const NDArray<sf::Uint8>& image)
{
    const auto image_r = xt::view(image, 0, xt::all(), xt::all());
    const auto image_g = xt::view(image, 1, xt::all(), xt::all());
    const auto image_b = xt::view(image, 2, xt::all(), xt::all());
    const auto image_a = xt::view(image, 3, xt::all(), xt::all());

    if (xt::any(xt::not_equal(image_r, image_g)) ||
        xt::any(xt::not_equal(image_g, image_b)) ||
        xt::any(xt::not_equal(image_a, 255)))
        logWarning() << "Image is not greyscale; using red channel";
    NDArray<sf::Uint8> image_gs = image_r;
    return image_gs;
}
