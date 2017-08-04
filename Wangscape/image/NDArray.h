#pragma once

#include <xtensor/xarray.hpp>
#include <SFML/Graphics.hpp>

template<typename T>
using NDArray = xt::xarray<T, xt::layout_type::dynamic>;

NDArray<sf::Uint8> imageFromSFImage(const sf::Image& image);

NDArray<sf::Uint8> imageToGreyscale(const NDArray<sf::Uint8>& image);