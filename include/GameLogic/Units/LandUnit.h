#include "Unit.h"
namespace Units {
    class LandUnit : public Unit{
        float HP, attack;
    public:
        LandUnit(float HP_, float speed_, float attack_);
        void tick() override;
    };
}
