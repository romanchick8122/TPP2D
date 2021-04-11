namespace Units {
    class Unit;

    class TestUnit;
}

#pragma once

#include <cstdio>
#include "UnitOrder.h"
#include "GameLogic/Squad/Squad.h"
#include "AllFlags.h"
#include "graphics/Textures.h"

namespace Units {
    class Unit {
    protected:
        UnitOrder *currentOrder;
        size_t currentUsageOfOrder;
        std::vector<UnitOrder *> allOrders;
        Squads::Squad *squad;
        std::vector<float> unitLandscapeFlagResists;
        std::vector<float> unitBorderFlagResists;
        float unitSpeed;
        float HP;
    public:
        const std::string name;
        const engine::config::Facade::Texture *texture;
        const float weight;

        Unit();

        Unit(const engine::config::Facade::Texture *&, const std::string &, float);

        void setSquad(Squads::Squad *);

        const std::vector<float> *landscapeFlagResists = &unitLandscapeFlagResists;
        const std::vector<float> *borderFlagResists = &unitBorderFlagResists;
        const float *commonSpeed = &unitSpeed;

        virtual void tick() = 0;

        virtual float getAttack() = 0;

        bool isOrderPossible(UnitOrder *);

        void enableOrder(UnitOrder *);

        void disableOrder();
    };
}