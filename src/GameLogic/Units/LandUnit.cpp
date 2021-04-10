#include "GameLogic/Units/LandUnit.h"

void Units::LandUnit::tick() {
    if(currentOrder != nullptr) currentOrder -> tick(this);
}

Units::LandUnit::LandUnit(float HP_, float speed_, float attack_) {
    HP = HP_;
    unitSpeed = speed_;
    attack = attack_;
    unitBorderFlagResists = Flags::generateBorderFlags();
    unitLandscapeFlagResists = Flags::generateLandscapeFlags();
}
