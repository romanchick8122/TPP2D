#include "util/cellgen.h"
#include "SFML/Graphics.hpp"
using util::cellGen::Point2D;
int main()
{
    sf::RenderWindow window(sf::VideoMode(1536, 864), "TPP2D");
    auto t = util::cellGen::getMap(Point2D(1536, 864), 3);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        int a = 0, b = 0, c = 0;
        for (auto &u : t) {
            a = (a + 17) % 256;
            b = (b + 213) % 256;
            c = (c + 123) % 256;
            sf::ConvexShape cell(u->vertices.size());
            for (int i = 0; i < u->vertices.size(); ++i) {
                cell.setPoint(i, sf::Vector2f(u->vertices[i].x, u->vertices[i].y));
            }
            cell.setFillColor(sf::Color(a, b, c));
            window.draw(cell);
        }
        for (auto &u : t) {
            for (auto &n : u->adjacent) {
                if (n > u) {
                    continue;
                }
                sf::VertexArray line(sf::Lines, 2);
                line[0].position = sf::Vector2f(u->center.x, u->center.y);
                line[1].position = sf::Vector2f(n->center.x, n->center.y);
                line[0].color = line[1].color = sf::Color::Black;
                window.draw(line);
            }
        }
        window.display();
    }
    return 0;
}