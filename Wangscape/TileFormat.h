#pragma once

#include <string>
#include <SFML/System/Vector2.hpp>

struct TileFormat
{
    sf::Vector2u resolution;
    std::string fileType = "png";
};
