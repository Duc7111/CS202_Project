#include "game.h"
#include "effect.h"
#include "audio.h"
#include "menu.h"
#include "highScore.h"
#include <chrono>
#include <thread>

sf::Texture CGAME::carTexture;
sf::Texture CGAME::truckTexture;
sf::Image CGAME::carImage;
sf::Image CGAME::truckImage;

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
	if (b) return new CELEPHANT;
	else return new CCAT;
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

//void CGAME::loadGame()
//{
//	std::cout << "Please input the path to load game file: ";
//	std::string path;
//	std::cin >> path;
//	std::ifstream fin;
//	fin.open(path);
//	resetGame();
//	//level
//	fin.read((char*)&level, sizeof(level));
//	//Obtacles (vehicle & animal)
//	int n;
//	fin.read((char*)&n, sizeof(int));
//	arrVehicle.resize(n);
//	for (CVEHICLE* p : arrVehicle)
//	{
//		bool t;
//		fin.read((char*)&t, sizeof(bool));
//		p = makeVehicle(t);
//	}
//
//	fin.read((char*)&n, sizeof(int));
//	arrVehicle.resize(n);
//	for (CVEHICLE* p : arrVehicle)
//	{
//		bool t;
//		fin.read((char*)&t, sizeof(bool));
//		p = makeVehicle(t);
//	}
//	//People
//	fin.read((char*)&cn, sizeof(cn));
//
//	fin.close();
//}
//
//void CGAME::saveGame() {
//	std::cout << "Please input the path to save game file: ";
//	std::string path;
//	std::cin >> path;
//	std::ofstream fout;
//	fout.open(path);
//
//	//Level
//	fout.write((char*)&level, sizeof(level));
//	//Obstacle
//	int n = arrVehicle.size();
//	fout.write((char*)&n, sizeof(int));
//	for (CVEHICLE* p : arrVehicle)
//	{
//		bool b = typeid(*p) == typeid(CTRUCK);
//		fout.write((char*)&b, sizeof(b));
//		if (b) fout.write((char*)p, sizeof(CTRUCK));
//		else fout.write((char*)p, sizeof(CVEHICLE));
//	}
//	for (CANIMAL* p : arrAnimal)
//	{
//		bool b = typeid(*p) == typeid(CELEPHANT);
//		fout.write((char*)&b, sizeof(b));
//		if (b) fout.write((char*)p, sizeof(CELEPHANT));
//		else fout.write((char*)p, sizeof(CCAT));
//	}
//	//People
//	fout.write((char*)&cn, sizeof(cn));
//
//	fout.close();
//}
void CGAME::gameLose(sf::RenderWindow& window) {
	float diffY;
	diffY = window.getView().getCenter().y - 610;
	diffY = abs(diffY);


	compareHighScore(CGAME::score);
	window.setTitle("Game over");

	sf::Font font;
	font.loadFromFile("RubikGemstones-Regular.ttf");

	sf::Text finalScore;
	finalScore.setFont(font);
	finalScore.setString("FINAL SCORE: " + to_string(CGAME::score));

	finalScore.setFillColor(sf::Color::White);

	finalScore.setCharacterSize(50);
	finalScore.setStyle(sf::Text::Bold);

	finalScore.setPosition(450, 420 - diffY);

	sf::Sprite bgSprite(CGAME::bgTexture);
	bgSprite.setScale(1300, 1300);
	bgSprite.setPosition(-100, 0 - diffY);

	sf::Texture roadTexture;
	roadTexture.loadFromFile("road2.png");
	sf::Sprite roadSprite(roadTexture);
	roadSprite.setPosition(0, 400 - diffY);
	float scale = (float)M_CELL / (roadSprite.getTexture()->getSize().y);
	roadSprite.setScale(sf::Vector2f(scale, scale));



	sf::Text option;
	sf::Font font2;
	font2.loadFromFile("SecularOne-Regular.ttf");
	option.setString("Play again");
	option.setFont(font2);
	option.setCharacterSize(50);
	option.setPosition(450, 600 - diffY);

	sf::Text option2(option);
	option2.setString("Quit game");
	option2.setPosition(450, 700 - diffY);

	sf::Text arrow(option);
	arrow.setString("-");
	arrow.setPosition(350, 600 - diffY);

	int index = 0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Key::W:
					if (index == 0)
						index = 1;
					else
						index--;
					break;
				case sf::Keyboard::Key::S:
					if (index == 1)
						index = 0;
					else
						index++;
					break;
				case sf::Keyboard::Key::Enter: {
					switch (index) {
					case 0:
						playGame(window);
						break;
					case 1:
						exit(0);
						break;
					}
					break;
				}
				default:
					break;
				}

			}
		}
		option.setFillColor(sf::Color::White);
		option.setStyle(sf::Text::Regular);
		option2.setFillColor(sf::Color::White);
		option2.setStyle(sf::Text::Regular);
		if (index == 0) {
			option.setFillColor(sf::Color::Yellow);
			option.setStyle(sf::Text::Underlined);
		}
		else {
			option2.setFillColor(sf::Color::Yellow);
			option2.setStyle(sf::Text::Underlined);
		}
		arrow.setPosition(350, 600 + 100 * index - diffY);
		arrow.setFillColor(sf::Color::Yellow);

		window.clear();

		window.draw(bgSprite);
		window.draw(roadSprite);
		window.draw(finalScore);
		window.draw(arrow);
		window.draw(option);
		window.draw(option2);

		window.display();
	}
}
sf::Clock CGAME::clock;
//Continnue when game is good designed
void CGAME::pauseGame(sf::RenderWindow& renderWindow, const CPEOPLE& player, const WORLD& world)
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
			switch (i)
			{
			case 0:
				window.close();
				break;
			case 1: {
				/*CGAME::singleton().saveGame();*/
				saveGame(renderWindow, player, world);
				window.close();
				break;
			}

			case 2:
				//cho nay quay ve menu
				/*graphicalMenu(renderWindow);*/
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

void moveWorld(sf::RenderWindow& window, CPEOPLE& player) {
	sf::View view = window.getView();
	sf::Vector2i position = player.getPosition();
	unsigned int direction = player.getDirection();
	bool noMove = false; //khong di chuyen camera
	if (player.getDirection() == 3 || player.getDirection() == 4)
		noMove = true;

	int y = player.getPosition().y;

	//if (y > 0 && y % 15 == 0 && !player.reinitializedVehicle) {
	//	//se co ktra di len di xuong de chon y phu hop
	//	if (player.getDirection() == 1) { //di len
	//		YCar -= moveOffset;
	//		YTruck -= moveOffset;
	//		addBg(player, CGAME::bgs);
	//	}
	//	else if (player.getDirection() == 2) {
	//		YCar += moveOffset;
	//		YTruck += moveOffset;
	//	}

	//	//player.reinitializedVehicle = true; //ngan khong cho dang dung no cu di chuyen duong
	//	//initializeVehicles();

	//}
	////else if (y % 15 != 0)
	////	//player.reinitializedVehicle = false;

	window.clear();
	//std::cout << player.getPosition().x << " " << player.getPosition().y << "\n";
	std::cout << player.getPositionInWorld().x << " ";
	std::cout << player.getPositionInWorld().y << "\n";
	if (!noMove) {
		view.setCenter(sf::Vector2f(view.getCenter().x, player.getPositionInWorld().y));
	}
	window.setView(view);
}

void initializeVehicles() { //de tao xe, va dung cap nhat vi tri xe khi di len
	generatedVehicles.clear();//xoa vector di, trong truong hop cap nhat vi tri

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

	for (int i = 0; i < 12; i++) {
		CVEHICLE* temp;
		if (i < 6) {
			temp = new CCAR;
		}
		else {
			temp = new CTRUCK;
		}
		generatedVehicles.push_back(temp);
		generatedVehicles[12 + i]->loadTextureForeground(-600 * (i < 6 ? i : i - 6) + 400);
	}
	//se co mot cai de tao xe va duong o bg phu nua

}

std::vector<CVEHICLE*> generatedVehicles;
int YScoreText = 300;
sf::Texture CGAME::catTexture;
sf::Texture CGAME::elephantTexture;
sf::Image CGAME::catImage;
sf::Image CGAME::elephantImage;

void playGame(sf::RenderWindow& window, bool reload) {

	sf::Clock clock;
	sf::Time elapsed;

	explosion::loadTexture();
	audio::loadSound();

	CGAME::carTexture.loadFromFile("car.png");
	CGAME::truckTexture.loadFromFile("truck.png");//load texture
	CGAME::carImage = CGAME::carTexture.copyToImage();
	CGAME::truckImage = CGAME::truckTexture.copyToImage();

	CGAME::catTexture.loadFromFile("cat.png");
	CGAME::elephantTexture.loadFromFile("elephant.png");//load texture
	CGAME::catImage = CGAME::catTexture.copyToImage();
	CGAME::elephantImage = CGAME::elephantTexture.copyToImage();

	//initializeVehicles();

	//
	CPEOPLE player;
	player.loadTexture();

	CGAME::font.loadFromFile("ZenDots-Regular.ttf");
	CGAME::currentScore.setFont(CGAME::font);
	CGAME::currentScore.setCharacterSize(45);
	CGAME::currentScore.setPosition(100, player.getPositionInWorld().y - YScoreText);

	VehicleRoad::loadTexture();
	AnimalRoad::loadTexture();

	CGAME::bgTexture.loadFromFile("bg.png");
	sf::Sprite bg(CGAME::bgTexture);
	bg.setScale(1300, 1300);
	bg.setPosition(-100, 0);
	sf::Sprite bg2(bg); //de keo len trong moveWorld
	bg2.setPosition(-100, bgPos -= bgOffset);
	CGAME::bgs.push_back(bg);
	CGAME::bgs.push_back(bg2);

	WORLD world;
	if (reload)
		CGAME::singleton().loadGame(window, player, world);
	else if (!reload)
		world.createWorld(window);





	const sf::Time update_ms = sf::seconds(1.f / 30.f);

	//window.setFramerateLimit(60);

	while (window.isOpen()) {
		CGAME::currentScore.setString(std::to_string(CGAME::score)); //hien thi diem
		//std::cout << player.drawPosition(15, 0).y << " "; //680
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Key::W:
					if (player.goUp()) break;
					audio::playMove();
					world.forward();
					break;
				case sf::Keyboard::Key::S:
					if (world.backward()) {
						if (player.goDown()) break;
					}
					audio::playMove();
					break;
				case sf::Keyboard::Key::A:
					if (player.goLeft()) break;
					audio::playMove();
					break;
				case sf::Keyboard::Key::D:
					if (player.goRight()) break;
					audio::playMove();
					break;
				case sf::Keyboard::Key::Escape:
					CGAME::singleton().pauseGame(window, player, world);
					break;
				default:
					break;
				}
			}
		}
		CGAME::currentScore.setPosition(100, player.getPositionInWorld().y - YScoreText);
		moveWorld(window, player);

		window.clear();

		window.draw(bg);

		drawBgs(window, CGAME::bgs);

		world.drawWorld(window);

		player.drawPlayer(window);

		world.checkCollide(window, player); //ktra va chạm

		window.display();
	}

	for (int i = 0; i < generatedVehicles.size(); i++)
		delete generatedVehicles[i];
}

