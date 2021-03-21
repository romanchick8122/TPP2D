#include "util/pathfinding.h"
#include <queue>
namespace util::pathfinding {
    std::list<Cell*> dijkstraPath(Cell* from, Cell* to, const Squad* squad) {
        typedef std::pair<float, std::pair<Cell*, Cell*>> distanceHeapElem;
        std::priority_queue<distanceHeapElem, std::vector<distanceHeapElem>, std::greater<>> distanceHeap;
        std::map<Cell*, std::pair<float, Cell*>> distance;
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
                std::list<Cell*> ans;
                Cell* curr = to;
                while (curr != from) {
                    ans.push_front(curr);
                    curr = distance[curr].second;
                }
                return ans;
            }
            for (auto t : cell->adjacent) {
                if (distance.find(t) != distance.end()) {
                    continue;
                }
                distanceHeap.push({dist + squad->action->calcSpeed(cell, t), {t, cell}});
            }
        }
        return std::list<Cell*>();
    }
}