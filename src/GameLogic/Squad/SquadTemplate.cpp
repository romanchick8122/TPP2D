#include "GameLogic/Squad/SquadTemplate.h"
#include <memory>
#include "engine/GUI/Button.h"
#include "GameLogic/Units/AllUnits.h"
#include "engine/GUI/GuiStrip.h"
#include "engine/GUI/GuiScroll.h"
Squads::SquadTemplate::SquadTemplate() : list(new engine::GUI::GuiList(engine::config::Facade::Color(60, 40, 8))) {
    auto topMenuStrip = std::make_unique<engine::GUI::GuiStrip>(600, engine::config::Facade::Color(0,0,0,0));
    topMenuStrip->addChild(std::make_unique<engine::GUI::Button>(
        engine::config::Facade::Rect({0, 0}, {555, 30}),
        [](engine::GUI::Button*){},
        engine::config::Facade::Color(0, 0, 0, 0),
        name,
        engine::config::Facade::Color(255, 220, 220)));
    topMenuStrip->addChild(std::make_unique<engine::GUI::Button>(
        engine::config::Facade::Rect({0, 0}, {30, 30}),
        [this](engine::GUI::Button*){ hide(); },
        engine::config::Facade::Color(255, 0, 0)
        ));
    list->addChild(std::move(topMenuStrip));


    auto mainPanel = std::make_unique<engine::GUI::GuiScroll>(engine::config::Facade::Rect(
        {0, 0}, {600, 1075 - list->boundary.height}),
                                                              engine::config::Facade::Color(30, 20, 4));
    engine::GUI::GuiScroll* scrollObj = mainPanel.get();

    auto buttonStrip = std::make_unique<engine::GUI::GuiStrip>(600, engine::config::Facade::Color(30, 20, 4));
    auto buttonLambda = [scrollObj](engine::GUI::Button* button) {
        scrollObj->addChild(std::make_unique<engine::GUI::Button>(
            engine::config::Facade::Rect({0, 0}, {590, 90}),
            [scrollObj](engine::GUI::Button* button){
                scrollObj->removeChild(button);
                },
            button->Texture
        ));
    };

    for (auto* fact : Units::allUnits) {
        buttonStrip->addChild(std::make_unique<engine::GUI::Button>(
            engine::config::Facade::Rect({0, 0},
                                         {static_cast<float>(fact->texture->getSize().x),
                                          static_cast<float>(fact->texture->getSize().y)}),
            buttonLambda,
            const_cast<engine::config::Facade::Texture*>(fact->texture)));
    }
    list->addChild(std::move(buttonStrip));
    mainPanel->boundary.height = 1075 - list->boundary.height;
    list->addChild(std::move(mainPanel));
    show();
};

bool Squads::SquadTemplate::isPossible(Cell *ptr) {
    for(auto i : temp) if(!i.first ->isPossible(ptr)) return false;
    return true;
}

void Squads::SquadTemplate::addFactory(Factory *ptr, int n) {
    for(auto & i : temp) if(i.first == ptr) {
        i.second += n;
        return;
    }
    temp.emplace_back(ptr, n);
}

Squads::Squad* Squads::SquadTemplate::build() {
    if(temp.empty()) return nullptr;
    std::list<Units::Unit*> units_;
    for(auto f : temp) for(int i = 0; i < f.second; ++i) units_.push_back(f.first -> createUnit());
    return new Squads::Squad(units_);
}

void Squads::SquadTemplate::show() {
    engine::gameController::Instance()->registerStaticObject(list.get());
}
void Squads::SquadTemplate::hide() {
    engine::gameController::Instance()->unregisterStaticObject(list.get());
}