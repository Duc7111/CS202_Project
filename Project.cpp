
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

	//tao xe
	//de lam object pooling sau	

	//test
	CCAR newCar;
	for (int i = 0; i < 6; i++) {
		generatedCars.push_back(newCar);
	}

	std::vector<CTRUCK> generatedTrucks;
	CTRUCK newTruck;
	for (int i = 0; i < 6; i++) {
		generatedTrucks.push_back(newTruck);
	}

	std::vector<CVEHICLE*> generatedVehicles;
	for (int i = 0; i < 6; i++) {
		generatedVehicles.push_back(&generatedTrucks[i]);
		generatedVehicles[i]->loadTexture(-500 * i);
	}

	for (int i = 0; i < 6; i++) {
		generatedVehicles.push_back(&generatedCars[i]);
		generatedVehicles[6 + i]->loadTexture(-500 * i);
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