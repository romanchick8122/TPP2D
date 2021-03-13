#pragma once
#include <list>
#include <GameLogic/Cell.h>
#include <GameLogic/Squad.h>
namespace util::pathfinding {
    std::list<const Cell*> dijkstraPath(const Cell* from, const Cell* to, const Squad* squad);
}
