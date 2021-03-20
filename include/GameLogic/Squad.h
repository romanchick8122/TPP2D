class Squad;
#pragma once
#include "GameLogic/Cell.h"
#include "Unit.h"
#include "engine/gameObject.h"
#include "Action.h"
#include "engine/config.h"

class Squad : engine::gameObject{
    Cell* cell;
    engine::config::Facade::Rect getRenderEdges() override;
    std::list<Unit*> units;
    void updateUnitSquadPtr();
    void updateSpeed();
    float squadCurrentSpeed;
    void updateFlagResists();
    std::vector<float> squadLandscapeFlagResists;
    std::vector<float> squadBorderFlagResists;
public:
    Squad(Cell*, std::list<Unit*>);
    const float* currentSpeed = &squadCurrentSpeed;
    const std::vector<float>* landscapeFlagResists = &squadLandscapeFlagResists;
    const std::vector<float>* borderFlagResists = &squadBorderFlagResists;
    Action* action;
    Squad(Cell* ptr);

    void tick() override;
    void lateTick() override;
    void render() override;

};
