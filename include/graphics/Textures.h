#include "engine/config.h"
#include <vector>
#include <unordered_map>
namespace graphics::Textures {
    void loadTextures();
    extern std::unordered_map<std::string, size_t> nameMapping;
    extern std::vector<engine::config::Facade::Texture*> textures;
}