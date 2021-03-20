#include <string>
#include "Cell.h"
#include "Unit.h"
class Factory;
#pragma once
class Factory {
protected:
    float cost;
public:
    const std::string name;
    virtual bool isPossible(Cell*) = 0;
    virtual Unit* createUnit() = 0;
    //void render();
    //todo
};

class Factory1 : public Factory {
    int param1;
public:
    explicit Factory1(float cost_, int param1_);
    bool isPossible(Cell*) override;
    Unit* createUnit() override;
};

class Factory2 : Factory {
    int param1;
    int param2;
public:
    Factory2(float cost_, int param1_, int param2_);
    bool isPossible(Cell*) override;
    Unit* createUnit() override;
};

class Factory3 : Factory {
    int param1;
    int param2;
    int param3;
public:
    Factory3(float cost_, int param1_, int param2_, int param3_);
    bool isPossible(Cell*) override;
    Unit* createUnit() override;
};
