#pragma once
#include "GameLogic/Units/Factory.h"
#include "LandUnit.h"
class LandUnitFactory: public Factory {
    float HP, speed, attack;
public:
    explicit LandUnitFactory(nlohmann::json&, const engine::config::Facade::Texture*&);
    bool isPossible(Cell*) override;
    Units::Unit* createUnit() override;
};