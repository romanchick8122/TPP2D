namespace Squads {
    class Squad;
}
#pragma once

#include "GameLogic/Cell.h"
#include "GameLogic/Units/Unit.h"
#include "engine/gameplayClickableGameObject.h"
#include "GameLogic/Squad/Action.h"
#include "engine/config.h"
#include "graphics/Facade.h"
#include "Player.h"

namespace Squads {
    class Squad : public engine::gameplayClickableGameObject {
        Player::Player* owner = Player::nullPlayer;
        engine::config::Facade::Point center = {100, 100};
        engine::config::Facade::Rect shape;
        Cell* cell;

        engine::config::Facade::Rect getRenderEdges() override;

        std::list<Units::Unit*> units;

        float fullAttack;
        float attack;

        void updateUnitSquadPtr();

        void update();

        float squadCurrentSpeed;

        void updateFlagResists();

        std::vector<float> squadLandscapeFlagResists;
        std::vector<float> squadBorderFlagResists;
    public:
        friend Squads::Action;

        void setOwner(Player::Player* owner_);

        void setCell(Cell*);

        void damageUnit(float&);


        float& getAttack();

        Squad(std::list<Units::Unit*>);
        ~Squad();

        const float* currentSpeed = &squadCurrentSpeed;
        const std::vector<float>* landscapeFlagResists = &squadLandscapeFlagResists;
        const std::vector<float>* borderFlagResists = &squadBorderFlagResists;
        Action* action;

        void tick() override;

        void lateTick() override;

        void render() override;

        bool tryOnClick(engine::config::Facade::Point pos, graphics::Event::MouseButton) override;

        void doOnClick() override;
    };
}
