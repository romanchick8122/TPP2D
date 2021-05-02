#include "ArmoredUnitFactory.h"

Units::ArmoredUnitFactory::ArmoredUnitFactory(nlohmann::json &unitInfo, const graphics::SFMLFacade::Texture *& texture_,
                                              TransportUnitFactory *base_) :
        Factory(unitInfo, texture_, base_) {
    base = base_;
    attack = unitInfo["attack"];
}

bool Units::ArmoredUnitFactory::isPossible(Cell *) {
    return true;
}

Units::Unit *Units::ArmoredUnitFactory::createUnit() {
    auto gay = dynamic_cast<TransportUnit *>(base->createUnit());
    gay->texture;
    gay->name;
    gay->weight;
    auto *unit = new Units::ArmoredUnit(dynamic_cast<TransportUnit *>(base->createUnit()), name, weight);
    unit->setStats(attack);
    return unit;
}
