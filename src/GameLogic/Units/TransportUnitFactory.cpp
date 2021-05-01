#include "TransportUnitFactory.h"

bool TransportUnitFactory::isPossible(Cell *) {
    return true;
}

TransportUnitFactory::TransportUnitFactory(nlohmann::json &unitInfo, const graphics::SFMLFacade::Texture *&texture) :
        Factory(unitInfo, texture) {
    HP = unitInfo["HP"];
    speed = unitInfo["speed"];
    armor = unitInfo["armor"];
    capacity = unitInfo["capacity"];
}

Units::Unit *TransportUnitFactory::createUnit() {
    auto *unit = new Units::TransportUnit(name, texture, weight);
    unit->setStats(HP, speed, armor, capacity);
    return unit;
}
