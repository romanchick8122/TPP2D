#include "Player.h"

Player::Player::Player(int r, int g, int b) {
    color = graphics::SFMLFacade::Color(r, g, b);
}

Player::Player* Player::nullPlayer = new Player(50, 50, 50);

std::vector<Player::Player*> Player::players;

void Player::setPlayers(int playersCount) {
    for(int i = 0; i < playersCount; ++i)
        players.push_back(new Player((37*i + 10)%255, (29*i + 60)%255, (19*i + 150)%255));
}