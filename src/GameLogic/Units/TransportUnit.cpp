#include "TransportUnit.h"

Units::TransportUnit::TransportUnit(const std::string &name_, const graphics::SFMLFacade::Texture *&texture_,
                                    float weight_) : Unit(texture_, name_, weight_) {

}

bool Units::TransportUnit::isPossibleToAdd(Units::Unit *unit_) {
    return (capacity - loadWeight) > unit_->weight;
}

void Units::TransportUnit::addUnit(Units::Unit *unit_) {
    if (isPossibleToAdd(unit_)) units.push_back(unit_);
}

void Units::TransportUnit::deleteUnit(const Units::Unit *&unit_) {
    for (auto it = units.begin(); it != units.end(); ++it) {
        if (*it == unit_) {
            units.erase(it);
            return;
        }
    }
}

void Units::TransportUnit::setStats(float HP_, float speed_, float armor_, float capacity_) {
    HP = HP_;
    fullHP = HP_;
    unitSpeed = speed_;
    capacity = capacity_;
    armor = armor_;
}

void Units::TransportUnit::tick() {
    return;
}

float Units::TransportUnit::getAttack() {
    float allAttack = 0;
    for (auto unit : units) allAttack += unit->getAttack();
    return allAttack;
}

void Units::TransportUnit::changeHP(float d) {
    if(units.empty()) {
        HP += d;
        return;
    }
    units.front()->changeHP(d);
    if(!units.front()->isAlive()) {
        delete units.front();
        units.pop_front();
    }
}
