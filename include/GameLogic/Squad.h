class Squad;
#pragma once
#include "GameLogic/Cell.h"
#include "Unit.h"
#include "engine/gameObject.h"
#include "Action.h"

class Squad : engine::gameObject{
    Cell* cell;
    sf::FloatRect getRenderEdges() override;
    std::list<Unit*> units;
    void updateSpeed();
    float squadCurrentSpeed;
    void updateFlagResists();
    std::vector<float> squadLandscapeFlagResists;
    std::vector<float> squadBorderFlagResists;
public:
    const float* currentSpeed = &squadCurrentSpeed;
    const std::vector<float>* landscapeFlagResists = &squadLandscapeFlagResists;
    const std::vector<float>* borderFlagResists = &squadBorderFlagResists;
    Action* action;
    Squad(Cell* ptr);

    float moveTime(const Cell* from, const Cell* to) const;

    void tick() override;
    void lateTick() override;
    void render(const engine::renderParams& params) override;

};
