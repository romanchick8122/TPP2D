#include "Action.h"
#include "AllFlags.h"
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

void Action::findPath() {
    //todo ALGO ALGO ALGO ALGO ALGO ALGO ALGO ALGO ALGO ALGO ALGO ALGO ALGO ALGO ALGO
    //float calcSpeed(Cell* start, Cell* end);
}