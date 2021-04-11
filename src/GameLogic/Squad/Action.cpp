#include "Action.h"
#include "AllFlags.h"
#include "util/pathfinding.h"
Squads::Action::Action(Squads::Squad* ptr) : squad(ptr){}

float Squads::Action::calcSpeed(const Cell *start, const Cell *end) {
    float finalSpeed = *(squad -> currentSpeed);
    return abs(finalSpeed);
    for(int i = 0; i < Flags::landscapeFlags.size(); ++i) {
        std::vector<float> vec = *end->landscapeFlags;
        finalSpeed /= ((*start->landscapeFlags)[i] + (*end->landscapeFlags)[i] - (*squad->landscapeFlagResists)[i])
                * Flags::landscapeFlags[i]->speedInfluence;
    }
    for(int i = 0; i < Flags::borderFlags.size(); ++i) {
        finalSpeed /= (((*end->bordersFlags).find(start)->second)[i] - (*squad->borderFlagResists)[i])
                      * Flags::borderFlags[i]->speedInfluence;
    }
}

void Squads::Action::setPath() {
    currentPath = possiblePath;
}

std::list<Cell*> Squads::Action::findPath(Cell* start, Cell* end) {
    return util::pathfinding::dijkstraPath(start, end, squad);
}

void Squads::Action::nextStep() {
    squad->cell = currentPath.front();
    currentPath.pop_front();
    progress = 0;
    if (currentPath.empty()) return;
    speed = calcSpeed(squad->cell, currentPath.front());
    auto way = currentPath.front()->center - squad->center;
    float wayAbs = pow(way.x*way.x+way.y*way.y, 0.5);
    endProgress = (wayAbs/speed) *10.0f;
    way.x/=wayAbs;
    way.y/=wayAbs;
    d = way*speed/10.0f;
}

void Squads::Action::tick() {
    if(currentPath.empty()) return;
    progress += 1;
    if(progress >= endProgress) {
        nextStep();
        return;
    }
    squad->center += d;
    squad->shape.left += d.x;
    squad->shape.top += d.y;
}

void Squads::Action::render() {
    if(currentPath.empty()) return;
    std::vector<Facade::Point> vec(currentPath.size() + 1);
    vec[0] = squad->center;
    for(auto [i, it] = std::make_pair(0, currentPath.begin()); i < currentPath.size(); ++i, ++it)
        vec[i+1] = (*it) -> center;
    Facade::DrawThickLineStrip(vec, 10, Facade::Color(255,0,0));
}

void Squads::Action::setPath(Cell *end) {
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
        d = -d;
    }
    currentPath = possiblePath;
}