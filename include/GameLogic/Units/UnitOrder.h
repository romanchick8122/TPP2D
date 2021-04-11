class UnitOrder;

class TestOrder;

#pragma once

#include <string>
#include "GameLogic/Units/Unit.h"

class UnitOrder {
public:
    virtual void tick(Units::Unit *ptr) = 0;

    virtual UnitOrder *copy() = 0;
};

class TestOrder : public UnitOrder {
public:
    std::string name = "test_order";

    void tick(Units::Unit *ptr) override;

    UnitOrder *copy();
};