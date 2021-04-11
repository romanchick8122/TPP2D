namespace Squads {
    class SquadTemplate;
}
#pragma once
#include <vector>
#include "GameLogic/Units/Factory.h"
#include "engine/GUI/GuiList.h"
namespace Squads {
    class SquadTemplate {
        std::vector<std::pair<Factory *, int>> temp;
        std::unique_ptr<engine::GUI::GuiList> list;
    public:
        SquadTemplate();
        bool isPossible(Cell *);
        void addFactory(Factory *, int);
        Squad *build();
    };
}