class Factory;

#pragma once

#include <string>
#include "Cell.h"
#include "Unit.h"

class Factory {
protected:
    float cost;
    float weight;
public:
    const std::string name;
    const engine::config::Facade::Texture *texture;

    Factory(nlohmann::json &, const engine::config::Facade::Texture *&);

    Factory(nlohmann::json &, const engine::config::Facade::Texture *&, Factory *);

    virtual bool isPossible(Cell *) = 0;

    virtual Units::Unit *createUnit() = 0;
    //void render();
    //todo
};
