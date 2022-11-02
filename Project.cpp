
#include "graphics.h"
#include "vehicle.h"

void main(int argc, char** argv[]) {
    sf::RenderWindow window(sf::VideoMode(1020, 680),
        "Bouncing car.");

    CCAR car;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        //car.setPosition(250.f, 250.f);

        window.clear(sf::Color(16, 16, 16, 255)); // Dark gray.
        generateCar(window);
        //window.draw(car.carSprite); // Drawing our sprite.
        window.display();
    }
}