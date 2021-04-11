#pragma once

#include "Factory.h"
#include "TransportUnit.h"

class TransportUnitFactory : public Factory {
    float HP, speed, capacity, armor;
public:
    explicit TransportUnitFactory(nlohmann::json &, const engine::config::Facade::Texture *&);

    bool isPossible(Cell *) override;

    Units::Unit *createUnit() override;
};
