#include "Image.h"
#include <vector>
#include <set>
#include <queue>
#include "Vector.h"

#include "logging/Logging.h"

namespace
{
const static std::vector<IVec> ORTHOGONAL_STEPS{
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const static std::vector<IVec> ORTHODIAGONAL_STEPS{
    {0, 1}, {1, 0}, {0, -1}, {-1, 0},
    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

ImageGrey dilatedEroded(const ImageGrey & image, bool use_diagonals, arma::u8 edge_value, bool dilate)
{
    const auto& steps = use_diagonals ? ORTHODIAGONAL_STEPS : ORTHOGONAL_STEPS;
    const auto n_steps = steps.size();
    ImageStackGrey displacements(image.n_rows, image.n_cols, n_steps + 1);
    displacements.fill(edge_value);
    displacements.slice(0) = image;
    for (unsigned int s = 0; s < n_steps; s++)
    {
        copyRegionBounded(image, displacements.slice(s + 1),
        {IVec(0, 0), steps[s], IVec(makeUVec(arma::size(image)))});
    }
    if (dilate)
        return arma::max(displacements, 2).eval();
    else
        return arma::min(displacements, 2).eval();
}

} // anonymous namespace

ImageColour imageFromSFImage(const sf::Image & sf_image)
{
    UVec shape = makeVector(sf_image.getSize());
    ImageColour image(shape.y(), shape.x(), 4);
    for(size_t y = 0; y < shape.y(); y++)
        for (size_t x = 0; x < shape.x(); x++)
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
    UVec shape = makeVector(sf_image.getSize());
    for (size_t y = 0; y < shape.y(); y++)
        for (size_t x = 0; x < shape.x(); x++)
        {
            const auto pixel = image.tube(y, x);
            sf_image.setPixel(x, y, sf::Color(pixel(0), pixel(1), pixel(2), pixel(3)));
        }
    return sf_image;
}

void copyRegionBounded(const ImageGrey& source, ImageGrey & target, CopyRegionParameters parameters)
{
    const auto source_shape = makeUVec(arma::size(source));
    const auto target_shape = makeUVec(arma::size(target));
    copyRegion(source, target, parameters.trim(source_shape, target_shape));
}

void copyRegion(const ImageGrey& source, ImageGrey & target, CopyRegionParameters parameters)
{
    const auto source_end = parameters.sourceOrigin + parameters.size;
    const auto target_end = parameters.targetOrigin + parameters.size;
    target.submat(arma::span(parameters.targetOrigin.y(), target_end.y() - 1),
                  arma::span(parameters.targetOrigin.x(), target_end.x() - 1)) =
        source.submat(arma::span(parameters.sourceOrigin.y(), source_end.y() - 1),
                      arma::span(parameters.sourceOrigin.x(), source_end.x() - 1));
}

bool isConnected(const ImageGrey & image, bool use_diagonals)
{
    const unsigned int n_ones = arma::nonzeros(image).eval().size();
    if (n_ones == 0)
        return false;
    const auto start_index = image.index_max();
    const auto start = arma::ind2sub(size(image), start_index);
    std::set<IVec> component;
    std::set<IVec> border;
    border.insert(IVec(start(1), start(0)));
    const auto& steps = use_diagonals ? ORTHODIAGONAL_STEPS : ORTHOGONAL_STEPS;
    const auto shape = makeUVec(arma::size(image));
    const auto in_bounds = [&shape](IVec point)
    {
        if (point.x() < 0 || point.y() < 0)
            return false;
        if ((unsigned int)point.x() >= shape.x() || (unsigned int)point.y() >= shape.y())
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
            if (image(new_point.y(), new_point.x()))
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
    {IVec(0, 0), IVec(1, 1),  makeIVec(arma::size(image))});
    return result;
}

ImageGrey unpadded(const ImageGrey & image)
{
    return image.submat(arma::span(1, image.n_rows - 2),
                        arma::span(1, image.n_cols - 2));
}

ImageStackGrey unpaddedStack(const ImageStackGrey & image_stack)
{
    return image_stack.subcube(arma::span(1, image_stack.n_rows - 2),
                               arma::span(1, image_stack.n_cols - 2),
                               arma::span::all);
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
        const std::string s = "Tried to get bounding box of all-zero mask";
        logError() << s;
        throw std::runtime_error(s);
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

ImageGrey32 distances(const ImageGrey & traversable, const ImageGrey & targets, bool use_diagonals)
{
    if (!isBinary(traversable))
    {
        const std::string s = "distances() requires binary traversable mask";
        logError() << s;
        throw std::runtime_error(s);
    }
    if (!isBinary(targets))
    {
        const std::string s = "distances() requires binary targets mask";
        logError() << s;
        throw std::runtime_error(s);
    }
    if(!isNonzero(traversable))
    {
        const std::string s = "distances() requires nonzero traversable mask";
        logError() << s;
        throw std::runtime_error(s);
    }
    if (!isNonzero(targets))
    {
        const std::string s = "distances() requires nonzero targets mask";
        logError() << s;
        throw std::runtime_error(s);
    }
    if(!isConnected(traversable))
    {
        const std::string s = "distances() requires connected traversable mask";
        logError() << s;
        throw std::runtime_error(s);
    }

    ImageGrey32 distance_field(arma::size(traversable));
    const arma::u32 infinity = std::numeric_limits<arma::u32>::max();
    distance_field.fill(infinity);

    const auto target_coordinates = arma::ind2sub(arma::size(targets), arma::find(targets)).eval();

    std::queue<IVec> border;
    const auto& steps = use_diagonals ? ORTHODIAGONAL_STEPS : ORTHOGONAL_STEPS;

    const auto shape = makeUVec(arma::size(traversable));

    const auto in_bounds = [&shape](IVec point)
    {
        if (point.x() < 0 || point.y() < 0)
            return false;
        if ((unsigned int)point.x() >= shape.x() || (unsigned int)point.y() >= shape.y())
            return false;
        return true;
    };

    for (unsigned int i = 0; i < target_coordinates.n_cols; i++)
    {
        IVec target{int(target_coordinates(1, i)), int(target_coordinates(0, i))};
        distance_field(target.y(), target.x()) = 0;
        border.push(target);
    }

    while (!border.empty())
    {
        IVec point = border.front();
        border.pop();
        arma::u32 distance = distance_field(point.y(), point.x()) + 1;
        for (const auto step : steps)
        {
            IVec new_point = point + step;
            if (!in_bounds(new_point))
                continue;
            if (!traversable(new_point.y(), new_point.x()))
                continue;
            if (distance_field(new_point.y(), new_point.x()) == infinity)
            {
                border.push(new_point);
                distance_field(new_point.y(), new_point.x()) = distance;
            }
        }
    }
    return distance_field;
}

ImageStackGrey tessellated(const ImageGrey & image, const std::vector<IVec>& offsets)
{
    const auto image_padded = padded(image);
    ImageStackGrey tessellation(image_padded.n_rows, image_padded.n_cols, offsets.size(), arma::fill::zeros);
    for (size_t i = 0; i < offsets.size(); i++)
    {
        copyRegionBounded(
            image_padded, tessellation.slice(i),
            {IVec(0, 0), offsets[i], makeUVec(arma::size(image_padded))});
    }
    return tessellation;
}
