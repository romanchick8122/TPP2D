#pragma once
#include "engine/Action.h"

namespace engine::actions {
    class ClickAction : public engine::Action {
    public:
        int id;
        void write(std::ostream&) override;
        static std::unique_ptr<Action> read(std::istream&);
        void apply() override;
    };
}