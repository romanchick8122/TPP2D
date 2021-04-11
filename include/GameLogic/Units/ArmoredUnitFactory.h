#include "Factory.h"
#include "TransportUnitFactory.h"
#include "ArmoredUnit.h"

namespace Units {
    class ArmoredUnitFactory : public Factory {
        TransportUnitFactory *base;
        float speed, attack;
    public:
        explicit ArmoredUnitFactory(nlohmann::json &, const engine::config::Facade::Texture *&, TransportUnitFactory *);

        bool isPossible(Cell *) override;

        Units::Unit *createUnit() override;
    };
}