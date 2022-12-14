#include "menu.h"
#include <stdio.h>
#include <string>
#include "settings.h"
#include "game.h"
#include "highScore.h"
int menu, currentIndex;
HANDLE console::input;
HANDLE console::output;
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
	std::string s;
	currentIndex = index;
	s = "1. Play\n";
	LPSTR STRTextMenuChinh = const_cast<char*>(s.c_str());
	inChuCoMau((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 6, 15, ((currentIndex == 0) ? 2 : 0), STRTextMenuChinh);
	s = "2. High score\n";
	STRTextMenuChinh = const_cast<char*>(s.c_str());
	inChuCoMau((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 7, 15, ((currentIndex == 1) ? 2 : 0), STRTextMenuChinh);
	s = "3. Exit\n";
	STRTextMenuChinh = const_cast<char*>(s.c_str());
	inChuCoMau((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 8, 15, ((currentIndex == 2) ? 2 : 0), STRTextMenuChinh);

}

void keyHandler(KEY_EVENT_RECORD key) {
	if (key.bKeyDown) {
		switch (key.wVirtualKeyCode) {
		case KEY_UP: {
			clrscr();
			if (menu == 0) {
				if (currentIndex == 0)
					currentIndex = 2;
				else
					currentIndex--;
				gameMenu(currentIndex);
			}
			break;
		}
		case KEY_DOWN: {
			clrscr();
			if (menu == 0) {
				if (currentIndex == 2)
					currentIndex = 0;
				else
					currentIndex++;
				gameMenu(currentIndex);
			}
			break;
		}
		case '\r': //phim enter
			clrscr();
			if (menu == 0) { //o menu start game
				switch (currentIndex) {
				case 0: { //index 0 
					/*playGame(window);*/
					break;
				}
				case 1: {
					//highScore();
					break;
				}
				case 2: {
					exit(0);
					break;
				}
				}
			}
			break;
		}
	}
}
sf::Texture menuBg;
sf::Texture play, highScore, load;
void graphicalMenu(sf::RenderWindow& window) {
	menuBg.loadFromFile("menu bg.png");
	play.loadFromFile("buttons/play.png");
	highScore.loadFromFile("buttons/highScore.png");
	load.loadFromFile("buttons/load.png");

	sf::Sprite bg(menuBg);
	bg.setScale(2.f, 2.f);

	sf::Sprite playBtn, highScoreBtn, loadBtn;
	playBtn = sf::Sprite(play);
	highScoreBtn = sf::Sprite(highScore);
	loadBtn = sf::Sprite(load);

	playBtn.setPosition(550, 300);
	highScoreBtn.setPosition(450, 400);
	loadBtn.setPosition(650, 400);

	sf::Font font;
	font.loadFromFile("ZenDots-Regular.ttf");
	sf::Text title;
	title.setFont(font);
	title.setString("Crossing Road");
	title.setCharacterSize(65);
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);
	title.setPosition(350, 50);

	while (window.isOpen()) {
		window.draw(bg);

		window.draw(playBtn);
		window.draw(highScoreBtn);
		window.draw(loadBtn);
		window.draw(title);

		if (playBtn.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { //neu bam vao button
				playGame(window);
			}
		}

		if (highScoreBtn.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				viewHighScore();
			}
		}

		if (loadBtn.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				/*Settings::settingsSound(window);*/
			}
		}

		window.display();
	}


}