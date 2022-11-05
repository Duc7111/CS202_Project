
#include "graphics.h"
#include "vehicle.h"

void main(int argc, char** argv[]) {
    sf::RenderWindow window(sf::VideoMode(1020, 680),
        "Bouncing car.");

    CCAR car;

    sf::Clock clock;
    sf::Time elapsed;

    const sf::Time update_ms = sf::seconds(1.f / 30.f);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }


        car.moveInWindow(clock,elapsed,update_ms);

        //car.setPosition(250.f, 250.f);

        window.clear(sf::Color(16, 16, 16, 255)); // Dark gray.
        car.drawCar(window);
        //window.draw(car.carSprite); // Drawing our sprite.
        window.display();
    }
}