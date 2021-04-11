#include "LandUnit.h"

void Units::LandUnit::tick() {
    if(currentOrder != nullptr) currentOrder -> tick(this);
}

Units::LandUnit::LandUnit(const std::string &name_, const graphics::SFMLFacade::Texture *&texture_) : Unit(texture_, name_) {
    currentOrder = nullptr;
}

void Units::LandUnit::setStats(float HP_, float speed_, float attack_) {
    HP = HP_;
    unitSpeed = speed_;
    attack = attack_;
    unitBorderFlagResists = Flags::generateBorderFlags();
    unitLandscapeFlagResists = Flags::generateLandscapeFlags();
}
