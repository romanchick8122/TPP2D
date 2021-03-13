#include "engine/gameController.h"
#include "engine/clickableGameObject.h"
#include "util/cellgen.h"
#include "util/geometry.h"
#include <cmath>
#include "Cell.h"
#include <iostream>
#include "Action.h"

using util::cellGen::Point2D;
class cell : public engine::clickableGameObject {
private:
    sf::ConvexShape shape;
    std::vector<Point2D> vertices;
    int a;
    int b;
    int c;
    int delta;
    bool isSelected;
    sf::FloatRect renderEdges;
public:
    cell(const util::cellGen::CellData& k) : vertices(k.vertices.begin(), k.vertices.end()), shape(k.vertices.size()) {
        a = rand() % 256;
        b = rand() % 256;
        c = rand() % 256;
        for (int i = 0; i < vertices.size(); ++i) {
            shape.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
        }
        shape.setFillColor(sf::Color(a, b, c));

        renderEdges = shape.getLocalBounds();
        isSelected = false;
        delta = 0;
    }
    void tick() override {
        delta += 4;
    }
    void lateTick() override {

    }
    void render(const engine::renderParams& params) override {
        shape.setOrigin(params.origin);
        shape.setScale(params.scale, params.scale);
        shape.setOutlineColor(sf::Color(127, 127, 127));
        if (isSelected) {
#define buka(x) std::abs((delta % (2 * (255 - x))) - (255 - x))
            shape.setFillColor(sf::Color(a + buka(a), b + buka(b), c + buka(c)));
        } else {
            shape.setFillColor(sf::Color(a, b, c));
        }
        params.targetWindow->draw(shape);
    }
    sf::FloatRect getRenderEdges() override {
        return renderEdges;
    }
    bool tryOnClick(sf::Vector2f pos) override {
        if (util::geometry::pointWithin(vertices, util::cellGen::Point2D(pos.x, pos.y))) {
            isSelected ^= true;
        }
        return false;
    }
    sf::FloatRect getClickEdges() override {
        return renderEdges;
    }
};
class AAA {
    std::map<int, int> m;
public:
    const std::map<int, int>* mPtr = &m;
    AAA() {

    }
    void set() {
        std::map<int, int> m2 = {{8,2}, {5,2}, {5532, 53}, {345, 534}, {245, 4235}, {52, 6534}};
        m = m2;
    }
};
int main() {
    engine::gameController controller(1536, 864, "TPP2D", 60);
    auto t = util::cellGen::getMap(Point2D(15360, 8640), 100);
    std::vector<Cell*> cells = makeSurface(t);
    Squad squad(cells[3]);
    float sp = squad.action->calcSpeed(cells[20], cells[21]);
    for (auto ob : t) {
        controller.registerObject(new cell(*ob));
    }
    controller.gameLoop();
    return 0;
}
