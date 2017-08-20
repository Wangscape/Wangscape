#pragma once

#include <spotify/json.hpp>

#include <SFML/Graphics/Rect.hpp>

namespace spotify
{
namespace json
{

// See Vector2Codec.h for issues with making this generic.
template<>
struct default_codec_t<sf::Rect<double>>
{
    typedef std::pair<double, double> DoublePair;
    typedef std::pair<DoublePair, DoublePair> DoublePairPair;
    static auto codec()
    {
        auto codec = codec::transform(
            codec::pair(codec::pair(codec::number<double>(), codec::number<double>()),
                        codec::pair(codec::number<double>(), codec::number<double>())),
            [](sf::Rect<double> v)
        {return DoublePairPair{{v.left, v.top}, {v.width, v.height}}; },
            [](DoublePairPair p)
        {return sf::Rect<double>(p.first.first, p.first.second, p.second.first, p.second.second); }
        );
        return codec;
    }
};

}
}
