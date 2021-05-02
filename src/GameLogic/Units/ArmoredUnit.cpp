#include "ArmoredUnit.h"


Units::ArmoredUnit::ArmoredUnit(Units::TransportUnit *base_, const std::string &name_, float weaponWeight) :
        Unit(base_->texture, name_ + base_->name, base_->weight + weaponWeight) {
    base = base_;
}

const Units::TransportUnit *Units::ArmoredUnit::getAsTransport() {
    const Units::TransportUnit *transport = base;
    return transport;
}

float Units::ArmoredUnit::getAttack() {
    return attack;
}

void Units::ArmoredUnit::tick() {
    return;
}

void Units::ArmoredUnit::setStats(float attack_) {
    unitSpeed = (*(base->commonSpeed) * (base->weight)) / weight;
    attack = attack_;
}

void Units::ArmoredUnit::changeHP(float d) {
    base -> changeHP(d);
    if(base -> isAlive()) HP = 0;
}
