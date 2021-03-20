#include "GameLogic/Unit.h"
#include "GameLogic/UnitOrder.h"

bool Unit::isOrderPossible(UnitOrder* order) {
    bool exist = false;
    for(auto i : allOrders) if(order == i) exist = true;
    return (currentOrder == nullptr || currentOrder == order) && exist;
};

void Unit::enableOrder(UnitOrder* order) {
    if(!isOrderPossible(order)) return;
    if(currentOrder == nullptr) {
        currentOrder = order -> copy();
        currentUsageOfOrder = 1;
        return;
    }
    ++currentUsageOfOrder;
}

void Unit::disableOrder() {
    if(currentUsageOfOrder > 1) {
        --currentUsageOfOrder;
        return;
    }
    currentOrder = nullptr;
    currentUsageOfOrder = 0;
}

void Unit::setSquad(Squad *ptr) {
    squad = ptr;
}


void TestUnit1::tick() {
    if(currentOrder != nullptr) currentOrder -> tick(this);
}

TestUnit1::TestUnit1(int param1_) : param1(param1_) {
    allOrders = std::vector<UnitOrder*>(1);
    unitSpeed = 100;
    allOrders[0] = new TestOrder();
    currentOrder = allOrders[0];
    unitBorderFlagResists = Flags::generateBorderFlags();
    unitLandscapeFlagResists = Flags::generateLandscapeFlags();
};

void TestUnit2::tick() {
    if(currentOrder != nullptr) currentOrder -> tick(this);
}

TestUnit2::TestUnit2(int param1_, int param2_) : param1(param1_), param2(param2_) {
    allOrders = std::vector<UnitOrder*>(1);
    unitSpeed = 1000;
    allOrders[0] = new TestOrder();
    currentOrder = allOrders[0];
    unitBorderFlagResists = Flags::generateBorderFlags();
    unitLandscapeFlagResists = Flags::generateLandscapeFlags();
};


void TestUnit3::tick() {
    if(currentOrder != nullptr) currentOrder -> tick(this);
}

TestUnit3::TestUnit3(int param1_, int param2_, int param3_) : param1(param1_), param2(param2_), param3(param3_) {
    allOrders = std::vector<UnitOrder*>(1);
    unitSpeed = 10000;
    allOrders[0] = new TestOrder();
    currentOrder = allOrders[0];
    unitBorderFlagResists = Flags::generateBorderFlags();
    unitLandscapeFlagResists = Flags::generateLandscapeFlags();
};
