#pragma once
#include "SFML/Graphics.hpp"
namespace engine {
    struct renderParams {
        sf::RenderWindow* targetWindow;
        sf::Vector2f origin;
        float scale;
    };
}