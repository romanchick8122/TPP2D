#include "AllFlags.h"
namespace Flags{
    std::vector<const Flag*> landscapeFlags;
    std::vector<const Flag*> borderFlags;
    void setFlags() {
        //landscape flags
        Flag* landscape0 = new Flag;
        landscape0->name = "forest";
        landscape0->speedInfluence = 0.5;
        landscape0->randParameter = 10;
        landscapeFlags.push_back(landscape0);


        //border flags
        Flag* border0 = new Flag;
        border0->name = "reinforces";
        border0->speedInfluence = 5;
        border0->randParameter = 10;
        borderFlags.push_back(border0);
    }
    std::vector<float> generateLandscapeFlags() {
        std::vector<float> newFlags;
        for(int i = 0; i <  landscapeFlags.size(); ++i) {
            newFlags.push_back(landscapeFlags[i]->randValue());
        }
        return newFlags;
    }
    std::vector<float> generateBorderFlags() {
        std::vector<float>* newFlags = new std::vector<float>;
        for(int i = 0; i <  borderFlags.size(); ++i) {
            newFlags->push_back(borderFlags[i]->randValue());
        }
        return *newFlags;
    }
}