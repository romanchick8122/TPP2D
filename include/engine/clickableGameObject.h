#pragma once
#include "engine/gameObject.h"
class clickableGameObject : public gameObject {
  public:
    virtual bool tryOnClick(sf::Vector2f clickPosition) = 0;
    virtual sf::FloatRect getClickEdges() = 0;
};