sf::Font CGAME::font;
sf::Text CGAME::currentScore;
int CGAME::score = 0;
int bgPos = 0;
sf::Texture CGAME::bgTexture;
std::vector<sf::Sprite> CGAME::bgs;

void addBg(const CPEOPLE& player, std::vector<sf::Sprite>& bgs) {
	sf::Sprite bgSprite(CGAME::bgTexture);
	bgSprite.setScale(1500, 7000);
	bgSprite.setPosition(sf::Vector2f(-200, bgPos -= bgOffset));
	bgs.push_back(bgSprite);
}

void drawBgs(sf::RenderWindow& window, std::vector<sf::Sprite> bgs) {
	for (int i = 0; i < bgs.size(); i++) {
		window.draw(bgs[i]);
	}

}

void CGAME::saveGame(const sf::RenderWindow& window, const CPEOPLE& player, const WORLD& world) {
	std::ofstream ofs("game.bin", std::ios::binary);

	if (!ofs)
		return;

	ofs.write((char*)&CGAME::score, sizeof(CGAME::score));

	int mX = player.getPosition().x;
	int mY = player.getPosition().y;
	ofs.write((char*)&mX, sizeof(mX));
	ofs.write((char*)&mY, sizeof(mY));
	int mDirection = player.getDirection();
	int animation = player.getAnimation();
	ofs.write((char*)&mDirection, sizeof(mDirection));
	ofs.write((char*)&animation, sizeof(animation));

	//save mấy cái của road ngay trước mặt nữa
	for (int i = 0; i < 7; i++) {
		bool isRoad = world.object[i];
		ofs.write((char*)&isRoad, sizeof(isRoad));
		if (!isRoad)
			continue;
		bool isVehicleRoad = world.object[i]->isVehicleRoad;
		ofs.write((char*)&isVehicleRoad, sizeof(isVehicleRoad));
	}

	ofs.close();
}
void CGAME::loadGame(sf::RenderWindow& window, CPEOPLE& player, WORLD& world) {
	std::ifstream ifs("game.bin", std::ios::binary);

	if (!ifs)
		return;

	ifs.read((char*)&CGAME::score, sizeof(int));

	int mX, mY, mDirection, mState, animation;
	ifs.read((char*)&mX, sizeof(int));
	ifs.read((char*)&mY, sizeof(int));
	ifs.read((char*)&mDirection, sizeof(int));
	ifs.read((char*)&animation, sizeof(int));
	player.setPeople(mX, mY, mDirection, animation);
	//de coi lai cai set view player

	for (int i = 0; i < 7; ++i) {
		bool isRoad;
		ifs.read((char*)&isRoad, sizeof(bool));
		if (!isRoad)
		{
			world.object.push_back(nullptr);
			continue;
		}
		bool isVehicleRoad;
		ifs.read((char*)&isVehicleRoad, sizeof(bool));
		Road* temp;
		if (isVehicleRoad)
			temp = new VehicleRoad;
		else
			temp = new AnimalRoad;
		temp->setWindow(&window);
		temp->resetSprite();
		temp->setPosition(i);
		world.object.push_back(temp);
	}

	ifs.close();
}