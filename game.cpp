#include "game.h"
#include "road.h"

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
	//inputing thread

	while (false)
	{
		//data controlling
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
void CGAME::pauseGame()
{
	sf::RenderWindow window(sf::VideoMode(400, 200), "Pause screen", sf::Style::None);
	bool moveInput[2] = { 1,1 };
	sf::Font font;
	if (!font.loadFromFile("ARLRDBD.TTF")) exit(0);
	sf::Text Title, opt[3];
	Title.setFont(font); 
	Title.setStyle(sf::Text::Bold);
	Title.setString("PAUSE");
	Title.setCharacterSize(50);

	opt[0].setFont(font);
	opt[0].setString("Continue");
	opt[0].setCharacterSize(30);
	opt[0].setPosition(sf::Vector2f(0.f, 60.f));
	opt[0].setStyle(sf::Text::Underlined);

	opt[1].setFont(font);
	opt[1].setString("Save");
	opt[1].setCharacterSize(30);
	opt[1].setPosition(sf::Vector2f(0.f, 100.f));

	opt[2].setFont(font);
	opt[2].setString("Quit");
	opt[2].setCharacterSize(30);
	opt[2].setPosition(sf::Vector2f(0.f, 140.f));
	int i = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
			if (event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					moveInput[0] = true;
					break;

				case sf::Keyboard::Down:
					moveInput[1] = true;
					break;

				default:
					break;
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && moveInput[0])
		{
			if (i > 0)
			{
				opt[i].setStyle(sf::Text::Regular);
				opt[--i].setStyle(sf::Text::Underlined);
			}
			moveInput[0] = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && moveInput[1])
		{
			if (i < 2)
			{
				opt[i].setStyle(sf::Text::Regular);
				opt[++i].setStyle(sf::Text::Underlined);
			}
			moveInput[1] = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			switch(i)
			{
			case 0:
				window.close();
				break;
			case 1:
				//saving functions...
				window.close();
				break;
			case 2:
				//return something, modify later
				window.close();
				break;
			}
		window.clear();
		window.draw(Title);
		window.draw(opt[0]);
		window.draw(opt[1]);
		window.draw(opt[2]);
		window.display();
	}
}

void moveWorld(sf::RenderWindow& window, const CPEOPLE& player) {
	sf::View view = window.getView();
	sf::Vector2i position = player.getPosition();
	unsigned int direction = player.getDirection();
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
	view.setCenter(player.getPositionInWorld());
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
				case sf::Keyboard::Key::Escape:
					CGAME::pauseGame();
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


