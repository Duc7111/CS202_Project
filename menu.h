#pragma once
#include <Windows.h>
extern int menu, currentIndex;
#define KEY_UP 0x26
#define KEY_DOWN 0x28
#define KEY_ESC 0x1B
void keyHandler(KEY_EVENT_RECORD key);
void eventHandler();
void clrscr(void);
void gotoXY(SHORT x, SHORT y);
SHORT wherex();
SHORT wherey();

class console {
public:
	static HANDLE output;
	static HANDLE input;
};