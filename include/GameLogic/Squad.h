class Squad;
#pragma once
#include "GameLogic/Cell.h"
#include "Unit.h"
#include "engine/gameObject.h"

class Squad : gameObject{
    Cell* cell;
    std::pair<sf::Vector2f, sf::Vector2f> getRenderEdges() override;
    std::list<Unit*> units;
    //std::list
public:
    void tick() override;
    void lateTick() override;
    void render(const renderParams& params) override;

    Squad(Cell* ptr);
};
