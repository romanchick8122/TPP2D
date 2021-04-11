#include "GameLogic/Squad/Squad.h"
#include "engine/config.h"
#include "graphics/Textures.h"
#include "engine/gameController.h"
#include "AllUnits.h"

using Facade = engine::config::Facade;


Squads::Squad::Squad(std::list<Units::Unit *> units_) {
    engine::gameController::Instance()->networkManager.makeShared(this);
    engine::gameController::Instance()->registerObject(this);
    action = new Action(this);
    units = units_;
    updateFlagResists();
    updateSpeed();
    updateUnitSquadPtr();
};

void Squads::Squad::updateUnitSquadPtr() {
    for (auto unit : units) unit->setSquad(this);
}

void Squads::Squad::updateFlagResists() {
    squadLandscapeFlagResists = std::vector<float>(Flags::landscapeFlags.size(), 1e9);
    squadBorderFlagResists = std::vector<float>(Flags::borderFlags.size(), 1e9);
    for (auto unit : units) {
        for (int i = 0; i < unit->landscapeFlagResists->size(); ++i) {
            squadLandscapeFlagResists[i] = std::min(squadLandscapeFlagResists[i], (*unit->landscapeFlagResists)[i]);
        }
        for (int i = 0; i < unit->borderFlagResists->size(); ++i) {
            squadBorderFlagResists[i] = std::min(squadBorderFlagResists[i], (*unit->borderFlagResists)[i]);
        }
    }
}

void Squads::Squad::updateSpeed() {
    squadCurrentSpeed = 1e9;
    for (auto unit : units) {
        squadCurrentSpeed = std::min(squadCurrentSpeed, *unit->commonSpeed);
    }
}

void Squads::Squad::tick() {
    action->tick();
    for (Units::Unit *unit : units) {
        unit->tick();
    };
};

void Squads::Squad::lateTick() { return; };

void Squads::Squad::render() {
    action->render();
    Facade::DrawRect(shape, graphics::Textures::textures[0]);
};

Facade::Rect Squads::Squad::getRenderEdges() {
    return shape;
}

bool Squads::Squad::tryOnClick(Facade::Point pos, graphics::Event::MouseButton) {
    if (!shape.contains(pos)) {
        return false;
    }
    doOnClick();
    return true;
}

void Squads::Squad::setCell(Cell *ptr) {
    cell = ptr;
    center = cell->center;
    shape = Facade::Rect(center.x - 21, center.y - 38, 76, 42);
}

void Squads::Squad::doOnClick() {
    previousClick = this;
}