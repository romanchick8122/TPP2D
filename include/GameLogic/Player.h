#pragma once

#include "graphics/Facade.h"
#include "graphics/SFMLFacade.h"

namespace Player{
    struct Player {
        graphics::SFMLFacade::Color color;
        char id;
        Player(int, int, int, char);
    };

    extern Player* nullPlayer;
    extern std::vector<Player*> players;

    void setPlayers(int);
}
