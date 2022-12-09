#include "game.h"
#include "effect.h"
#include "audio.h"

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
			switch (i)
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

	//road1.loadTexture(YCar + 50);
	//road2.loadTexture(YTruck + 50);
	//road3.loadTexture((YCar - moveOffset - 150) + 50);
	//road4.loadTexture((YTruck - moveOffset - 150) + 50);

	//dirt1.loadTexture((YCar - 300) + 50);
	//dirt2.loadTexture((YCar - 550) + 50);
	//dirt3.loadTexture((YCar - 300 - moveOffset - 50) + 50);
	//dirt4.loadTexture((YCar - 550 - moveOffset - 50) + 50);
	//de tao them 2 lan duong cho background phu nua
}

std::vector<CVEHICLE*> generatedVehicles;
//ROAD road1, road2, road3, road4;
//DIRT dirt1, dirt2, dirt3, dirt4;

void playGame() {
	sf::RenderWindow window(sf::VideoMode(1280, 700), "PROJECT CS202", sf::Style::Titlebar | sf::Style::Close);

	sf::Clock clock;
	sf::Time elapsed;

	explosion::loadTexture();
	audio::loadSound();

	//CGAME::carTexture.loadFromFile("car.png");
	//CGAME::truckTexture.loadFromFile("truck.png");//load texture
	//CGAME::carImage = CGAME::carTexture.copyToImage();
	//CGAME::truckImage = CGAME::truckTexture.copyToImage();

	//initializeVehicles();

	//
	CPEOPLE player;
	player.loadTexture();

	VehicleRoad::loadTexture();
	
	WORLD world;
	world.createWorld(window);

	CGAME::bgTexture.loadFromFile("bg.png");
	sf::Sprite bg(CGAME::bgTexture);
	bg.setScale(1300, bgPos);
	bg.setPosition(-100, 0);
	sf::Sprite bg2(bg); //de keo len trong moveWorld
	bg2.setPosition(-100, bgPos -= bgOffset);
	CGAME::bgs.push_back(bg);
	CGAME::bgs.push_back(bg2);

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
					audio::playMove();
					world.forward();
					break;
				case sf::Keyboard::Key::S:
					player.goDown();
					audio::playMove();
					break;
				case sf::Keyboard::Key::A:
					player.goLeft();
					audio::playMove();
					break;
				case sf::Keyboard::Key::D:
					player.goRight();
					audio::playMove();
					break;
				case sf::Keyboard::Key::Escape:
					CGAME::pauseGame();
					audio::playMove();
					break;
				default:
					break;
				}
			}
		}
		moveWorld(window, player);
		window.clear();
		window.draw(bg);

		drawBgs(window, CGAME::bgs);

		world.drawWorld();
		
		player.drawPlayer(window);

		//int collidedIndex = -1;
		//if (player.collidedWithEnemy(collidedIndex)) {
		//	explosion::animateExplosion(window, generatedVehicles[collidedIndex]->getSprite());
		//}

		//drawObjects(window, generatedVehicles);


		/*CGAME::current = window.getView();*/


		window.display();
	}
}

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