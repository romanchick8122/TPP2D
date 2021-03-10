#pragma once
#include "Cell.h"
#include "UnitOrder.h"

class Unit {
public:
    virtual void tick();
};

class TestUnit {
    UnitOrder* currentOrder;
    size_t currentUsageOfOrder;
    Squad* squad;
    UnitOrder* allOrders[1];
    TestUnit(Squad* ptr) : squad(ptr){
        allOrders[0] = new TestOrder();
    };

    void tick() {
        currentOrder -> tick(this);
    }
};
