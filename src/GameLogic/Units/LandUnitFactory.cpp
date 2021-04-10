#include "GameLogic/Units/LandUnitFactory.h"
#include "GameLogic/Units/LandUnit.h"

LandUnitFactory::LandUnitFactory(std::string& name_, float cost_, float HP_, float speed_, float attack_): Factory(name_, cost_) {
    HP = HP_;
    speed = speed_;
    attack = attack_;
}

bool LandUnitFactory::isPossible(Cell *) {
    return true;
}

Units::Unit *LandUnitFactory::createUnit() {
    return new Units::LandUnit(HP, speed, attack);
}
