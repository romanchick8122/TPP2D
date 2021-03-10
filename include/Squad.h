#pragma once
#include "Cell.h"

class Squad : GameObject{
    Player* owner;
    Cell* cell;
    std::list<Unit> units;

};
