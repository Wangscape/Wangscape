#include "TileRearrangement.h"

sf::Image TileRearrangement::rearrangeTexture(const sf::Image & base_texture) const
{
    ImageColour base_array = imageFromSFImage(base_texture);
    ImageStackGrey dual_r(dualSize.y, dualSize.x, basePartition.n_slices, arma::fill::zeros);
    ImageStackGrey dual_g(dualSize.y, dualSize.x, basePartition.n_slices, arma::fill::zeros);
    ImageStackGrey dual_b(dualSize.y, dualSize.x, basePartition.n_slices, arma::fill::zeros);
    ImageStackGrey dual_a(dualSize.y, dualSize.x, basePartition.n_slices, arma::fill::zeros);
    const auto rearrange_colour = [this](const ImageGrey &base_channel, ImageStackGrey& dual_channel_stack)
    {
        for (unsigned int c = 0; c < basePartition.n_slices; c++)
        {
            copyRegionBounded(
                base_channel, dual_channel_stack.slice(c),
                {0, 0},
                allOffsets[c] - dualOffset,
                sf::Vector2i(dualSize));
            dual_channel_stack.slice(c) %= dualPartition.slice(c);
        }
    };
    rearrange_colour(base_array.slice(0), dual_r);
    rearrange_colour(base_array.slice(1), dual_g);
    rearrange_colour(base_array.slice(2), dual_b);
    rearrange_colour(base_array.slice(3), dual_a);
    ImageColour dual(dualSize.y, dualSize.x, 4);
    dual.slice(0) = arma::sum(dual_r, 2).eval();
    dual.slice(1) = arma::sum(dual_g, 2).eval();
    dual.slice(2) = arma::sum(dual_b, 2).eval();
    dual.slice(3) = arma::sum(dual_a, 2).eval();
    return imageToSFImage(dual);
}
