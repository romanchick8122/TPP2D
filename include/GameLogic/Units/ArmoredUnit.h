#include "Unit.h"
#include "TransportUnit.h"

namespace Units {
    class ArmoredUnit : public Unit {
        TransportUnit *base;
        float attack;
    public:
        const TransportUnit *getAsTransport();

        ArmoredUnit(const ArmoredUnit &) = delete;

        ArmoredUnit(TransportUnit *base_, const std::string &name_, float weaponWeight);

        float getAttack() override;

        void changeHP(float) override;

        bool isAlive() override;

        void drawHP(engine::config::Facade::Rect) override;

        void setStats(float attack);

        void tick() override;
    };
}
