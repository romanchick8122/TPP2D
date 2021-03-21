class Action;
#pragma once
#include "Squad.h"
#include "Cell.h"

class Action {
    float progress;
    Squad* squad;
    float speed;
    Facade::Point d;
    float dx;
    float dy;
    Cell* nextCell;
    std::list<Cell*> currentPath;
    std::list<Cell*> possiblePath;
public:
    Action(Squad*);
    void nextStep();
    float calcSpeed(const Cell* start, const Cell* end);
    std::list<Cell*> findPath(Cell*, Cell*);
    void setPath();
    void setPath(Cell*);
    void tick();
    void render();
};
