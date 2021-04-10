#include "GameLogic/Units/AllUnits.h"
#include "LandUnitFactory.h"
namespace Units {
    std::vector<Factory*> AllUnits;
    void setUnits() {
        for (auto& unitInfo : engine::config::runtime["GameLogic"]["AllUnits"]["LandUnit"]) {
            AllUnits.push_back(new LandUnitFactory(unitInfo["name"], unitInfo["cost"], unitInfo["HP"], unitInfo["speed"], unitInfo["attack"]));
        }
    }
}