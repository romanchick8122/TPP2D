#include "GameLogic/Squad.h"
#include "engine/config.h"
using Facade = engine::config::Facade;
Squad::Squad(Cell* ptr) {
    action = new Action(this);
    cell = ptr;
    Unit* u = new TestUnit(this);
    units.push_back(u);
    updateFlagResists();
    updateSpeed();
}

void Squad::updateFlagResists() {
    squadLandscapeFlagResists = std::vector<float>(Flags::landscapeFlags.size(),1e9);
    squadBorderFlagResists = std::vector<float>(Flags::borderFlags.size(),1e9);
    for(auto unit : units) {
        for(int i = 0; i < unit->landscapeFlagResists->size(); ++i) {
            squadLandscapeFlagResists[i] = std::min(squadLandscapeFlagResists[i], (*unit->landscapeFlagResists)[i]);
        }
        for(int i = 0; i < unit->borderFlagResists->size(); ++i) {
            squadBorderFlagResists[i] = std::min(squadBorderFlagResists[i], (*unit->borderFlagResists)[i]);
        }
    }
}

void Squad::updateSpeed() {
    squadCurrentSpeed = 1e9;
    for(auto unit : units) {
        squadCurrentSpeed = std::min(squadCurrentSpeed, *unit->commonSpeed);
    }
}

void Squad::tick(){
    for(Unit* unit : units) {
        unit -> tick();
    };
};
void Squad::lateTick(){return;};
void Squad::render(){return;};
Facade::Rect Squad::getRenderEdges(){
    return Facade::Rect();
};