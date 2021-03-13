#include "util/pathfinding.h"
#include <queue>
namespace util::pathfinding {
    std::list<const Cell*> dijkstraPath(const Cell* from, const Cell* to, const Squad* squad) {
        std::priority_queue<std::pair<float, std::pair<const Cell*, const Cell*>>> distanceHeap;
        std::map<const Cell*, std::pair<float, const Cell*>> distance;
        distanceHeap.push({0, {from, nullptr}});
        while (!distanceHeap.empty()) {
            auto [dist, cpPair] = distanceHeap.top();
            auto [cell, prev] = cpPair;
            distanceHeap.pop();
            if (distance.find(cell) != distance.end()) {
                continue;
            }
            distance[cell] = {dist, prev};
            if (cell == to) {
                std::list<const Cell*> ans;
                const Cell* curr = to;
                while (curr != from) {
                    ans.push_front(curr);
                    curr = distance[curr].second;
                }
                return ans;
            }
        }
    }
}
