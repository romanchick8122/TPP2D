class Unit;
class TestUnit;
#pragma once

#include <cstdio>
#include "UnitOrder.h"
#include "GameLogic/Squad.h"
#include "AllFlags.h"

class Unit {
protected:
    UnitOrder* currentOrder;
    size_t currentUsageOfOrder;
    UnitOrder* allOrders[1];
    Squad* squad;
    std::vector<float> unitLandscapeFlagResists;
    std::vector<float> unitBorderFlagResists;
    float unitSpeed;
public:
    const std::vector<float>* landscapeFlagResists = &unitLandscapeFlagResists;
    const std::vector<float>* borderFlagResists = &unitBorderFlagResists;
    const float* commonSpeed = &unitSpeed;
    virtual void tick() = 0;
    virtual bool isOrderPossible(UnitOrder*) = 0;
    virtual void enableOrder(UnitOrder*) = 0;
    virtual void disableOrder() = 0;
};

class TestUnit : public Unit {
public:
    TestUnit(Squad* ptr);
    bool isOrderPossible(UnitOrder*) override;
    void enableOrder(UnitOrder*) override;
    void disableOrder() override;
    void tick() override;

};
