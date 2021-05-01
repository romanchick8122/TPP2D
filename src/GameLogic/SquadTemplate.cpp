#include "SquadTemplate.h"

SquadTemplate::SquadTemplate() {}

bool SquadTemplate::isPossible(Cell *ptr) {
    for(auto i : temp) if(!i.first ->isPossible(ptr)) return false;
    return true;
}

void SquadTemplate::addFactory(Factory *ptr, int n) {
    for(int i = 0; i < temp.size(); ++i) if(temp[i].first == ptr) {
        temp[i].second += n;
        return;
    }
    temp.push_back({ptr, n});
}

Squad *SquadTemplate::build() {
    if(temp.empty()) return nullptr;
    std::list<Unit*> units_;
    for(auto f : temp) for(int i = 0; i < f.second; ++i) units_.push_back(f.first -> createUnit());
    return new Squad(nullptr, units_);
}

