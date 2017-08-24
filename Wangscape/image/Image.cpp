#include "Image.h"
#include <vector>
#include <set>
#

#include "logging/Logging.h"

const static std::vector<sf::Vector2i> orthogonal_steps{
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const static std::vector<sf::Vector2i> orthodiagonal_steps{
    {0, 1}, {1, 0}, {0, -1}, {-1, 0},
    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

ImageColour imageFromSFImage(const sf::Image & sf_image)
{
    auto shape = sf_image.getSize();
    ImageColour image(shape.y, shape.x, 4);
    for(size_t y = 0; y < shape.y; y++)
        for (size_t x = 0; x < shape.x; x++)
        {
            auto pixel = sf_image.getPixel(x, y);
            image(y, x, 0) = pixel.r;
            image(y, x, 1) = pixel.g;
            image(y, x, 2) = pixel.b;
            image(y, x, 3) = pixel.a;
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

ImageColour imageGreyscaleToImage(const ImageGrey & image)
{
    ImageColour image_colour(image.n_rows, image.n_cols, 4);
    image_colour.slice(0) = image;
    image_colour.slice(1) = image;
    image_colour.slice(2) = image;
    image_colour.slice(3).fill(255);
    return image_colour;
}

sf::Image imageToSFImage(const ImageColour & image)
{
    sf::Image sf_image;
    sf_image.create(image.n_cols, image.n_rows);
    auto shape = sf_image.getSize();
    for (size_t y = 0; y < shape.y; y++)
        for (size_t x = 0; x < shape.x; x++)
        {
            const auto pixel = image.tube(y, x);
            sf_image.setPixel(x, y, sf::Color(pixel(0), pixel(1), pixel(2), pixel(3)));
        }
    return sf_image;
}

void copyRegionBounded(const ImageGrey& source, ImageGrey & target, sf::Vector2i source_origin, sf::Vector2i target_origin, sf::Vector2i size)
{
    const auto source_shape = arma::size(source);
    const auto target_shape = arma::size(target);
    // Cut off negative indices in source or target
    sf::Vector2i origin_excess;
    origin_excess.x = std::min({source_origin.x,
                                target_origin.x,
                                0});
    origin_excess.y = std::min({source_origin.y,
                                target_origin.y,
                                0});
    source_origin -= origin_excess;
    target_origin -= origin_excess;
    size += origin_excess;
    // Cut off indices greater than shape in source or target
    sf::Vector2i end_excess;
    const auto source_end = source_origin + size;
    const auto target_end = target_origin + size;
    end_excess.x = std::max({source_end.x - (int)source_shape.n_cols,
                             target_end.x - (int)target_shape.n_cols,
                             0});
    end_excess.y = std::max({source_end.y - (int)source_shape.n_rows,
                             target_end.y - (int)target_shape.n_rows,
                             0});
    size -= end_excess;
    copyRegion(source, target, source_origin, target_origin, size);
}

void copyRegion(const ImageGrey& source, ImageGrey & target,
                sf::Vector2i source_origin, sf::Vector2i target_origin, sf::Vector2i size)
{
    const auto source_end = source_origin + size;
    const auto target_end = target_origin + size;
    target.submat(arma::span(target_origin.y, target_end.y - 1),
                  arma::span(target_origin.x, target_end.x - 1)) =
        source.submat(arma::span(source_origin.y, source_end.y - 1),
                      arma::span(source_origin.x, source_end.x - 1));
}

bool isConnected(const ImageGrey & image, bool use_diagonals)
{
    unsigned int n_ones = arma::nonzeros(image).eval().size();
    if (n_ones == 0)
        return false;
    const auto start_index = image.index_max();
    const auto start = arma::ind2sub(size(image), start_index);
    const auto less = [](sf::Vector2i a, sf::Vector2i b) {return std::tie(a.x, a.y) < std::tie(b.x, b.y); };
    std::set<sf::Vector2i, decltype(less)> component(less);
    std::set<sf::Vector2i, decltype(less)> border(less);
    border.insert(sf::Vector2i(start(1), start(0)));
    const auto& steps = use_diagonals ? orthodiagonal_steps : orthogonal_steps;
    const auto in_bounds = [&image](sf::Vector2i point)
    {
        if (point.x < 0 || point.y < 0)
            return false;
        if ((unsigned int)point.x >= image.n_cols || (unsigned int)point.y >= image.n_rows)
            return false;
        return true;
    };
    while (!border.empty())
    {
        const auto point = *border.begin();
        border.erase(border.begin());
        component.insert(point);
        for (const auto& step : steps)
        {
            const auto new_point = point + step;
            if (!in_bounds(new_point))
                continue;
            if (component.find(new_point) != component.end())
                continue;
            if (image(new_point.y, new_point.x))
                border.insert(new_point);
        }
    }
    return component.size() == n_ones;
}

bool isNonzero(const ImageGrey & image)
{
    return image.max() != 0;
}

bool isBinary(const ImageGrey & image)
{
    return image.max() <= 1;
}

ImageGrey padded(const ImageGrey & image)
{
    ImageGrey result(arma::size(image) + 2, arma::fill::zeros);
    copyRegion(image, result,
               sf::Vector2i(0, 0), sf::Vector2i(1, 1),
               sf::Vector2i(image.n_cols, image.n_rows));
    return result;
}

ImageGrey unpadded(const ImageGrey & image)
{
    return image.submat(arma::span(1, image.n_rows - 2),
                        arma::span(1, image.n_cols - 2));
}

ImageStackGrey unpaddedStack(const ImageStackGrey & image_stack)
{
    return image_stack.subcube(arma::span(1,image_stack.n_rows-2),
                               arma::span(1, image_stack.n_cols- 2),
                               arma::span::all);
}

ImageGrey dilatedEroded(const ImageGrey & image, bool use_diagonals, arma::u8 edge_value, bool dilate)
{
    const auto& steps = use_diagonals ? orthodiagonal_steps : orthogonal_steps;
    const auto n_steps = steps.size();
    ImageStackGrey displacements(image.n_rows, image.n_cols, n_steps + 1);
    displacements.fill(edge_value);
    displacements.slice(0) = image;
    for (unsigned int s = 0; s < n_steps; s++)
    {
        copyRegionBounded(image, displacements.slice(s + 1),
                          sf::Vector2i(0, 0), steps[s],
                          sf::Vector2i(image.n_cols, image.n_rows));
    }
    if (dilate)
        return arma::max(displacements, 2).eval();
    else
        return arma::min(displacements, 2).eval();
}

ImageGrey eroded(const ImageGrey & image, bool use_diagonals, arma::u8 edge_value)
{
    return dilatedEroded(image, use_diagonals, edge_value, false);
}

ImageGrey boundary(const ImageGrey & image, bool use_diagonals)
{
    return arma::conv_to<ImageGrey>::from((image != eroded(image, use_diagonals)).eval()).eval();
}

ImageGrey neighbourhoodIntersection(const ImageGrey & image, const ImageGrey & neighbours, bool use_diagonals)
{
    return (image % dilated(neighbours, use_diagonals)).eval();
}

ImageGrey dilated(const ImageGrey & image, bool use_diagonals, arma::u8 edge_value)
{
    return dilatedEroded(image, use_diagonals, edge_value, true);
}

sf::IntRect regionBox(const ImageGrey & image)
{
    const auto nonzero_indices = arma::find(image).eval();
    if (nonzero_indices.size() == 0)
    {
        logError() << "Tried to get bounding box of all-zero mask";
        throw std::runtime_error("Couldn't find bounding box");
    }
    const auto nonzero_coords = arma::ind2sub(arma::size(image), nonzero_indices).eval();
    const auto nz_min = arma::min(nonzero_coords, 1).eval();
    const auto nz_max = arma::max(nonzero_coords, 1).eval();
    const auto nz_size = (nz_max - nz_min + 1).eval();
    return sf::IntRect(nz_min(1), nz_min(0), nz_size(1), nz_size(0));
}

sf::IntRect boxUnion(sf::IntRect a, sf::IntRect b)
{
    arma::imat origins = {{a.left, a.top}, {b.left, b.top}};
    arma::imat sizes = {{a.width, a.height}, {b.width, b.height}};
    auto ends = (origins + sizes - 1).eval();
    auto origin_min = arma::min(origins, 0).eval();
    auto end_max = arma::max(ends, 0).eval();
    auto size_max = (end_max - origin_min + 1).eval();
    return sf::IntRect(origin_min(0), origin_min(1),
                       size_max(0), size_max(1));
}
