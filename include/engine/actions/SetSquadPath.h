#pragma once
#include "engine/Action.h"
#include "GameLogic/Squad/Squad.h"
#include "GameLogic/Cell.h"
namespace engine::actions {
    class SetSquadPath : public engine::Action {
        size_t squadId;
        size_t targetId;
        SetSquadPath();
      public:
        SetSquadPath(Squads::Squad*, Cell*);
        void write(std::ostream&) override;
        static std::unique_ptr<engine::Action> read(std::istream&);
        void apply() override;
    };
}