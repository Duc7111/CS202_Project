
#include "graphics.h"
#include "vehicle.h"
#include <iostream>
#include <thread>

void main(int argc, char** argv[]) {
	sf::RenderWindow window(sf::VideoMode(1840, 1250),
		"PROJECT CS202");
	//window.setFramerateLimit(30);
	//CCAR car;

	sf::Clock clock;
	sf::Time elapsed;

	//tao xe
	//de lam object pooling sau	
	//de coi con cach nao khong
	CCAR newCar;
	for (int i = 0; i < 6; i++) {
		newCar = CCAR(-500 * i);
		generatedCars.push_back(newCar);
	}

	std::cout << generatedCars.size();

	const sf::Time update_ms = sf::seconds(1.f / 30.f);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		drawCar(window, generatedCars);

		window.display();
	}
}