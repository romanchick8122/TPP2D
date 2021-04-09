#include "GameLogic/Squad.h"
#include "engine/config.h"
using Facade = engine::config::Facade;
Squad::Squad(Cell* ptr) :center(ptr->center){
    shape = Facade::Rect(center.x - 10, center.y-10, 10, 10);
    action = new Action(this);
    cell = ptr;
    Unit* u = new TestUnit1(1);
    units.push_back(u);
    updateFlagResists();
    updateSpeed();
    updateUnitSquadPtr();
}

Squad::Squad(Cell *cell_, std::list<Unit *> units_) {
    shape = Facade::Rect(center.x - 16, center.y-16, 16, 16);
    action = new Action(this);
    cell = cell_;
    units = units_;
    updateFlagResists();
    updateSpeed();
    updateUnitSquadPtr();
};

void Squad::updateUnitSquadPtr() {
    for(auto unit : units) unit->setSquad(this);
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
    action->tick();
    for(Unit* unit : units) {
        unit -> tick();
    };
};
void Squad::lateTick(){return;};

void Squad::render(){
    action->render();
    Facade::DrawRect(shape, Facade::Color(255, 255, 0));
    return;
};
Facade::Rect Squad::getRenderEdges(){
    return shape;
}

bool Squad::tryOnClick(Facade::Point pos) {
    return false;
}
Facade::Rect Squad::getClickEdges() {
    return shape;
}

void Squad::setCell(Cell *ptr) {
    cell = ptr;
}
