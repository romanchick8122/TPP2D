#include "AllFlags.h"
#include "engine/config.h"
namespace Flags{
    std::vector<std::unique_ptr<Flag>> landscapeFlags;
    std::vector<std::unique_ptr<Flag>> borderFlags;
    void setFlags() {
        for (auto& lo : engine::config::runtime["GameLogic"]["AllFlags"]["landscape"]) {
            Flag* land = new Flag;
            land->name = lo["name"];
            land->speedInfluence = lo["speedInfluence"];
            land->randParameter = lo["randParameter"];
            landscapeFlags.push_back(std::unique_ptr<Flag>(land));
        }
        for (auto& lo : engine::config::runtime["GameLogic"]["AllFlags"]["border"]) {
            Flag* land = new Flag;
            land->name = lo["name"];
            land->speedInfluence = lo["speedInfluence"];
            land->randParameter = lo["randParameter"];
            borderFlags.push_back(std::unique_ptr<Flag>(land));
        }
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