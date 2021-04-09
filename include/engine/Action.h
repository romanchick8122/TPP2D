#pragma once
#include "iostream"
namespace engine {
    class Action {
        void write(const std::ostream&);
        void read(const std::istream&);
        void apply();
    };
}