#include "GameLogic/UnitOrder.h"
#include <iostream>

void TestOrder::tick(Unit* ptr) {
    std::cout << "tick";
}

UnitOrder* TestOrder::copy() {
    return this;
}
