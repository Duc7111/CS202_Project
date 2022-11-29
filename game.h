#include <SFML/Graphics.hpp>
#include "vehicle.h"
#include "animal.h"
#include "people.h"
#include "road.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#pragma once

#define LEVEL_MAX 5

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
	void loadGame(ifstream&); // Thực hiện tải lại trò chơi đã lưu
	void saveGame(ofstream&); // Thực hiện lưu lại dữ liệu trò chơi
	void pauseGame(HANDLE); // Tạm dừng Thread
	void resumeGame(HANDLE); //Quay lai Thread
	void updatePosPeople(char); //Thực hiện điều khiển di chuyển của CPEOPLE
	void updatePosVehicle(); //Thực hiện cho CTRUCK & CCAR di chuyển
	void updatePosAnimal();//Thực hiện cho CDINAUSOR & CBIRD di chuyển

};
const float setX = -1500;
const float speed = 10;
const float timeStep = 1.f / 30.f; //de nhan voi so khung hinh cua may

extern CVEHICLE** vehicles; //mang chua cac loai xe ung dung polymorphism

template <typename T>
void drawObjects(sf::RenderWindow& window, std::vector<T*>& generated) {

	for (int i = 0; i < generated.size(); i++) {
		float newX = generated[i]->getSprite().getPosition().x + (speed * timeStep);
		if (newX > 1400)
			newX = setX;
		float currentY = generated[i]->getSprite().getPosition().y;
		generated[i]->setPosition(newX, currentY);
	}

	for (int i = 0; i < generated.size(); i++) {
		window.draw(generated[i]->getSprite());
	}
	//ROAD newRoad;
	//newRoad.drawRoad(window, YCar + 50);
	//ROAD newRoad2;
	//newRoad2.drawRoad(window, YTruck + 50);
}

void playGame();
void highScore();

void moveWorld(sf::RenderWindow& window, int mDirection);