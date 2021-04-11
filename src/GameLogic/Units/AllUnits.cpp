#include "GameLogic/Units/AllUnits.h"
#include "LandUnitFactory.h"
#include "graphics/Textures.h"

namespace Units {
    std::vector<Factory*> allUnits;
    void setUnits() {
        for (nlohmann::json& unitInfo : engine::config::runtime["GameLogic"]["AllUnits"]["LandUnit"]) {
            const engine::config::Facade::Texture* texture = graphics::Textures::textures[graphics::Textures::nameMapping[unitInfo["texture"]]];
            allUnits.push_back(new LandUnitFactory(unitInfo, texture));
        }
    }
}