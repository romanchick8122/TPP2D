#pragma once
#include "graphics/SFMLFacade.h"
#include "nlohmann/json.hpp"
namespace engine::config {
    extern const float scaleSpeed;
    extern const float minScale;
    extern const float maxScale;
    using Facade = graphics::SFMLFacade;
    extern nlohmann::json runtime;
}