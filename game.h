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
const float speed = 100;
const float timeStep = 1.f / 30.f; //de nhan voi so khung hinh cua may
template <typename T>
void drawObjects(sf::RenderWindow& window, std::vector<T>& generated) {

	for (int i = 0; i < generated.size(); i++) {
		float newX = generated[i].sprite.getPosition().x + (speed * timeStep);
		if (newX > 1840)
			newX = setX;
		generated[i].sprite.setPosition(newX, Y);
	}

	/*if (newX == 20.f)
		generateCar();*/

	for (int i = 0; i < generated.size(); i++) {
		if (generated[i].sprite.getPosition().x > 1840) {
			generated[i].sprite.setPosition(setX, Y);
		}

	}

	window.clear(sf::Color(16, 16, 16, 255));
	for (T car : generated)
		window.draw(car.sprite);
}

