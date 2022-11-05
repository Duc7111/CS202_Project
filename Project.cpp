
#include "graphics.h"
#include "vehicle.h"
#include <iostream>
#include <thread>

void main(int argc, char** argv[]) {
	sf::RenderWindow window(sf::VideoMode(1840, 1250),
		"PROJECT CS202");

	//CCAR car;

	sf::Clock clock;
	sf::Time elapsed;

	//generateCar();
	CCAR newCar;
	CCAR newCar2(-500);
	CCAR newCar3(-1000);
	generatedCars.push_back(newCar);
	generatedCars.push_back(newCar2);
	generatedCars.push_back(newCar3);
	std::cout << generatedCars.size();

	const sf::Time update_ms = sf::seconds(1.f / 30.f);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		drawCar(window, clock, elapsed, update_ms, generatedCars);
		/*window.draw(newCar.carSprite);
		window.draw(newCar2.carSprite);*/
		//dat tat ca window draw ke nhau
		/*drawCar(window, clock, elapsed, update_ms, newCar);
		drawCar(window, clock, elapsed, update_ms, newCar2);*/
		//de y neu tao car o ngoai vong lap thi no se chay dc
		/*for (int i=0; i<generatedCars.size(); i++)
		   drawCar(window, clock, elapsed, update_ms,generatedCars[i]);*/
		window.display();
	}
}