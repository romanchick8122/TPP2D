namespace Squads {
    class Action;
}

#pragma once

#include "Squad.h"
#include "Cell.h"

namespace Squads {
    class Action {
        float progress;
        float endProgress;
        Squad* squad;
        float speed;
        bool underAttack = false;
        engine::config::Facade::Point d;
        std::list<Cell*> currentPath;
        std::list<Cell*> possiblePath;
    public:
        Action(Squad*);

        void nextStep();

        void move();

        void attack();

        float calcSpeed(const Cell* start, const Cell* end);

        std::list<Cell*> findPath(Cell*, Cell*);

        void stopAction();

        void setPath();

        void setPath(Cell*);

        void tick();

        void lateTick();

        void render();
    };
}