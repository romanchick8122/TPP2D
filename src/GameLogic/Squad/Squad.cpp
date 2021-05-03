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
    update();
    updateUnitSquadPtr();
}

Squads::Squad::~Squad() {
    if(previousClick == this) previousClick = nullptr;
    engine::gameController::Instance()->networkManager.removeShared(this);
    engine::gameController::Instance()->unregisterObject(this);
    delete action;
    for(auto unit : units) delete unit;
}

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

void Squads::Squad::update() {
    squadCurrentSpeed = 1e9;
    fullAttack = 0;
    for (auto unit : units) {
        squadCurrentSpeed = std::min(squadCurrentSpeed, *unit->commonSpeed);
        fullAttack += unit->getAttack();
    }
}

void Squads::Squad::tick() {
    action->tick();
    for (Units::Unit *unit : units) {
        unit->tick();
    }
    attack = fullAttack/1000;
}

void Squads::Squad::lateTick() {
    action->lateTick();
    return;
}

void Squads::Squad::render() {
    if (!cell->visible) {
        return;
    }
    action->render();
    Facade::DrawRect(shape, units.front()->texture);
    auto d = shape.height / units.size();
    float currentTop = shape.top;
    for(auto unit : units) {
        unit -> drawHP(engine::config::Facade::Rect({shape.left, currentTop}, {shape.width, d}));
        currentTop += d;
    }
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
    cell->addSquad(this);
    shape = Facade::Rect(center.x - 38, center.y - 21, 76, 42);
}

void Squads::Squad::doOnClick() {
    if(owner == Player::players[engine::gameController::Instance()->networkManager.serverId]) previousClick = this;
}

void Squads::Squad::setOwner(Player::Player* owner_) {
    owner = owner_;
}

void Squads::Squad::damageUnit(float& d) {
    auto unitAttack = units.front()->getAttack();
    units.front()->changeHP(-d);
    if(unitAttack != units.front()->getAttack()) fullAttack += units.front()->getAttack() - unitAttack;
    if(!units.front()->isAlive()) {
        delete units.front();
        units.pop_front();
        fullAttack -= unitAttack;
    }
}

float& Squads::Squad::getAttack() {
    return attack;
}
