#include "Action.h"
#include "AllFlags.h"
#include "util/pathfinding.h"
Action::Action(Squad* ptr) : squad(ptr){}

float Action::calcSpeed(const Cell *start, const Cell *end) {
    float finalSpeed = *(squad -> currentSpeed);
    for(int i = 0; i < Flags::landscapeFlags.size(); ++i) {
        std::vector<float> vec = *end->landscapeFlags;
        finalSpeed /= ((*start->landscapeFlags)[i] + (*end->landscapeFlags)[i] - (*squad->landscapeFlagResists)[i])
                * Flags::landscapeFlags[i]->speedInfluence;
    }
    for(int i = 0; i < Flags::borderFlags.size(); ++i) {
        finalSpeed /= (((*end->bordersFlags).find(start)->second)[i] - (*squad->borderFlagResists)[i])
                      * Flags::borderFlags[i]->speedInfluence;
    }
    return abs(finalSpeed);
}

void Action::setPath() {
    currentPath = possiblePath;
}

std::list<Cell*> Action::findPath(Cell* start, Cell* end) {
    return util::pathfinding::dijkstraPath(start, end, squad);
}

void Action::nextStep() {
    squad->cell = nextCell;
    progress = 0;
    if(currentPath.empty()) {
        speed = 0;
        nextCell = nullptr;
        squad->center = squad->cell->center;
        return;
    }
    speed = calcSpeed(nextCell, currentPath.front());
    nextCell = currentPath.front();
    currentPath.pop_front();
}

void Action::tick() {
    if(currentPath.empty()) return;
    progress += 0.01;
    if(progress >= 1) {
        nextStep();
        return;
    }
    squad->center.x += dx;
    squad->center.y += dy;
}

void Action::render() {

}

void Action::setPath(Cell *end) {
    currentPath = findPath(squad->cell, end);
}
