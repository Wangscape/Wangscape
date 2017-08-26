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

// Converts an SFML image to an RGBA image array.
ImageColour imageFromSFImage(const sf::Image& image);
// Converts an RGBA image to a greyscale image, warning if any pixel has colour or transparency.
ImageGrey imageToGreyscale(const ImageColour& image);
// Converts a greyscale image array to an RGBA image array.
ImageColour imageGreyscaleToImage(const ImageGrey& image);
// Converts an RGBA image array to an SFML image.
sf::Image imageToSFImage(const ImageColour& image);

// Translates and copies a region of an image to another image without checking bounds.
void copyRegion(const ImageGrey& source, ImageGrey& target,
                IVec source_origin, IVec target_origin, IVec size);
// Restricts the origin and size parameters, then translates and copies a region of an image to another image.
void copyRegionBounded(const ImageGrey& source, ImageGrey& target,
                       IVec source_origin, IVec target_origin, IVec size);

// Returns true iff the nonzero pixels of the image form a single connected component.
bool isConnected(const ImageGrey& image, bool use_diagonals = false);
// Returns true iff there is at least one nonzero pixel.
bool isNonzero(const ImageGrey& image);
// Returns true iff every pixel is 0 or 1.
bool isBinary(const ImageGrey& image);
// Returns the input image with a one-element-wide padding of zeros.
ImageGrey padded(const ImageGrey& image);
// Undoes padding by stripping the first and last rows and columns.
ImageGrey unpadded(const ImageGrey& image);
// Undoes padding of a stack by stripping the first and last rows and columns. Every slice is preserved.
ImageStackGrey unpaddedStack(const ImageStackGrey& image_stack);
// Returns an image in which every pixel's value is the maximum value within its neighbourhood in the input image.
ImageGrey dilated(const ImageGrey& image, bool use_diagonals = true, arma::u8 edge_value = 0);
// Returns an image in which every pixel's value is the minimum value within its neighbourhood in the input image.
ImageGrey eroded(const ImageGrey& image, bool use_diagonals = true, arma::u8 edge_value = 255);
// Returns a binary image describing the input's boundary. A pixel is 1 if it is nonzero in the input and adjacent to a zero pixel.
ImageGrey boundary(const ImageGrey& image, bool use_diagonals = true);
// Returns a binary image describing the intersection between the input image and the dilation of the neighbours argument.
// A pixel is nonzero if it is nonzero in the input and adjacent to a nonzero pixel in neighbours.
ImageGrey neighbourhoodIntersection(const ImageGrey& image, const ImageGrey& neighbours, bool use_diagonals = true);
// Returns a rectangle describing the bounding box of the nonzero pixels in the input image.
sf::IntRect regionBox(const ImageGrey& image);
// Returns the smallest rectangle containing the two input rectangles.
sf::IntRect boxUnion(sf::IntRect a, sf::IntRect b);
// Returns a 32-bit greyscale image describing the minimum distance of each pixel in traversable from a pixel in targets.
ImageGrey32 distances(const ImageGrey& traversable, const ImageGrey& targets, bool use_diagonals=true);
// Returns an image stack where each slice has the input image translated by an offset.
ImageStackGrey tessellated(const ImageGrey& image, const std::vector<IVec>& offsets);
