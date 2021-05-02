#include "GameLogic/Squad/SquadTemplate.h"
#include <memory>
#include "engine/GUI/Button.h"
#include "GameLogic/Units/AllUnits.h"
#include "engine/GUI/GuiStrip.h"
#include "engine/GUI/GuiScroll.h"
#include "engine/actions/SpawnAction.h"
engine::GUI::GuiObject* Squads::SquadTemplate::getAvailableFactoryObject(Factory* factory) {
    auto strip = new engine::GUI::GuiStrip(390, engine::config::Facade::Color(30, 20, 4));
    strip->addChild(std::make_unique<engine::GUI::Button>(
        engine::config::Facade::Rect({0, 0}, {390, 90}),
        [this, factory](engine::GUI::Button* caller) {
            addFactory(factory, 1);
        },
        factory->texture,
        factory->name,
        engine::config::Facade::Color(255, 255, 255)
    ));
    return strip;
}
std::pair<engine::GUI::GuiObject*, engine::GUI::Button*> Squads::SquadTemplate::getFactoryListObject(
        Factory* factory, int count) {
    auto factoryObj = new engine::GUI::GuiStrip(
        390,
        engine::config::Facade::Color(0, 0, 0));
    //texture + count
    auto countButton = new engine::GUI::Button(
        engine::config::Facade::Rect({0, 0}, {76, 42}),
        [this, factory](engine::GUI::Button*) {
            removeFactory(factory);
        },
        factory->texture,
        std::to_string(count),
        engine::config::Facade::Color(255, 255, 255)
    );
    factoryObj->addChild(std::unique_ptr<engine::GUI::GuiObject>(countButton));
    //name
    factoryObj->addChild(std::make_unique<engine::GUI::Button>(
        engine::config::Facade::Rect({0, 0}, {390 - 76 - 15, 42}),
        [](engine::GUI::Button*) {},
        engine::config::Facade::Color(0, 0, 0, 0),
        factory->name,
        engine::config::Facade::Color(255, 255, 255)
    ));
    return {factoryObj, countButton};
}
Squads::SquadTemplate::SquadTemplate() : list(new engine::GUI::GuiList(engine::config::Facade::Color(60, 40, 8))) {
    auto topMenuStrip = std::make_unique<engine::GUI::GuiStrip>(400, engine::config::Facade::Color(0,0,0,0));
    //name
    topMenuStrip->addChild(std::make_unique<engine::GUI::Button>(
        engine::config::Facade::Rect({0, 0}, {355, 30}),
        [](engine::GUI::Button*){},
        engine::config::Facade::Color(0, 0, 0, 0),
        name,
        engine::config::Facade::Color(255, 220, 220)));
    //close button
    topMenuStrip->addChild(std::make_unique<engine::GUI::Button>(
        engine::config::Facade::Rect({0, 0}, {30, 30}),
        [this](engine::GUI::Button*){ hide(); },
        engine::config::Facade::Color(255, 0, 0)
        ));
    list->addChild(std::move(topMenuStrip));

    //Selected factories
    auto mainPanel = std::make_unique<engine::GUI::GuiScroll>(engine::config::Facade::Rect(
        {0, 0}, {400, 1075 - list->boundary.height}),
                                                              engine::config::Facade::Color(30, 20, 4));
    scrollObj = mainPanel.get();

    //Factories scroll
    factoriesAvailable = std::make_unique<engine::GUI::GuiScroll>(engine::config::Facade::Rect({410, 50},
                                                                {400, 1075 - list->boundary.height}),
                                                                  engine::config::Facade::Color(60, 40, 8));

    for (auto* fact : Units::allUnits) {
        factoriesAvailable->addChild(std::unique_ptr<engine::GUI::GuiObject>(getAvailableFactoryObject(fact)));
    }
    mainPanel->boundary.height = 1075 - list->boundary.height;
    list->addChild(std::move(mainPanel));
    show();
};

bool Squads::SquadTemplate::isPossible(Cell *ptr) {
    for(auto i : temp) if(!i.first.first ->isPossible(ptr)) return false;
    return true;
}

void Squads::SquadTemplate::addFactory(Factory *ptr, int n) {
    for(auto & i : temp) if(i.first.first == ptr) {
        i.first.second += n;
        i.second.second->Text = std::to_string(i.first.second);
        return;
    }

    //create new gui object
    auto listObj = getFactoryListObject(ptr, n);
    scrollObj->addChild(std::unique_ptr<engine::GUI::GuiObject>(listObj.first));
    temp.emplace_back(std::make_pair(ptr, n), listObj);
}
void Squads::SquadTemplate::removeFactory(Factory* ptr) {
    std::remove_reference_t<decltype(temp[0])>* toSwap = nullptr;
    for (auto& i : temp) if (i.first.first == ptr) {
        --i.first.second;
        if (i.first.second == 0) {
            scrollObj->removeChild(i.second.first);
            toSwap = &i;
            break;
        }
        i.second.second->Text = std::to_string(i.first.second);
    }
    if (toSwap != nullptr) {
        std::swap(*toSwap, temp.back());
        temp.pop_back();
    }
}

void Squads::SquadTemplate::build(Cell* buildOn, Player::Player* owner) {
    if(temp.empty()) return;
    std::vector<std::pair<size_t, size_t>> toAction(temp.size());
    for (size_t i = 0; i < temp.size(); ++i) {
        toAction[i] = {temp[i].first.first->id, temp[i].first.second};
    }
    engine::gameController::Instance()->networkManager.addAction(std::unique_ptr<engine::Action>(
        new engine::actions::SpawnAction(std::move(toAction), buildOn->id, owner->id)
        ));
}

void Squads::SquadTemplate::show() {
    engine::gameController::Instance()->registerStaticObject(list.get());
    engine::gameController::Instance()->registerStaticObject(factoriesAvailable.get());
}
void Squads::SquadTemplate::hide() {
    engine::gameController::Instance()->unregisterStaticObject(list.get());
    engine::gameController::Instance()->unregisterStaticObject(factoriesAvailable.get());
}