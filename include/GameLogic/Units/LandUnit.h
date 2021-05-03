#pragma once

#include "Unit.h"

namespace Units {
    class LandUnit : public Unit {
        float attack;
    public:
        LandUnit(const std::string &name_, const graphics::SFMLFacade::Texture *&texture_, float weight_);

        void setStats(float HP_, float speed_, float attack_);

        void tick() override;

        float getAttack() override;
    };
}
