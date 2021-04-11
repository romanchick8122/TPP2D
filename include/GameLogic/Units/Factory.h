class Factory;
#pragma once
#include <string>
#include "Cell.h"
#include "Unit.h"
class Factory {
protected:
    float cost;
public:
    const std::string name;
    const engine::config::Facade::Texture* texture;
    Factory(const std::string&, float, const engine::config::Facade::Texture*&);
    virtual bool isPossible(Cell*) = 0;
    virtual Units::Unit* createUnit() = 0;
    //void render();
    //todo
};
