#include "GameLogic/Units/Unit.h"
#include "GameLogic/Units/UnitOrder.h"

bool Units::Unit::isOrderPossible(UnitOrder *order) {
    bool exist = false;
    for (auto i : allOrders) if (order == i) exist = true;
    return (currentOrder == nullptr || currentOrder == order) && exist;
}

void Units::Unit::enableOrder(UnitOrder *order) {
    if (!isOrderPossible(order)) return;
    if (currentOrder == nullptr) {
        currentOrder = order->copy();
        currentUsageOfOrder = 1;
        return;
    }
    ++currentUsageOfOrder;
}

void Units::Unit::disableOrder() {
    if (currentUsageOfOrder > 1) {
        --currentUsageOfOrder;
        return;
    }
    currentOrder = nullptr;
    currentUsageOfOrder = 0;
}

void Units::Unit::setSquad(Squads::Squad *ptr) {
    squad = ptr;
}

Units::Unit::Unit(const graphics::SFMLFacade::Texture *&texture_, const std::string &name_, float weight_) : name(name_),
                                                                                                             texture(texture_),
                                                                                                             weight(weight_) {
    HP = 1;
}

bool Units::Unit::isAlive() {
    return HP > 0;
}

void Units::Unit::drawHP(engine::config::Facade::Rect rect) {
    auto coef = HP/fullHP;
    rect.width *= coef;
    engine::config::Facade::DrawRect(rect, engine::config::Facade::Color(static_cast<int>(255*(1-coef)),
                                                                         static_cast<int>(255*coef),0, 128));
}
