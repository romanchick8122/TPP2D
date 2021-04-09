#pragma once
#include "engine/Action.h"
namespace engine::actions {
    class None : engine::Action {
      public:
        void write(const std::ostream&) override;
        void apply() override;
    };
}