#include "LandUnit.h"

void Units::LandUnit::tick() {
    if (currentOrder != nullptr) currentOrder->tick(this);
}

Units::LandUnit::LandUnit(const std::string &name_, const graphics::SFMLFacade::Texture *&texture_, float weight_) :
        Unit(texture_, name_, weight_) {
    currentOrder = nullptr;
}

void Units::LandUnit::setStats(float HP_, float speed_, float attack_) {
    HP = HP_;
    fullHP = HP_;
    unitSpeed = speed_;
    attack = attack_;
    unitBorderFlagResists = Flags::generateBorderFlags();
    unitLandscapeFlagResists = Flags::generateLandscapeFlags();
}

float Units::LandUnit::getAttack() {
    return attack;
}

void Units::LandUnit::changeHP(float d) {
    HP += d;
}
