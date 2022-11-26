#include "game.h"
void playGame() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "PROJECT CS202", sf::Style::Titlebar | sf::Style::Close);

	sf::Clock clock;
	sf::Time elapsed;

	std::vector<CVEHICLE*> generatedVehicles;


	for (int i = 0; i < 12; i++) {
		CVEHICLE* temp;
		if (i < 6) {
			temp = new CCAR;
		}
		else {
			temp = new CTRUCK;
		}
		generatedVehicles.push_back(temp);
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

		drawObjects(window, generatedVehicles);

		window.display();
	}
}