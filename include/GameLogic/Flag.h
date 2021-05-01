struct Flag;
#pragma once
#include <vector>
#include <string>

struct Flag {
    std::string name;
    float speedInfluence;
    float randParameter;
    //todo render options
    float randValue() const;
    void render() const;
};
