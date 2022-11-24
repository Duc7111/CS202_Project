
#include "graphics.h"
#include "vehicle.h"
#include "game.h"
#include <iostream>
#include <thread>
#include "menu.h"

void main(int argc, char** argv[]) {
	//them may cai event handler o day
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	gameMenu(0);
	eventHandler();
}