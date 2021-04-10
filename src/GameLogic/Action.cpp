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
    squad->cell = currentPath.front();
    progress = 0;
    currentPath.pop_front();
    if (currentPath.empty()) return;
    d = (squad->center - currentPath.front()->center)/100.0f;
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
    if(currentPath.empty()) return;
    std::vector<Facade::Point> vec(currentPath.size() + 1);
    vec[0] = squad->center;
    for(auto [i, it] = std::make_pair(0, currentPath.begin()); i < currentPath.size(); ++i, ++it)
        vec[i+1] = (*it) -> center;
    Facade::DrawThickLineStrip(vec, 10, Facade::Color(255,0,0));
}

void Action::setPath(Cell *end) {
    if(currentPath.empty() && progress == 0) {
        currentPath = findPath(squad->cell, end);
        currentPath.push_front(squad->cell);
        nextStep();
        return;
    }
    possiblePath = findPath(squad->cell, end);
    if(currentPath.front() != possiblePath.front()){
        progress = 1 - progress;
        possiblePath.push_front(squad->cell);
        d = (squad->center - possiblePath.front()->center)/100.0f;
    }
    currentPath = possiblePath;
}