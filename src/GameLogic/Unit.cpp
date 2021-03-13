#include "GameLogic/Unit.h"
#include "GameLogic/UnitOrder.h"

void TestUnit::tick() {
    if(currentOrder != nullptr) currentOrder -> tick(this);
}

TestUnit::TestUnit(Squad* ptr) {
    unitSpeed = 10000;
    allOrders[0] = new TestOrder();
    currentOrder = allOrders[0];
    unitBorderFlagResists = Flags::generateBorderFlags();
    unitLandscapeFlagResists = Flags::generateLandscapeFlags();
};

bool TestUnit::isOrderPossible(UnitOrder* order) {
    return currentOrder == nullptr || currentOrder == order;
};

void TestUnit::enableOrder(UnitOrder* order) {
    if(!isOrderPossible(order)) return;
    if(currentOrder == nullptr) {
        currentOrder = order -> copy();
        currentUsageOfOrder = 1;
        return;
    }
    ++currentUsageOfOrder;
}

void TestUnit::disableOrder() {
    if(currentUsageOfOrder > 1) {
        --currentUsageOfOrder;
        return;
    }
    currentOrder = nullptr;
    currentUsageOfOrder = 0;
}


