#include "SquadTemplate.h"

SquadTemplate::SquadTemplate() : GuiList(engine::config::Facade::Color(60, 40, 8)) {};

bool SquadTemplate::isPossible(Cell *ptr) {
    for(auto i : temp) if(!i.first ->isPossible(ptr)) return false;
    return true;
}

void SquadTemplate::addFactory(Factory *ptr, int n) {
    for(auto & i : temp) if(i.first == ptr) {
        i.second += n;
        return;
    }
    temp.emplace_back(ptr, n);
}

Squad *SquadTemplate::build() {
    if(temp.empty()) return nullptr;
    std::list<Units::Unit*> units_;
    for(auto f : temp) for(int i = 0; i < f.second; ++i) units_.push_back(f.first -> createUnit());
    return new Squad(nullptr, units_);
}