#include "game.h"
#include "road.h"

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
	gameState gS = CON;
	char input = 0;
	//inputing thread

	while (gS)
	{
		//data controlling
		updatePosPeople(input);
		updatePosAnimal();
		updatePosVehicle();
		//condition check
		//if (cn.isDead()) gS = END;

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

void moveWorld(sf::RenderWindow& window, const CPEOPLE& player) {
	sf::View view = window.getView();
	sf::Vector2i position = player.getPosition();
	unsigned int direction = player.getDirection();
	bool noMove = false; //khong di chuyen camera
	if (player.getDirection() == 3 || player.getDirection() == 4)
		noMove = true;
	switch (player.getDirection()) {
	case 1: {
		view.move(0, -4);
		//thay doi limit di chuyen
	}
	case 2: //di xuong
	{
		if (position.x > 0)
			view.move(0, 4);
		//limit view di xuong luc ban dau
		//thay doi limit di chuyen
		break;
	}
	//queo trai, queo phai khong can di chuyen view
	}

	window.clear();
	if (!noMove) {
		view.setCenter(player.getPositionInWorld());
	}

	window.setView(view);
}

void playGame() {
	sf::RenderWindow window(sf::VideoMode(1240, 720), "PROJECT CS202", sf::Style::Titlebar | sf::Style::Close);

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
		generatedVehicles[i]->loadTexture(-600 * (i < 6 ? i : i - 6) + 400);
	}
	//
	CPEOPLE player;
	ROAD road1, road2;
	player.loadTexture();
	road1.loadTexture(YCar + 50);
	road2.loadTexture(YTruck + 50);

	sf::Texture bgTexture;
	bgTexture.loadFromFile("bg.png");
	sf::Sprite bg(bgTexture);

	bg.setScale(1280, 720);
	bg.setPosition(-100, 0);
	sf::Sprite bg2(bg); //de keo len trong moveWorld
	bg2.setPosition(-100, -1280);

	const sf::Time update_ms = sf::seconds(1.f / 30.f);


	while (window.isOpen()) {

		//std::cout << player.drawPosition(15, 0).y << " "; //680
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Key::W:
					player.goUp();
					break;
				case sf::Keyboard::Key::S:
					player.goDown();
					break;
				case sf::Keyboard::Key::A:
					player.goLeft();
					break;
				case sf::Keyboard::Key::D:
					player.goRight();
					break;
				default:
					break;
				}
			}
		}
		moveWorld(window, player);
		window.clear();

		//camera.setCenter(player.sprite.getPosition());
		//camera.setViewport(sf::FloatRect(0.25f, 0.25, 0.5f, 0.5f));
		//window.setView(camera);

		window.draw(bg);
		window.draw(bg2);
		road1.drawRoad(window);
		road2.drawRoad(window);

		player.drawPlayer(window);

		drawObjects(window, generatedVehicles);


		/*CGAME::current = window.getView();*/


		window.display();
	}
}


