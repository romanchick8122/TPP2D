#pragma once
#include "SFML/Graphics.hpp"
#include "Facade.h"
namespace graphics {
    class FanFacade : public SFMLFacade{
    public:
        class Color1 : public sf::Color {
        public:
            Color1():Color(){};
            Color1(int red, int green, int blue, int alpha = 255) : sf::Color(rand()%255, rand()%255, rand()%255){};
        };
        using Color = Color1;
    };
}