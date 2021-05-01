#include "Factory.h"

Factory1::Factory1(float cost_, int param1_) : param1(param1_){
    cost = cost_;
}

bool Factory1::isPossible(Cell*) {
    return true;
}

Unit* Factory1::createUnit() {
    return new TestUnit1(param1);
}


Factory2::Factory2(float cost_, int param1_, int param2_) : param1(param1_), param2(param2_){
    cost = cost_;
}

bool Factory2::isPossible(Cell *) {
    return true;
}

Unit *Factory2::createUnit() {
    return new TestUnit2(param1, param2);
}

Factory3::Factory3(float cost_, int param1_, int param2_, int param3_) : param1(param1_), param2(param2_), param3(param3_){
    cost = cost_;
}

bool Factory3::isPossible(Cell *) {
    return true;
}

Unit *Factory3::createUnit() {
    return new TestUnit3(param1, param2, param3);
}

