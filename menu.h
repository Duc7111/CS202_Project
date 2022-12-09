#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
extern int menu, currentIndex;
#define KEY_UP 0x26
#define KEY_DOWN 0x28
#define KEY_ESC 0x1B
#define ConsoleWidth 1080
void keyHandler(KEY_EVENT_RECORD key);
void eventHandler();
void clrscr(void);
void gotoXY(SHORT x, SHORT y);
SHORT wherex();
SHORT wherey();
void inChuCoMau(SHORT x, SHORT y, WORD color, WORD background, LPSTR str, ...);


class console {
public:
	static HANDLE output;
	static HANDLE input;
};


void gameMenu(short index);

void graphicalMenu(sf::RenderWindow& window);

extern sf::Texture play, highScore, load;