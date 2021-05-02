#pragma once

#include "graphics/Facade.h"
#include "graphics/SFMLFacade.h"

namespace Player{
    struct Player {
        graphics::SFMLFacade::Color color;
        Player(int, int, int);
    };

    extern Player* nullPlayer;
}
