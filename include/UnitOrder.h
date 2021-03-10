#pragma once
#include "Unit.h"

class UnitOrder {
public:
    UnitOrder(Unit*);
    virtual void tick(Unit*);
    virtual UnitOrder* copy();
};

class TestOrder : public UnitOrder {
public:
    std::string name = "test_order";
    void tick(Unit* ptr) {
        std::cout << "tick";
    }
    UnitOrder* copy() {
        return this;
    }
};