class Factory;

#pragma once

#include <string>
#include "Cell.h"
#include "Unit.h"
#include "engine/gameObject.h"

class Factory : public engine::gameObject {
protected:
    float weight;
public:
    float cost;
    const std::string name;
    const engine::config::Facade::Texture *texture;

    Factory(nlohmann::json &, const engine::config::Facade::Texture *&);

    Factory(nlohmann::json &, const engine::config::Facade::Texture *&, Factory *);

    virtual bool isPossible(Cell *) = 0;

    virtual Units::Unit *createUnit() = 0;
    void render() override;
    void tick() override;
    void lateTick() override;
    std::string repr() override;
    engine::config::Facade::Rect getRenderEdges() override;
    virtual bool tryOnClick(engine::config::Facade::Point clickPosition, graphics::Event::MouseButton) override;
};
