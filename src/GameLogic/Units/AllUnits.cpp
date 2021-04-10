#include "GameLogic/Units/AllUnits.h"
#include "LandUnit.h"
namespace Units {
    extern std::vector<Factory*> AllUnits;
    void setUnits() {
        for (auto& unitInfo : engine::config::runtime["GameLogic"]["AllUnits"]["LandUnit"]) {
            Unit* unit = new LandUnit(unitInfo[name]);
            land->name = unit["name"];
            land->speedInfluence = lo["speedInfluence"];
            land->randParameter = lo["randParameter"];
            landscapeFlags.push_back(std::unique_ptr<Flag>(land));
        }
    }
}