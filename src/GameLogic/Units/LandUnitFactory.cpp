#include "LandUnitFactory.h"

bool LandUnitFactory::isPossible(Cell *) {
    return true;
}

Units::Unit *LandUnitFactory::createUnit() {
    auto *unit = new Units::LandUnit(name, texture, weight);
    unit->setStats(HP, speed, attack);
    return unit;
}

LandUnitFactory::LandUnitFactory(nlohmann::json &unitInfo, const engine::config::Facade::Texture *&texture_) :
        Factory(unitInfo, texture_) {
    HP = unitInfo["HP"];
    speed = unitInfo["speed"];
    attack = unitInfo["attack"];
}
