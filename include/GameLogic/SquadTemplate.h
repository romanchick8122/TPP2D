#pragma once
#include <vector>
#include "GameLogic/Units/Factory.h"
class SquadTemplate {
    std::vector<std::pair<Factory*, int>> temp;
public:
    SquadTemplate();
    bool isPossible(Cell*);
    void addFactory(Factory*, int);
    Squad* build();
    //todo void render();
};
