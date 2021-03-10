#pragma once
#include "Unit.h"

class UnitOrder {
public:
    UnitOrder(Unit*);
    virtual void tick();
    virtual UnitOrder* Copy();
};

class testOrder : UnitOrder {
public:
    const std::string name = "test_order";
    void tick() {
        std::cout << "tick";
    }
    UnitOrder* Copy() {
        return this;
    }
};