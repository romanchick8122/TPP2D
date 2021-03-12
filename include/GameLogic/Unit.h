class Unit;
class TestUnit;
#pragma once

#include <cstdio>
#include "UnitOrder.h"
#include "GameLogic/Squad.h"

class Unit {
public:
    virtual void tick() = 0;
    virtual bool isOrderPossible(UnitOrder*) = 0;
    virtual void enableOrder(UnitOrder*) = 0;
    virtual void disableOrder() = 0;
};

class TestUnit : public Unit {
    UnitOrder* currentOrder;
    size_t currentUsageOfOrder;
    Squad* squad;
    UnitOrder* allOrders[1];
public:
    TestUnit(Squad* ptr);
    bool isOrderPossible(UnitOrder*) override;
    void enableOrder(UnitOrder*) override;
    void disableOrder() override;
    void tick() override;

};
