#include "ArmoredUnitFactory.h"

Units::ArmoredUnitFactory::ArmoredUnitFactory(nlohmann::json &unitInfo, const graphics::SFMLFacade::Texture *&,
                                              TransportUnitFactory *base_) :
        Factory(unitInfo, texture, base_) {
    base = base_;
    attack = unitInfo["attack"];
}

bool Units::ArmoredUnitFactory::isPossible(Cell *) {
    return true;
}

Units::Unit *Units::ArmoredUnitFactory::createUnit() {
    auto *unit = new Units::ArmoredUnit(dynamic_cast<TransportUnit *>(base->createUnit()), name, weight);
    unit->setStats(attack);
    return unit;
}
