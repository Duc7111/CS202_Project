
#include "graphics.h"

void main(int argc, char** argv[]) {
    sf::RenderWindow window(sf::VideoMode(640, 480),
        "Bouncing car.");

    sf::Texture carTexture;
    carTexture.loadFromFile("car.png");
    sf::Sprite car(carTexture);
    sf::Vector2u size = carTexture.getSize();
    car.setOrigin(size.x / 2, size.y / 2);
    sf::Vector2f increment(0.4f, 0.4f);
    car.scale(sf::Vector2f(0.25f, 0.25f));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        car.setPosition(sf::Vector2f(250.f, 250.f));

        window.clear(sf::Color(16, 16, 16, 255)); // Dark gray.
        window.draw(car); // Drawing our sprite.
        window.display();
    }
}