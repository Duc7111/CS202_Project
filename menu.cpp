#include "menu.h"
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
