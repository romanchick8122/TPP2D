#pragma once
#include <list>
#include <iostream>
#include <util/cellgen.h>
#include "Unit.h"

class GameObject {
public:
    virtual void render();
    virtual void tick();
    virtual void lateTick();
};

class Player {

};
