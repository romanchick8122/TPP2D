#include "GameLogic/Units/Factory.h"
class LandUnitFactory: public Factory {
    float HP, speed, attack;
    //const std::string name;
public:
    explicit LandUnitFactory(const std::string& name_, float cost, float HP_, float speed_, float attack_);
    bool isPossible(Cell*) override;
    Units::Unit* createUnit() override;
};