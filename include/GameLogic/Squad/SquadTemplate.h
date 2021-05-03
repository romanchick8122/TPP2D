namespace Squads {
    class SquadTemplate;
}
#pragma once
#include <vector>
#include "GameLogic/Units/Factory.h"
#include "engine/GUI/GuiList.h"
#include "engine/GUI/GuiScroll.h"
#include "engine/GUI/Button.h"
#include "GameLogic/Player.h"
namespace Squads {
    class SquadTemplate {
        std::list<std::pair<std::pair<Factory*, int>, std::pair<engine::GUI::GuiObject*, engine::GUI::Button*>>> temp;
        std::unique_ptr<engine::GUI::GuiList> list;
        engine::GUI::GuiScroll* scrollObj;
        std::unique_ptr<engine::GUI::GuiScroll> factoriesAvailable;
        std::string name;
        engine::GUI::GuiObject* getAvailableFactoryObject(Factory* factory);
        std::pair<engine::GUI::GuiObject*, engine::GUI::Button*> getFactoryListObject(Factory* factory, int count);
      public:
        SquadTemplate();
        bool isPossible(Cell*);
        void addFactory(Factory*, int);
        void removeFactory(Factory*);
        void build(Cell*, Player::Player*);
        void show();
        void hide();
    };
}