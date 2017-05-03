#pragma once

#include <spotify/json.hpp>

#include <SFML/System/Vector2.hpp>

namespace spotify
{
namespace json
{

// Tried to write this as
// template<typename U> struct default_codec_t<sf::Vector2<U>>,
// but it doesn't seem to be compatible with typedefs like sf::Vector2u.
template<>
struct default_codec_t<sf::Vector2u>
{
    static auto codec()
    {
        auto codec = codec::transform(
            codec::pair(codec::number<unsigned int>(), codec::number<unsigned int>()),
            [](sf::Vector2u v) {return std::pair<unsigned int, unsigned int>(v.x, v.y); },
            [](std::pair<unsigned int, unsigned int> p) {return sf::Vector2u(p.first, p.second); }
        );
        return codec;
    }
};

}
}
