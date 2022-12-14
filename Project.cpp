#include "graphics.h"
#include "vehicle.h"
#include "game.h"
#include <iostream>
//#include <thread>
#include "menu.h"
#include "highScore.h"
#include "settings.h"

int main(int argc, char** argv[]) {
	readHighScore();
	//them may cai event handler o day
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	loadTextureOfSettings();
	sf::RenderWindow window(sf::VideoMode(1280, 700), "PROJECT CS202", sf::Style::Titlebar | sf::Style::Close);
	graphicalMenu(window);
	/*gameMenu(0);*/
	eventHandler();
	return 0;
}