#pragma once
#include "iostream"
#include "memory"
namespace engine {
    class Action {
      public:
        enum Type {
            None,
            SetSquadPath
        };
        virtual void write(std::ostream&) = 0;
        virtual void apply() = 0;
    };
    std::unique_ptr<Action> readAction(std::istream&);
}