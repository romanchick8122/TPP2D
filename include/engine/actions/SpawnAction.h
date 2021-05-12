#pragma once
#include "engine/Action.h"
#include <vector>
namespace engine::actions {
    class SpawnAction : public engine::Action {
        std::vector<std::pair<size_t, size_t>> factories;
        size_t buildOn;
        char owner;
      public:
        SpawnAction(std::vector<std::pair<size_t, size_t>>&&, size_t, char);
        void write(std::ostream&) override;
        static std::unique_ptr<engine::Action> read(std::istream&);
        void apply() override;

    };
}