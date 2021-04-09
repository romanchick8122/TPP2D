#pragma once
#include "engine/Action.h"
namespace engine::actions {
    class None : engine::Action {
      public:
        void write(std::ostream&) override;
        static std::unique_ptr<Action> read(std::istream&);
        void apply() override;
    };
}