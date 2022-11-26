#include <SFML/Graphics.hpp>
#include "vehicle.h"
#include "animal.h"
#include "people.h"
#include <Windows.h>
#include <iostream>
#pragma once
using namespace std;
class CGAME {
	CTRUCK* axt;
	CCAR* axh;
	CDINAUSOR* akl;
	CBIRD* ac;
	CPEOPLE cn;
public:
	CGAME(); //Chuẩn bị dữ liệu cho tất cả các đối tượng
	void drawGame(); //Thực hiện vẽ trò chơi ra màn hình sau khi có dữ liệu
	~CGAME(); // Hủy tài nguyên đã cấp phát
	CPEOPLE getPeople();//Lấy thông tin người
	CVEHICLE* getVehicle();//Lấy danh sách các xe
	CANIMAL* getAnimal(); //Lấy danh sách các thú
	void resetGame(); // Thực hiện thiết lập lại toàn bộ dữ liệu như lúc đầu
	void exitGame(HANDLE); // Thực hiện thoát Thread
	void startGame(); // Thực hiện bắt đầu vào trò chơi
	void loadGame(istream); // Thực hiện tải lại trò chơi đã lưu
	void saveGame(istream); // Thực hiện lưu lại dữ liệu trò chơi
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

	window.clear(sf::Color(16, 16, 16, 255)); //do cai cau nay nen mat xe cu

	for (int i = 0; i < generated.size(); i++) {
		window.draw(generated[i]->getSprite());
	}

}

void playGame();
void highScore();