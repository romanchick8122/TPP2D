#include "GameLogic/UnitOrder.h"

void TestOrder::tick(Unit* ptr) {
    std::cout << "tick";
}

UnitOrder* TestOrder::copy() {
    return this;
}
