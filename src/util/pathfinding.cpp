#include "util/pathfinding.h"
#include "engine/gameController.h"
#include <queue>
namespace util::pathfinding {
    std::list<Cell*> dijkstraPath(Cell* from, Cell* to, const Squads::Squad* squad) {
        typedef std::pair<float, std::pair<size_t , size_t>> distanceHeapElem;
        std::priority_queue<distanceHeapElem, std::vector<distanceHeapElem>, std::greater<>> distanceHeap;
        std::map<size_t, std::pair<float, size_t>> distance;
        distanceHeap.push({0, {from->id, std::numeric_limits<size_t>::max()}});
        while (!distanceHeap.empty()) {
            auto [dist, cpPair] = distanceHeap.top();
            auto [cell, prev] = cpPair;
            distanceHeap.pop();
            if (distance.find(cell) != distance.end()) {
                continue;
            }
            distance[cell] = {dist, prev};
            if (cell == to->id) {
                std::list<Cell*> ans;
                Cell* curr = to;
                while (curr != from) {
                    ans.push_front(curr);
                    curr = dynamic_cast<Cell*>(
                        engine::gameController::Instance()->networkManager.getShared(distance[curr->id].second));
                }
                return ans;
            }
            Cell* ccell = dynamic_cast<Cell*>(engine::gameController::Instance()->networkManager.getShared(cell));
            for (auto t : ccell->adjacent) {
                if (distance.find(t->id) != distance.end()) {
                    continue;
                }
                distanceHeap.push({dist + squad->action->calcSpeed(ccell, t), {t->id, cell}});
            }
        }
        return std::list<Cell*>();
    }
}
