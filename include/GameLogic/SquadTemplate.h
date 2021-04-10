#pragma once
#include <vector>
#include "GameLogic/Units/Factory.h"
#include "engine/GUI/GuiList.h"
  class SquadTemplate : public engine::GUI::GuiList {
    std::vector<std::pair<Factory*, int>> temp;
public:
    SquadTemplate();
    bool isPossible(Cell*);
    void addFactory(Factory*, int);
    Squad* build();
};
