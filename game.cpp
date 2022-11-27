#include "game.h"

enum gameState { END, CON, PAUSE };

CGAME::CGAME() : level(0)
{
	//Add code if needed
}

CGAME::~CGAME()
{
	for (CVEHICLE* p : arrVehicle) delete p;
	for (CANIMAL* p : arrAnimal) delete p;
}

CPEOPLE CGAME::getPeople()
{
	return cn;
}

vector<CVEHICLE*> CGAME::getVehicle()
{
	return arrVehicle;
}

vector<CANIMAL*> CGAME::getAnimal()
{
	return arrAnimal;
}

void CGAME::resetGame()
{
	level = 0;

	for (CVEHICLE* p : arrVehicle) delete p;
	arrVehicle.clear();

	for (CANIMAL* p : arrAnimal) delete p;
	arrAnimal.clear();
}

void CGAME::exitGame(HANDLE h) //later modify (depend on main)
{

}

CVEHICLE* makeVehicle(bool b)
{
	if (b) return new CTRUCK;
	else return new CCAR;
}

CANIMAL* makeAnimal(bool b)
{
	if (b) return new CDINAUSOR;
	else return new CBIRD;
}

void CGAME::startGame()
{
	//Initialize
	gameState gS;
	char input;
	//inputing thread

	while (gS)
	{
		//data controlling
		updatePosPeople(input);
		updatePosAnimal();
		updatePosVehicle();
		//condition check
		if (cn.isDead())
			gS = END;

		//screen drawing
	}
}

void CGAME::loadGame(ifstream& fin)
{
	resetGame();
	//level
	fin.read((char*)&level, sizeof(level));
	//Obtacles (vehicle & animal)
	int n;
	fin.read((char*)&n, sizeof(int));
	arrVehicle.resize(n);
	for (CVEHICLE* p : arrVehicle)
	{
		bool t;
		fin.read((char*)&t, sizeof(bool));
		p = makeVehicle(t);
	}

	fin.read((char*)&n, sizeof(int));
	arrVehicle.resize(n);
	for (CVEHICLE* p : arrVehicle)
	{
		bool t;
		fin.read((char*)&t, sizeof(bool));
		p = makeVehicle(t);
	}
	//People
	fin.read((char*)&cn, sizeof(cn));
}

void CGAME::saveGame(ofstream& fout)
{
	//Level
	fout.write((char*)&level, sizeof(level));
	//Obstacle
	int n = arrVehicle.size();
	fout.write((char*)&n, sizeof(int));
	for (CVEHICLE* p : arrVehicle)
	{
		bool b = typeid(*p) == typeid(CTRUCK);
		fout.write((char*)&b, sizeof(b));
		if (b) fout.write((char*)p, sizeof(CTRUCK));
		else fout.write((char*)p, sizeof(CVEHICLE));
	}
	for (CANIMAL* p : arrAnimal)
	{
		bool b = typeid(*p) == typeid(CDINAUSOR);
		fout.write((char*)&b, sizeof(b));
		if (b) fout.write((char*)p, sizeof(CDINAUSOR));
		else fout.write((char*)p, sizeof(CBIRD));
	}
	//People
	fout.write((char*)&cn, sizeof(cn));
}
//Continnue when game is good designed
void CGAME::pauseGame(HANDLE)
{

}

void CGAME::resumeGame(HANDLE)
{

}

void CGAME::updatePosPeople(char input)
{

}

void CGAME::updatePosVehicle()
{

}

void CGAME::updatePosAnimal()
{

}

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