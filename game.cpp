#include "game.h"
#include "effect.h"
#include "audio.h"
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

void CGAME::loadGame()
{
	std::cout << "Please input the path to load game file: ";
	std::string path;
	std::cin >> path;
	std::ifstream fin;
	fin.open(path);
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

	fin.close();
}

void CGAME::saveGame() {
	std::cout << "Please input the path to save game file: ";
	std::string path;
	std::cin >> path;
	std::ofstream fout;
	fout.open(path);

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
		bool b = typeid(*p) == typeid(CELEPHANT);
		fout.write((char*)&b, sizeof(b));
		if (b) fout.write((char*)p, sizeof(CELEPHANT));
		else fout.write((char*)p, sizeof(CCAT));
	}
	//People
	fout.write((char*)&cn, sizeof(cn));

	fout.close();
}
void gameLose() {

	sf::RenderWindow window(sf::VideoMode(1000, 800), "Game Lose");
	compareHighScore(CGAME::score);
	window.setTitle("Game over");

	sf::Font font1, font2;
	font1.loadFromFile("AlfaSlabOne-Regular.ttf");
	font2.loadFromFile("Prompt-Bold.ttf");

	sf::Text gameOverTitle, finalScore;
	gameOverTitle.setFont(font1);
	finalScore.setFont(font2);
	gameOverTitle.setString("YOU LOST! PRESS ENTER TO EXIT");
	finalScore.setString("Final score: " + to_string(CGAME::score));

	gameOverTitle.setFillColor(sf::Color::Green);
	finalScore.setFillColor(sf::Color::Cyan);

	gameOverTitle.setCharacterSize(50);
	gameOverTitle.setStyle(sf::Text::Bold);
	finalScore.setCharacterSize(50);
	finalScore.setStyle(sf::Text::Bold);

	gameOverTitle.setPosition(300, 100);
	finalScore.setPosition(300, 500);

	sf::Texture bgTexture;
	sf::Sprite bgSprite;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Key::Enter:
					window.close();
					break;

				default:
					break;
				}
			}
		}

		window.clear();


		window.draw(finalScore);
		window.draw(gameOverTitle);

		window.display();
	}
}
//Continnue when game is good designed
void pauseGame()
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
				CGAME::saveGame();
				window.close();
				break;
			}

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

void moveWorld(sf::RenderWindow& window, CPEOPLE& player) {
	sf::View view = window.getView();
	sf::Vector2i position = player.getPosition();
	unsigned int direction = player.getDirection();
	bool noMove = false; //khong di chuyen camera
	if (player.getDirection() == 3 || player.getDirection() == 4)
		noMove = true;

	int y = player.getPosition().y;

	if (y > 0 && y % 15 == 0 && !player.reinitializedVehicle) {
		//se co ktra di len di xuong de chon y phu hop
		if (player.getDirection() == 1) { //di len
			YCar -= moveOffset;
			YTruck -= moveOffset;
			addBg(player, CGAME::bgs);
		}
		else if (player.getDirection() == 2) {
			YCar += moveOffset;
			YTruck += moveOffset;
		}

		player.reinitializedVehicle = true; //ngan khong cho dang dung no cu di chuyen duong
		initializeVehicles();

	}
	else if (y % 15 != 0)
		player.reinitializedVehicle = false;

	window.clear();
	if (!noMove) {
		view.setCenter(sf::Vector2f(view.getCenter().x, player.getPositionInWorld().y));
	}
	//initializeVehicles() //di chuyen len thi tao xe o tren
	//khi di chuyen den mot mY % n nhat dinh thi no se initializeVehicle (phai ktra dang di xuong hay di len)
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

void playGame(sf::RenderWindow& window) {

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


	WORLD world;
	world.createWorld(window);

	CGAME::bgTexture.loadFromFile("bg.png");
	sf::Sprite bg(CGAME::bgTexture);
	bg.setScale(1300, 1300);
	bg.setPosition(-100, 0);
	sf::Sprite bg2(bg); //de keo len trong moveWorld
	bg2.setPosition(-100, bgPos -= bgOffset);
	CGAME::bgs.push_back(bg);
	CGAME::bgs.push_back(bg2);

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
					pauseGame();
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

//void saveGame(const CPEOPLE& player, const WORLD& world) {
//	std::ofstream ofs("game.bin", std::ios::binary);
//
//	if (!ofs)
//		return;
//
//	ofs.write((char*)&CGAME::currentScore, sizeof(CGAME::currentScore));
//	float posX = player.getPositionInWorld().x;
//	ofs.write((char*)&posX, sizeof(posX));
//	float posY = player.getPositionInWorld().y;
//	ofs.write((char*)&posY, sizeof(posY));
//
//	//save mấy cái của road ngay trước mặt nữa
//	for (int i = 0; i < 7; i++) {
//		sf::Vector2f roadPos = world.object[i]->sprite.getPosition();
//		ofs.write((char*)&roadPos.x, sizeof(roadPos.x));
//		ofs.write((char*)&roadPos.y, sizeof(roadPos.y));
//	}
//}
//void loadGame(CPEOPLE& player, WORLD& world) {
//	std::ifstream ifs("game.bin", std::ios::binary);
//
//	if (!ifs)
//		return;
//
//	ifs.read((char*)&CGAME::currentScore, sizeof(int));
//	float posX, posY;
//	ifs.read((char*)&posX, sizeof(float));
//	ifs.read((char*)&posY, sizeof(float));
//	player.getSprite().setPosition(sf::Vector2f(posX, posY));
//
//	for (int i = 0; i < 7; i++) {
//		float x, y;
//		ifs.read((char*)&x, sizeof(float));
//		ifs.read((char*)&y, sizeof(float));
//		world.object[i]->sprite.setPosition({ x,y });
//	}
//}