#pragma once
#include "SFML/Graphics.hpp"
struct renderParams {
    sf::RenderWindow* targetWindow;
    sf::Vector2f origin;
    float scale;
};