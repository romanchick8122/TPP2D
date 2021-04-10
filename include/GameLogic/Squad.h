class Squad;
#pragma once
#include "GameLogic/Cell.h"
#include "Unit.h"
#include "engine/gameplayClickableGameObject.h"
#include "Action.h"
#include "engine/config.h"
#include "graphics/Facade.h"

class Squad : public engine::gameplayClickableGameObject{
    int x = 255,y= 255,z=0;
    engine::config::Facade::Point center = {100, 100};
    Facade::Rect shape;
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
    bool tryOnClick(Facade::Point pos, graphics::Event::MouseButton) override;
    void doOnClick() override;
};
