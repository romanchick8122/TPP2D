#pragma once
#include <list>
#include <GameLogic/Cell.h>
#include <GameLogic/Squad/Squad.h>
namespace util::pathfinding {
    std::list<Cell*> dijkstraPath(Cell* from, Cell* to, const Squads::Squad* squad);
}
