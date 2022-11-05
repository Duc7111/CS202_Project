
#include "graphics.h"
#include "vehicle.h"
#include <iostream>
#include <thread>

void main(int argc, char** argv[]) {
	sf::RenderWindow window(sf::VideoMode(1840, 1250),
		"PROJECT CS202");
	window.setFramerateLimit(30);
	//CCAR car;

	sf::Clock clock;
	sf::Time elapsed;

	//tao xe();
	CCAR newCar;
	CCAR newCar2(-500);
	CCAR newCar3(-1000);
	CCAR newCar4(-1500);
	CCAR newCar5(-2000);
	CCAR newCar6(-2500);
	generatedCars.push_back(newCar);
	generatedCars.push_back(newCar2);
	generatedCars.push_back(newCar3);
	generatedCars.push_back(newCar4);
	generatedCars.push_back(newCar5);
	generatedCars.push_back(newCar6);
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