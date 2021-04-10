#include "GameLogic/Units/UnitOrder.h"
#include "GameLogic/Units/Unit.h"

class SquadOrder {
    std::list<std::pair<Units::Unit*, int>> orders;
    bool isEnable = false;
public:
    bool isPossible();
    void enable();
    void disable();
};
