#include "graphics.h"
#include "vehicle.h"
#include "game.h"
#include <iostream>
#include "menu.h"
#include "highScore.h"
#include "settings.h"

int main(int argc, char** argv[]) {
	srand(time(0));

	readHighScore();
	CGAME::bgTexture.loadFromFile("bg.png");
	//them may cai event handler o day
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	loadTextureOfSettings();
	TREE::loadTexture();

	sf::RenderWindow window(sf::VideoMode(1280, 700), "PROJECT CS202", sf::Style::Titlebar | sf::Style::Close);
	graphicalMenu(window);
	/*gameMenu(0);*/

	return 0;
}