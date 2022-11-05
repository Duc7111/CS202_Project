
#include "graphics.h"
#include "vehicle.h"
#include <iostream>

void main(int argc, char** argv[]) {
    sf::RenderWindow window(sf::VideoMode(1366, 768),
        "Bouncing car.");

    //CCAR car;

    sf::Clock clock;
    sf::Time elapsed;

    generateCar();
    CCAR newCar, newCar2;
    std::cout << generatedCars.size();

    const sf::Time update_ms = sf::seconds(1.f / 30.f);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        drawCar(window, clock, elapsed, update_ms, newCar);
        drawCar(window, clock, elapsed, update_ms, newCar2);
        //de y neu tao car o ngoai vong lap thi no se chay dc
        /*for (int i=0; i<generatedCars.size(); i++)
           drawCar(window, clock, elapsed, update_ms,generatedCars[i]);*/
        window.display();
    }
}