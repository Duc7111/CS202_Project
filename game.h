#pragma once
#include <SFML/Graphics.hpp>
#include "animal.h"
#include "vehicle.h"
#include "people.h"
#include "road.h"
#include "world.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>

#pragma once

#define LEVEL_MAX 5

extern std::vector<CVEHICLE*> generatedVehicles;


const float roadOffset = 175;

using namespace std;
class CGAME
{
private:
	unsigned short level;
	vector<CVEHICLE*> arrVehicle;
	vector<CANIMAL*> arrAnimal;
	CPEOPLE cn;
public:
	CGAME(); //Chuẩn bị dữ liệu cho tất cả các đối tượng
	void drawGame(); //Thực hiện vẽ trò chơi ra màn hình sau khi có dữ liệu
	~CGAME(); // Hủy tài nguyên đã cấp phát
	CPEOPLE getPeople();//Lấy thông tin người
	vector<CVEHICLE*> getVehicle();//Lấy danh sách các xe
	vector<CANIMAL*> getAnimal(); //Lấy danh sách các thú
	void resetGame(); // Thực hiện thiết lập lại toàn bộ dữ liệu như lúc đầu
	void exitGame(HANDLE); // Thực hiện thoát Thread
	void startGame(); // Thực hiện bắt đầu vào trò chơi
	void saveGame(std::ofstream& ofs, const sf::RenderWindow& window, const CPEOPLE& player, const WORLD& world);
	void loadGame(std::ifstream& ifs, sf::RenderWindow& window, CPEOPLE& player, WORLD& world);
	void pauseGame(sf::RenderWindow& gameWindow, const CPEOPLE& player, const WORLD& world); // Tạm dừng Thread
	void gameLose(sf::RenderWindow& window);

	//void resumeGame(); //Quay lai Thread

	static sf::Texture carTexture;
	static sf::Texture truckTexture;
	static sf::Image carImage;
	static sf::Image truckImage;

	static sf::Texture catTexture;
	static sf::Texture elephantTexture;
	static sf::Image catImage;
	static sf::Image elephantImage;

	static sf::Texture bgTexture;
	static std::vector<sf::Sprite> bgs;

	static int score;
	static sf::Text currentScore;

	static sf::Font font;

	static CGAME& singleton() {
		static CGAME instance;
		return instance;
	}

	static sf::Clock clock;

	static sf::View defaultView;
};
const float setX = -1200;
const float speed = 100;
const float timeStep = 1.f / 30.f; //de nhan voi so khung hinh cua may

extern int bgPos;
const int bgOffset = 8300;

extern int YScoreText;

void initializeVehicles();

template <typename T>
void drawObjects(sf::RenderWindow& window, std::vector<T*>& generated) {

	for (int i = 0; i < generated.size(); i++) {
		float newX = generated[i]->getSprite().getPosition().x + (speed * timeStep);
		if (newX >= 1600)
			newX = setX;
		float currentY = generated[i]->getSprite().getPosition().y;
		generated[i]->setPosition(newX, currentY);
	}

	for (int i = 0; i < generated.size(); i++) {
		window.draw(generated[i]->getSprite());
	}
}
void moveWorld(sf::RenderWindow& window, CPEOPLE& player, bool reload = false);
void playGame(sf::RenderWindow& window, bool reload = false, std::string loadPath = "");


//extern ROAD road1, road2, road3, road4;
//extern DIRT dirt1, dirt2, dirt3, dirt4;

void addBg(const CPEOPLE& player, std::vector<sf::Sprite>& bgs); //dung khi di chuyen len
void drawBgs(sf::RenderWindow& window, std::vector<sf::Sprite> bgs);

const float moveOffset = 950;

extern float diffY;

void saveWindow(const sf::RenderWindow& renderWindow, const CPEOPLE& player, const WORLD& world);
void reloadWindow(sf::RenderWindow& window, bool fromGame = true);