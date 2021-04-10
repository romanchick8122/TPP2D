#include "graphics/Textures.h"
void graphics::Textures::loadTextures() {
    auto tex = engine::config::runtime["graphics"]["Textures"]["list"];
    textures.reserve(tex.size());
    for (auto& tx : tex) {
        auto* newTex = new engine::config::Facade::Texture;
        newTex->loadFromFile(tx);
        nameMapping[tx] = textures.size();
        textures.push_back(newTex);
    }
}
std::unordered_map<std::string, size_t> graphics::Textures::nameMapping;
std::vector<engine::config::Facade::Texture*> graphics::Textures::textures;