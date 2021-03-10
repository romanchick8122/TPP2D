#pragma once
#include "SFML/Graphics.hpp"
struct renderParams {
    sf::RenderWindow targetWindow;
    sf::Vector2f coordShift;
};
class gameObject {
  public:
    virtual void tick() = 0;
    virtual void lateTick() = 0;
    virtual void render(const renderParams& params) = 0;
};