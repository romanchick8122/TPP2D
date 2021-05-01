#include "UnitOrder.h"
#include "Unit.h"

class SquadOrder {
    std::list<std::pair<Unit*, int>> orders;
    bool isEnable = false;
public:
    bool isPossible();
    void enable();
    void disable();
};
