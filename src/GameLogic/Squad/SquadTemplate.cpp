#include "GameLogic/Squad/SquadTemplate.h"

Squads::SquadTemplate::SquadTemplate() {}

bool Squads::SquadTemplate::isPossible(Cell *ptr) {
    for(auto i : temp) if(!i.first ->isPossible(ptr)) return false;
    return true;
}

void Squads::SquadTemplate::addFactory(Factory *ptr, int n) {
    for(int i = 0; i < temp.size(); ++i) if(temp[i].first == ptr) {
        temp[i].second += n;
        return;
    }
    temp.push_back({ptr, n});
}

Squads::Squad *Squads::SquadTemplate::build() {
    if(temp.empty()) return nullptr;
    std::list<Units::Unit*> units_;
    for(auto f : temp) for(int i = 0; i < f.second; ++i) units_.push_back(f.first -> createUnit());
    return new Squads::Squad(nullptr, units_);
}

