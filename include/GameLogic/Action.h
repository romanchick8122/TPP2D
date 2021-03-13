class Action;
#pragma once
#include "Squad.h"
#include "Cell.h"

class Action {
    const Squad* squad;
    float speed;
    Cell* nextCell;
    std::list<Cell*> currentPath;
    std::list<Cell*> possiblePath;
public:
    Action(Squad*);
    float calcSpeed(const Cell* start, const Cell* end);
    void findPath();
    void setPath();
    void tick();
    void render();
};
