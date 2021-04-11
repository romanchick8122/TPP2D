#include "GameLogic/Squad/SquadTemplate.h"
#include <memory>
#include "engine/GUI/Button.h"
#include "GameLogic/Units/AllUnits.h"
#include "engine/GUI/GuiStrip.h"
Squads::SquadTemplate::SquadTemplate() : list(new engine::GUI::GuiList(engine::config::Facade::Color(60, 40, 8))) {
    auto buttonStrip = std::make_unique<engine::GUI::GuiStrip>(600, engine::config::Facade::Color(30, 20, 4));
    for (auto* fact : Units::allUnits) {
        
    }
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

Squads::Squad *Squads::SquadTemplate::build() {
    if(temp.empty()) return nullptr;
    std::list<Units::Unit*> units_;
    for(auto f : temp) for(int i = 0; i < f.second; ++i) units_.push_back(f.first -> createUnit());
    return new Squads::Squad(nullptr, units_);
}
