#include "graphics/Textures.h"
void graphics::Textures::loadTextures() {
    squad = new engine::config::Facade::Texture;
    squad->loadFromFile("resources/squad.png");
}
engine::config::Facade::Texture* graphics::Textures::squad;