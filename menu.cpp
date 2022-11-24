#include "menu.h"
#include <stdio.h>
int menu, currentIndex;
void eventHandler()
{
	while (1)
	{
		DWORD DWNumberOfEvents = 0;
		DWORD DWNumberOfEventsRead = 0;

		HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
		GetNumberOfConsoleInputEvents(input, &DWNumberOfEvents);

		if (DWNumberOfEvents)
		{
			INPUT_RECORD* IREventBuffer = new INPUT_RECORD[DWNumberOfEvents];
			ReadConsoleInput(input, IREventBuffer, DWNumberOfEvents, &DWNumberOfEventsRead);

			for (DWORD i = 0; i < DWNumberOfEvents; ++i)
			{
				if (IREventBuffer[i].EventType == KEY_EVENT)
				{
					keyHandler(IREventBuffer[i].Event.KeyEvent);
				}
			}
		}
	}
}
void keyHandler(KEY_EVENT_RECORD key) {
	if (key.bKeyDown) {
		switch (key.wVirtualKeyCode) {
		case KEY_UP:
			clrscr();
			//cho nay la co menu
		}
	}
}

void clrscr(void)
{
	system("CLS");
}


// Ham dich chuyen con tro den toa do x, y.
void gotoXY(SHORT x, SHORT y)
{
	COORD Cursor_an_Pos = { x, y };
	console::output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(console::output, Cursor_an_Pos);
}

// Tra ve vi tri x hien tai.
SHORT wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	console::output = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console::output, &coninfo);
	return coninfo.dwCursorPosition.X;
}

// Tra ve vi tri y hien tai.
SHORT wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	console::output = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console::output, &coninfo);
	return coninfo.dwCursorPosition.Y;
}

void datMauNen(WORD color)
{
	console::output = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(console::output, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4; // Dich trai 3 bit de phu hop voi mau nen
	wAttributes &= 0xff0f; // Cai 0 cho 1 bit chu nhay va 3 bit mau nen
	wAttributes |= color;

	SetConsoleTextAttribute(console::output, wAttributes);
}

void datMau(WORD color)
{
	console::output = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(console::output, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(console::output, wAttributes);
}

WORD textattr()
{
	CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
	GetConsoleScreenBufferInfo(console::output, &ConsoleInfo);
	return ConsoleInfo.wAttributes;
}

void resettextattr()
{
	DWORD Mau_Mac_Dinh = textattr();
	SetConsoleTextAttribute(console::output, Mau_Mac_Dinh);
}

void resettextattr()
{
	DWORD Mau_Mac_Dinh = textattr();
	SetConsoleTextAttribute(console::output, Mau_Mac_Dinh);
}

void inChuCoMau(SHORT x, SHORT y, WORD color, WORD background, LPSTR str, ...)
{
	gotoXY(x, y);
	datMauNen(background);
	datMau(color);

	/*In duoc nhieu chu hon*/
	va_list args;
	va_start(args, str);
	vprintf(str, args);
	va_end(args);
	/*In duoc nhieu chu hon*/

	resettextattr();
	//datMau(7);
}

void gameMenu(short index) {
	clrscr();
	menu = 0;

	LPSTR STRTextMenuChinh = const_cast<char*>(s.c_str());
	inChuCoMau((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 2, 3, 0, STRTextMenuChinh);


	currentIndex = index; //tuong tu tren
	s = "1. Play";
	STRTextMenuChinh = const_cast<char*>(s.c_str());
	inChuCoMau((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 6, 15, ((currentIndex == 0) ? 2 : 0), STRTextMenuChinh);
	s = "2. High score";
	STRTextMenuChinh = const_cast<char*>(s.c_str());
	inChuCoMau((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 7, 15, ((currentIndex == 1) ? 2 : 0), STRTextMenuChinh);
	s = "3. Exit";
	STRTextMenuChinh = const_cast<char*>(s.c_str());
	inChuCoMau((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 8, 15, ((currentIndex == 2) ? 2 : 0), STRTextMenuChinh);

}