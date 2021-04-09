class Squad;
#pragma once
#include "GameLogic/Cell.h"
#include "Unit.h"
#include "engine/gameObject.h"
#include "Action.h"
#include "engine/config.h"

class Squad : public engine::gameObject{
    engine::config::Facade::Point center = {100, 100};
    Facade::Rect shape;
    Cell* cell;
    engine::config::Facade::Rect getRenderEdges() override;
    engine::config::Facade::Rect getClickEdges() override;
    std::list<Unit*> units;
    void updateUnitSquadPtr();
    void updateSpeed();
    float squadCurrentSpeed;
    void updateFlagResists();
    std::vector<float> squadLandscapeFlagResists;
    std::vector<float> squadBorderFlagResists;
public:
    void setCell(Cell*);
    friend Action;
    Squad(Cell*, std::list<Unit*>);
    const float* currentSpeed = &squadCurrentSpeed;
    const std::vector<float>* landscapeFlagResists = &squadLandscapeFlagResists;
    const std::vector<float>* borderFlagResists = &squadBorderFlagResists;
    Action* action;
    Squad(Cell* ptr);
    void tick() override;
    void lateTick() override;
    void render() override;
    std::unique_ptr<engine::Action> tryOnClick(Facade::Point pos) override;
};
