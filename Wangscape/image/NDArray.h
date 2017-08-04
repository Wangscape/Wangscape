#pragma once

#include <SFML/Graphics.hpp>
#include <armadillo>

typedef arma::Cube<arma::u8> ImageColour;
typedef arma::Mat<arma::u8> ImageGrey;
typedef arma::Mat<double> ImageGreyFloat;

ImageColour imageFromSFImage(const sf::Image& image);

ImageGrey imageToGreyscale(const ImageColour& image);