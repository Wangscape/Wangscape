#pragma once

#include <SFML/Graphics.hpp>
#include <armadillo>

typedef arma::Mat<arma::u8> ImageGrey;
typedef arma::Cube<arma::u8> ImageStackGrey;
typedef arma::Cube<arma::u8> ImageColour;
typedef arma::Mat<double> ImageGreyFloat;

ImageColour imageFromSFImage(const sf::Image& image);
ImageGrey imageToGreyscale(const ImageColour& image);
ImageColour imageGreyscaleToImage(const ImageGrey& image);
sf::Image imageToSFImage(const ImageColour& image);

void copyRegion(const ImageGrey& source, ImageGrey& target,
                sf::Vector2i source_origin, sf::Vector2i target_origin, sf::Vector2i size);
void copyRegionBounded(const ImageGrey& source, ImageGrey& target,
                       sf::Vector2i source_origin, sf::Vector2i target_origin, sf::Vector2i size);

bool isConnected(const ImageGrey& image, bool use_diagonals = false);
bool isNonzero(const ImageGrey& image);
bool isBinary(const ImageGrey& image);
ImageGrey padded(const ImageGrey& image);
ImageGrey unpadded(const ImageGrey& image);
ImageStackGrey unpaddedStack(const ImageStackGrey& image_stack);
ImageGrey dilatedEroded(const ImageGrey& image, bool use_diagonals, arma::u8 edge_value, bool dilate);
ImageGrey dilated(const ImageGrey& image, bool use_diagonals = true, arma::u8 edge_value = 0);
ImageGrey eroded(const ImageGrey& image, bool use_diagonals = true, arma::u8 edge_value = 255);
ImageGrey boundary(const ImageGrey& image, bool use_diagonals = true);
ImageGrey neighbourhoodIntersection(const ImageGrey& image, const ImageGrey& neighbours, bool use_diagonals = true);
sf::IntRect regionBox(const ImageGrey& image);
sf::IntRect boxUnion(sf::IntRect a, sf::IntRect b);
