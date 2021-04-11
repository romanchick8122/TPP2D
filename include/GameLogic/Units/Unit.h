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
        const std::string name;
        const engine::config::Facade::Texture* texture;
    public:
        Unit();
        Unit(const engine::config::Facade::Texture*&, const std::string&);
        void setSquad(Squads::Squad *);

        const std::vector<float> *landscapeFlagResists = &unitLandscapeFlagResists;
        const std::vector<float> *borderFlagResists = &unitBorderFlagResists;
        const float *commonSpeed = &unitSpeed;

        virtual void tick() = 0;

        bool isOrderPossible(UnitOrder *);

        void enableOrder(UnitOrder *);

        void disableOrder();
    };

    class TestUnit1 : public Unit {
        int param1;
    public:
        TestUnit1(int param1_);

        void tick() override;

    };

    class TestUnit2 : public Unit {
        int param1;
        int param2;
    public:
        TestUnit2(int param1_, int param2_);

        void tick() override;

    };

    class TestUnit3 : public Unit {
        int param1;
        int param2;
        int param3;
    public:
        TestUnit3(int param1_, int param2_, int param3_);

        void tick() override;

    };
}