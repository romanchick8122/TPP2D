#include "Player.h"

Player::Player::Player(int r, int g, int b) {
    color = graphics::SFMLFacade::Color(r, g, b);
}

Player::Player* Player::nullPlayer = new Player(50, 50, 50);