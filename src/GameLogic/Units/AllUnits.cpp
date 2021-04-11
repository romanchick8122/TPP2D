#include "GameLogic/Units/AllUnits.h"
#include "LandUnitFactory.h"
#include "TransportUnitFactory.h"
#include "ArmoredUnitFactory.h"
#include "graphics/Textures.h"

namespace Units {
    std::vector<Factory*> allUnits;
    void setUnits() {
        for (nlohmann::json& unitInfo : engine::config::runtime["GameLogic"]["AllUnits"]["LandUnit"]) {
            const engine::config::Facade::Texture* texture = graphics::Textures::textures[graphics::Textures::nameMapping[unitInfo["texture"]]];
            allUnits.push_back(new LandUnitFactory(unitInfo, texture));
        }
        for (nlohmann::json& unitInfo : engine::config::runtime["GameLogic"]["AllUnits"]["TransportUnit"]) {
            const engine::config::Facade::Texture* texture = graphics::Textures::textures[graphics::Textures::nameMapping[unitInfo["texture"]]];
            allUnits.push_back(new TransportUnitFactory(unitInfo, texture));
        }
        std::vector<TransportUnitFactory*> bases;
        for (nlohmann::json& unitInfo : engine::config::runtime["GameLogic"]["AllUnits"]["ArmoredUnit"]["Bases"]) {
            const engine::config::Facade::Texture* texture = graphics::Textures::textures[graphics::Textures::nameMapping[unitInfo["texture"]]];
            bases.push_back(new TransportUnitFactory(unitInfo, texture));
        }
        for(auto i : bases)
            for(nlohmann::json& unitInfo : engine::config::runtime["GameLogic"]["AllUnits"]["ArmoredUnit"]["Weapons"]) {
                allUnits.push_back(new ArmoredUnitFactory(unitInfo, i->texture, i));
            }
    }
}