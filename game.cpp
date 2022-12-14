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

float diffY = 0;
void CGAME::gameLose(sf::RenderWindow& window) {
	CGAME::isLose = true;
	diffY = window.getView().getCenter().y - 610;
	diffY = abs(diffY);


	compareHighScore(CGAME::score);

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

	audio::playLose();

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
				case sf::Keyboard::W:
					moveInput[0] = true;
					break;

				case sf::Keyboard::S:
					moveInput[1] = true;
					break;

				default:
					break;
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && moveInput[0])
		{
			if (i > 0)
			{
				opt[i].setStyle(sf::Text::Regular);
				opt[--i].setStyle(sf::Text::Underlined);
			}
			moveInput[0] = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && moveInput[1])
		{
			if (i < 1)
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
				CGAME::standingTimer.Start();
				window.close();
				break;
			case 1: {
				/*CGAME::singleton().saveGame();*/
				saveWindow(renderWindow, player, world);
				window.close();
				break;
			}

			}
		window.clear();
		window.draw(Title);
		window.draw(opt[0]);
		window.draw(opt[1]);
		window.display();
	}
}

void moveWorld(sf::RenderWindow& window, CPEOPLE& player, bool reload) {
	sf::View view = window.getView();
	sf::Vector2i position = player.getPosition();
	unsigned int direction = player.getDirection();
	bool noMove = false; //khong di chuyen camera
	if (player.getDirection() == 3 || player.getDirection() == 4)
		noMove = true;

	int y = player.getPosition().y;

	//}
	////else if (y % 15 != 0)
	////	//player.reinitializedVehicle = false;

	window.clear();
	//std:://cout << player.getPosition().x << " " << player.getPosition().y << "\n";
	if (reload || !noMove) {
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

bool CGAME::isLose = false;
std::vector<CVEHICLE*> generatedVehicles;
int YScoreText = 300;
sf::Texture CGAME::catTexture;
sf::Texture CGAME::elephantTexture;
sf::Image CGAME::catImage;
sf::Image CGAME::elephantImage;
Timer CGAME::standingTimer;
sf::Text CGAME::standingTime;

void playGame(sf::RenderWindow& window, bool reload, std::string loadPath) {
	CGAME::isLose = false;
	menuSound.stop();

	window.setView(window.getDefaultView());

	//timeCount = 0;
	CGAME::score = 0;
	//sf::Time elapsed;

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
	player.switchCharacter(CPEOPLE::getCharacterIndex());

	CGAME::font.loadFromFile("ZenDots-Regular.ttf");
	CGAME::currentScore.setFont(CGAME::font);
	CGAME::currentScore.setCharacterSize(45);
	CGAME::currentScore.setPosition(100, player.getPositionInWorld().y - YScoreText);

	CGAME::standingTime = sf::Text(CGAME::currentScore);
	CGAME::standingTime.setCharacterSize(40);
	CGAME::standingTime.setPosition(1000, player.getPositionInWorld().y - YScoreText);
	CGAME::standingTime.setFillColor(sf::Color::Red);

	VehicleRoad::loadTexture();
	AnimalRoad::loadTexture();

	BACKGROUND background;

	WORLD world;
	if (reload) {
		std::ifstream ifs(loadPath, std::ios::binary);
		CGAME::singleton().loadGame(ifs, window, player, world, CGAME::remainingTime);
		background.updateOnLoad(world);
	}

	else if (!reload)
		world.createWorld(window);


	const sf::Time update_ms = sf::seconds(1.f / 30.f);
	CGAME::standingTimer.Reset();
	//window.setFramerateLimit(60);

	while (window.isOpen()) {
		CGAME::currentScore.setString(std::to_string(CGAME::score)); //hien thi diem
		CGAME::standingTime.setString(std::to_string(CGAME::remainingTime - (int)CGAME::standingTimer.GetElapsedSeconds()));
		//std:://cout << player.drawPosition(15, 0).y << " "; //680
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Key::W:
					if (player.goUp()) break;
					CGAME::standingTimer.Reset();
					CGAME::remainingTime = 15;
					audio::playMove();
					world.forward();
					background.update(world);
					break;
				case sf::Keyboard::Key::S:
					if (world.backward()) {
						if (player.goDown()) break;
					}
					audio::playMove();
					CGAME::standingTimer.Reset();
					CGAME::remainingTime = 15;
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
					CGAME::standingTimer.Pause();
					CGAME::singleton().pauseGame(window, player, world);
					break;
				case sf::Keyboard::Key::T:
					CGAME::standingTimer.Pause();
					saveWindow(window, player, world);
					break;
				case sf::Keyboard::Key::L:
					CGAME::standingTimer.Pause();
					reloadWindow(window);
					break;
				default:
					break;
				}
			}
		}
		CGAME::currentScore.setPosition(100, player.getPositionInWorld().y - YScoreText);
		CGAME::standingTime.setPosition(1000, player.getPositionInWorld().y - YScoreText);

		moveWorld(window, player);

		window.clear();


		background.draw(window);

		world.drawWorld(window);

		player.draw(window);
		if (CGAME::standingTimer.GetElapsedSeconds() == CGAME::remainingTime - 3)
			audio::clockTicking();
		if (CGAME::standingTimer.GetElapsedSeconds() >= CGAME::remainingTime) //quá thời gian
			CGAME::singleton().gameLose(window);

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

void CGAME::saveGame(std::ofstream& ofs, const sf::RenderWindow& window, const CPEOPLE& player, const WORLD& world) {

	ofs.write((char*)&CGAME::score, sizeof(CGAME::score));
	int timer = CGAME::standingTimer.GetElapsedSeconds();
	ofs.write((char*)&timer, sizeof(timer));

	ofs << player;
	ofs << world;

	ofs.close();
}
void CGAME::loadGame(std::ifstream& ifs, sf::RenderWindow& window, CPEOPLE& player, WORLD& world, int& remainingTime) {
	if (!ifs)
	{
		sf::Font font;
		font.loadFromFile("ZenDots-Regular.ttf");

		sf::Text title;
		title.setFont(font);
		title.setString("File cannot be opened (because it is non-existent, etc.)");
		title.setFillColor(sf::Color::White);
		title.setCharacterSize(35);
		title.setStyle(sf::Text::Bold);
		title.setPosition(50, 220 - diffY);

		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					graphicalMenu(window);
				}

				else if (event.type == sf::Event::KeyPressed)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						graphicalMenu(window);
					}
				}
			}

			window.clear();
			window.draw(title);
			window.display();
		}


	}

	ifs.read((char*)&CGAME::score, sizeof(int));
	int time;
	ifs.read((char*)&time, sizeof(time));
	remainingTime = 15 - time; //thoi gian con lai

	ifs >> player;

	moveWorld(window, player, true); //de lam them cai ktra xem co move hay chua trc do


	inputRoads(ifs, window, world);

	ifs.close();
}
int CGAME::remainingTime = 15;
sf::View CGAME::defaultView;
void saveWindow(const sf::RenderWindow& renderWindow, const CPEOPLE& player, const WORLD& world) {
	sf::RenderWindow window(sf::VideoMode(1280, 700), "Save game", sf::Style::Titlebar | sf::Style::Close);
	window.setView(CGAME::defaultView);

	sf::Font font;
	font.loadFromFile("RubikGemstones-Regular.ttf");

	sf::Text title;
	title.setFont(font);
	title.setString("Please enter path to save your game: ");
	title.setFillColor(sf::Color::White);
	title.setCharacterSize(50);
	title.setStyle(sf::Text::Bold);
	title.setPosition(50, 220);

	sf::Sprite bgSprite(CGAME::bgTexture);
	bgSprite.setScale(1300, 1300);
	bgSprite.setPosition(-100, 0);

	sf::Texture roadTexture;
	roadTexture.loadFromFile("road2.png");
	sf::Sprite roadSprite(roadTexture);
	roadSprite.setPosition(0, 400);
	float scale = (float)M_CELL / (roadSprite.getTexture()->getSize().y);
	roadSprite.setScale(sf::Vector2f(scale, scale));

	std::string inputPath = "";
	sf::Text output;
	output.setPosition(50, 420);
	output.setFont(font);
	output.setCharacterSize(45);
	output.setStyle(sf::Text::Italic);
	output.setString(inputPath);
	output.setFillColor(sf::Color::White);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				CGAME::standingTimer.Start();
				window.close();
			}
			else if (event.type == sf::Event::TextEntered) {
				if (std::isprint(event.text.unicode))
				{
					inputPath += event.text.unicode;

					output.setString(inputPath);
				}
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					std::ofstream ofs(inputPath, std::ios::binary);
					CGAME::singleton().saveGame(ofs, renderWindow, player, world);
					window.close();
					CGAME::standingTimer.Start();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
					if (!inputPath.empty())
						inputPath.pop_back();
					output.setString(inputPath);
				}
			}


		}

		window.clear();

		window.draw(bgSprite);
		window.draw(roadSprite);
		window.draw(title);
		window.draw(output);

		window.setView(CGAME::defaultView);

		window.display();
	}
}
void reloadWindow(sf::RenderWindow& window, bool fromGame) {
	menuSound.stop();
	window.setView(CGAME::defaultView);

	sf::Font font;
	font.loadFromFile("RubikGemstones-Regular.ttf");

	sf::Text title;
	title.setFont(font);
	title.setString("Please enter path to your save game: ");
	title.setFillColor(sf::Color::White);
	title.setCharacterSize(50);
	title.setStyle(sf::Text::Bold);
	title.setPosition(50, 220);

	sf::Sprite bgSprite(CGAME::bgTexture);
	bgSprite.setScale(1300, 1300);
	bgSprite.setPosition(-100, 0);

	sf::Texture roadTexture;
	roadTexture.loadFromFile("road2.png");
	sf::Sprite roadSprite(roadTexture);
	roadSprite.setPosition(0, 400);
	float scale = (float)M_CELL / (roadSprite.getTexture()->getSize().y);
	roadSprite.setScale(sf::Vector2f(scale, scale));

	std::string inputPath = "";

	sf::Text output;
	output.setPosition(50, 420);
	output.setFont(font);
	output.setCharacterSize(45);
	output.setStyle(sf::Text::Italic);
	output.setString(inputPath);
	output.setFillColor(sf::Color::White);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				graphicalMenu(window);
			}
			else if (event.type == sf::Event::TextEntered) {
				if (std::isprint(event.text.unicode))
				{
					if (fromGame)
					{
						fromGame = false;
						continue;
					}
					inputPath += event.text.unicode;

					output.setString(inputPath);
				}
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					playGame(window, true, inputPath);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
					if (!inputPath.empty())
						inputPath.pop_back();
					output.setString(inputPath);
				}
			}


		}

		window.clear();

		window.draw(bgSprite);
		window.draw(roadSprite);
		window.draw(title);
		window.draw(output);

		window.setView(CGAME::defaultView);

		window.display();
	}
}