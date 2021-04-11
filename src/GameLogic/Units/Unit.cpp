#include "GameLogic/Units/Unit.h"
#include "GameLogic/Units/UnitOrder.h"

bool Units::Unit::isOrderPossible(UnitOrder* order) {
    bool exist = false;
    for(auto i : allOrders) if(order == i) exist = true;
    return (currentOrder == nullptr || currentOrder == order) && exist;
};

void Units::Unit::enableOrder(UnitOrder* order) {
    if(!isOrderPossible(order)) return;
    if(currentOrder == nullptr) {
        currentOrder = order -> copy();
        currentUsageOfOrder = 1;
        return;
    }
    ++currentUsageOfOrder;
}

void Units::Unit::disableOrder() {
    if(currentUsageOfOrder > 1) {
        --currentUsageOfOrder;
        return;
    }
    currentOrder = nullptr;
    currentUsageOfOrder = 0;
}

void Units::Unit::setSquad(Squads::Squad *ptr) {
    squad = ptr;
}

Units::Unit::Unit(const graphics::SFMLFacade::Texture *&texture_, const std::string &name_) :name(name_), texture(texture_){

}

Units::Unit::Unit() {

}

void Units::TestUnit1::tick() {
    if(currentOrder != nullptr) currentOrder -> tick(this);
}

Units::TestUnit1::TestUnit1(int param1_) : param1(param1_) {
    allOrders = std::vector<UnitOrder*>(1);
    unitSpeed = 100;
    allOrders[0] = new TestOrder();
    currentOrder = allOrders[0];
    unitBorderFlagResists = Flags::generateBorderFlags();
    unitLandscapeFlagResists = Flags::generateLandscapeFlags();
};