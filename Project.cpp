
#include "graphics.h"
#include "vehicle.h"
#include "game.h"
#include <iostream>
#include <thread>

void main(int argc, char** argv[]) {
	sf::RenderWindow window(sf::VideoMode(1840, 1250),
		"PROJECT CS202");

	sf::Clock clock;
	sf::Time elapsed;

	std::vector<CVEHICLE*> generatedVehicles;


	for (int i = 0; i < 12; i++) {
		if (i < 6) {
			CCAR* tempCar = new CCAR;
			generatedVehicles.push_back(tempCar);
		}
		else {
			CTRUCK* tempTruck = new CTRUCK;
			generatedVehicles.push_back(tempTruck);
		}
		generatedVehicles[i]->loadTexture(-500 * (i < 6 ? i : i - 6));
	}
	//

	const sf::Time update_ms = sf::seconds(1.f / 30.f);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		//std::thread t1(drawObjects<CCAR>, std::ref(window), std::ref(generatedCars));
		//std::thread t2(drawObjects<CTRUCK>, std::ref(window), std::ref(generatedTrucks));
		//t1.join();
		////t2.join();

		drawObjects(window, generatedVehicles);
		//drawObjects(window, generatedTrucks);
		//hien gio chua ve ca 2 duoc, khong dung thread duoc nen co the se ket hop de ve chung trong mot ham tat ca luon
		//de van dung polymorphism

		window.display();
	}
}