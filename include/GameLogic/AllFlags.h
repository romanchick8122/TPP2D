#pragma once
#include "Flag.h"
namespace Flags{
    extern std::vector<const Flag*> landscapeFlags;
    extern std::vector<const Flag*> borderFlags;
    void setFlags();
    std::vector<float> generateBorderFlags();
    std::vector<float> generateLandscapeFlags();
}