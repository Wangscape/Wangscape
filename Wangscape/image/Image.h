#pragma once

#include <SFML/Graphics.hpp>
#include <armadillo>
#include "Vector.h"

typedef arma::Mat<arma::u8> ImageGrey;
typedef arma::Cube<arma::u8> ImageStackGrey;
typedef arma::Cube<arma::u8> ImageColour;
typedef arma::Mat<double> ImageGreyFloat;
typedef arma::Mat<arma::u32> ImageGrey32;
typedef arma::Cube<arma::u32> ImageStackGrey32;

ImageColour imageFromSFImage(const sf::Image& image);
ImageGrey imageToGreyscale(const ImageColour& image);
ImageColour imageGreyscaleToImage(const ImageGrey& image);
sf::Image imageToSFImage(const ImageColour& image);

void copyRegion(const ImageGrey& source, ImageGrey& target,
                IVec source_origin, IVec target_origin, IVec size);
void copyRegionBounded(const ImageGrey& source, ImageGrey& target,
                       IVec source_origin, IVec target_origin, IVec size);

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
ImageGrey32 distances(const ImageGrey& traversable, const ImageGrey& targets, bool use_diagonals=true);
ImageStackGrey tessellated(const ImageGrey& image, const std::vector<IVec>& offsets);
