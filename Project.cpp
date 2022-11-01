
#include "graphics.h"
#include "vehicle.h"

void main(int argc, char** argv[]) {
    sf::RenderWindow window(sf::VideoMode(1020, 680),
        "Bouncing car.");


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        car.setPosition(sf::Vector2f(300.f, 250.f));

        window.clear(sf::Color(16, 16, 16, 255)); // Dark gray.
        window.draw(car); // Drawing our sprite.
        window.display();
    }
}