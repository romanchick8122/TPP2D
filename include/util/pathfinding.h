#pragma once
#include <list>
#include <GameLogic/Cell.h>
#include <GameLogic/Squad.h>
namespace util::pathfinding {
    std::list<Cell*> dijkstraPath(Cell* from, Cell* to, const Squad* squad);
}
