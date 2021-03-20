#pragma once
#include "Factory.h"
namespace AllUnits {
    Factory1* TU1_light = new Factory1(100, 1);
    Factory1* TU1_heavy = new Factory1(300, 15);
    Factory2* TU2_medium = new Factory2(400, 14, 50);
    Factory2* TU2_heavy = new Factory2(700, 19, 120);
    Factory3* TU2_armored = new Factory3(900, 9, 53, 700);
    Factory3* TU2_OP = new Factory3(10000, 1000, 1000, 1000);
}