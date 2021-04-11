#pragma once
#include "Unit.h"
namespace Units {
    class LandUnit : public Unit{
        float HP, attack;
    public:
        LandUnit(const std::string &name_, const graphics::SFMLFacade::Texture *&texture_);
        void setStats(float HP_, float speed_, float attack_);
        void tick() override;
    };
}
