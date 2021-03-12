#include "engine/gameController.h"
#include "util/cellgen.h"
#include "GameLogic/Cell.h"
#include "GameLogic/Squad.h"
//#include "GameLogic/Unit.h"
//#include "GameLogic/UnitOrder.h"

using util::cellGen::Point2D;
class cell : public gameObject {
private:
    std::vector<Point2D> vertices;
    int a;
    int b;
    int c;
    std::pair<sf::Vector2f, sf::Vector2f> renderEdges;
public:
    cell(const util::cellGen::CellData& k) : vertices(k.vertices.begin(), k.vertices.end()) {
        a = rand() % 256;
        b = rand() % 256;
        c = rand() % 256;
        renderEdges.first.x = renderEdges.second.x = vertices[0].x;
        renderEdges.first.y = renderEdges.second.y = vertices[0].y;
        for (auto point : vertices) {
            if (point.y < renderEdges.first.y) {
                renderEdges.first.y = point.y;
            }
            if (point.y > renderEdges.second.y) {
                renderEdges.second.y = point.y;
            }
            if (point.x < renderEdges.first.x) {
                renderEdges.first.x = point.x;
            }
            if (point.x > renderEdges.second.x) {
                renderEdges.second.x = point.x;
            }
        }
    }
    void tick() override {

    }
    void lateTick() override {

    }
    void render(const renderParams& params) override {
        sf::ConvexShape shape(vertices.size());
        for (int i = 0; i < vertices.size(); ++i) {
            shape.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
        }
        shape.setFillColor(sf::Color(a, b, c));
        shape.setOrigin(params.origin);
        shape.setScale(params.scale, params.scale);
        params.targetWindow->draw(shape);
    }
    decltype(renderEdges) getRenderEdges() override {
        return renderEdges;
    }
};
int main()
{
    //Cell* c = new Cell();
    //Squad s(c);
    ;
    //s.tick();
    //std::cout << "432";
    gameController controller(1536, 864, "TPP2D", 60);
    auto t = util::cellGen::getMap(Point2D(15360, 8640), 1000);
    for (auto ob : t) {
        controller.registerObject(new cell(*ob));
    }
    controller.gameLoop();
    return 0;
}