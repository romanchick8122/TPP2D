#include "GameLogic/Units/Factory.h"

Factory::Factory(nlohmann::json &unitInfo, const engine::config::Facade::Texture *&texture_) :
        name(unitInfo["name"]), cost(unitInfo["cost"]), texture(texture_), weight(unitInfo["weight"]) {
    engine::gameController::Instance()->networkManager.makeShared(this);
}

Factory::Factory(nlohmann::json &unitInfo, const engine::config::Facade::Texture *&texture_, Factory *otherFactory) :
        name(std::string(unitInfo["addName"]) + otherFactory->name),
        cost(otherFactory->cost + float(unitInfo["addCost"])),
        texture(texture_), weight(float(unitInfo["addWeight"]) + otherFactory->cost) {
    engine::gameController::Instance()->networkManager.makeShared(this);
}

void Factory::render() {return;}

void Factory::tick() {return;}

void Factory::lateTick() {return;}

engine::config::Facade::Rect Factory::getRenderEdges() {
    return graphics::SFMLFacade::Rect();
}

bool Factory::tryOnClick(engine::config::Facade::Point clickPosition, graphics::Event::MouseButton) {
    return false;
}

std::string Factory::repr() {
    return "Factory - " + name;
}