class UnitOrder;
class TestOrder;

#pragma once
#include <string>
#include "GameLogic/Unit.h"

class UnitOrder {
public:
    virtual void tick(Unit* ptr) = 0;
    virtual UnitOrder* copy() = 0;
};

class TestOrder : public UnitOrder {
public:
    std::string name = "test_order";
    void tick(Unit* ptr) override;
    UnitOrder* copy();
};