#include <string>
#include "Cell.h"
#include "Unit.h"
class Factory;
#pragma once
class Factory {
protected:
    float cost;
public:
    const std::string name;
    Factory(const std::string&, float);
    virtual bool isPossible(Cell*) = 0;
    virtual Units::Unit* createUnit() = 0;
    //void render();
    //todo
};
