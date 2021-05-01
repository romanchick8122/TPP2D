#pragma once

#include "Unit.h"

namespace Units {
    class TransportUnit : public Unit {
        float capacity, armor;
        float loadWeight;
        std::list<Unit *> units;
    public:
        float getAttack() override;

        bool isPossibleToAdd(Unit *);

        void addUnit(Unit *);

        void deleteUnit(const Unit *&);

        TransportUnit(const std::string &name_, const graphics::SFMLFacade::Texture *&texture_, float weight_);

        void setStats(float HP_, float speed_, float capacity_, float armor_);

        void tick() override;
    };
}
