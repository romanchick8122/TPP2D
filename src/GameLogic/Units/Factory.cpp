#include "GameLogic/Units/Factory.h"

Factory::Factory(nlohmann::json &unitInfo, const engine::config::Facade::Texture *&texture_) :
        name(unitInfo["name"]), cost(unitInfo["cost"]), texture(texture_), weight(unitInfo["weight"]) {}

Factory::Factory(nlohmann::json &unitInfo, const engine::config::Facade::Texture *&texture_, Factory *otherFactory) :
        name(std::string(unitInfo["addName"]) + otherFactory->name),
        cost(otherFactory->cost + float(unitInfo["addCost"])),
        texture(texture_), weight(float(unitInfo["addWeight"]) + otherFactory->cost) {

}
