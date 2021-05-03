#pragma once

#include "Flag.h"
#include "memory"

namespace Flags {
    extern std::vector<std::unique_ptr<Flag>> landscapeFlags;
    extern std::vector<std::unique_ptr<Flag>> borderFlags;

    void setFlags();

    std::vector<float> generateBorderFlags();

    std::vector<float> generateLandscapeFlags();
}