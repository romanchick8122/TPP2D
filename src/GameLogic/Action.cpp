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
    squad->center = squad->cell->center;
    progress = 0;
    if(currentPath.empty()) {
        speed = 0;
        nextCell = nullptr;
        return;
    }
    d = (squad->center - currentPath.front()->center)/100.0f;
    //speed = calcSpeed(nextCell, currentPath.front());
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
    squad->center -= d;
    squad->shape.left -= d.x;
    squad->shape.top -= d.y;
}

void Action::render() {
    std::vector<Facade::Point> vec(currentPath.size() + 2);
    vec[0] = squad->center;
    vec[1] = nextCell->center;
    for(auto [i, it] = std::make_pair(0, currentPath.begin()); i < currentPath.size(); ++i, ++it)
        vec[i+2] = (*it) -> center;
    Facade::DrawThickLineStrip(vec, 10, Facade::Color(255,0,0));
}

void Action::setPath(Cell *end) {
    if(currentPath.empty() && progress == 0) {
        currentPath = findPath(squad->cell, end);
        return;
    }
    currentPath = findPath(squad->cell, end);
    progress = 1 - progress;
    currentPath.push_front(squad->cell);
    d = (squad->center - currentPath.front()->center)/100.0f;
    nextCell = currentPath.front();
    currentPath.pop_front();
}