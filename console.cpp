
#include <windows.h>
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#define _WIN32_WINNT 1537
#endif
#include <WinCon.h>
#include <iostream>
#include <conio.h> 
#include "myconsole.h"
using namespace std;


//this function outputs a string str at position (x,y) of the screen 
void OutputString(int x, int y, char* str)
{
	COORD c;
	c.X = x;
	c.Y = y;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, c);
	cout << str;
	cout.flush();
}

//this function will clear the screen
void ClearScreen()
{
	CONSOLE_SCREEN_BUFFER_INFO info;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(h, &info);
	system("cls");
	SetConsoleCursorPosition(h, info.dwCursorPosition);

}

void PlaceCursor(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, c);
}


unsigned int CheckWhichKeyPressed(bool& specialKey, int waitTime)
{
	HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD r;
	DWORD w = 1;
	DWORD eventss;
	DWORD waitResult = 0;
	int keypressed = false;
	int toReturn = 0;

	waitResult = WaitForSingleObject(h, waitTime);

	if (waitResult == WAIT_OBJECT_0)
	{
		//FlushConsoleInputBuffer(h);..commented out as this takes to asynchronous mode on some systems
		keypressed = ReadConsoleInput(h, &r, 1, &eventss);

		if (keypressed && r.EventType == KEY_EVENT && r.Event.KeyEvent.bKeyDown)
		{
			toReturn = r.Event.KeyEvent.wVirtualKeyCode;

			if (r.Event.KeyEvent.uChar.AsciiChar)
			{
				toReturn = r.Event.KeyEvent.uChar.AsciiChar;
				specialKey = false;
			}
			else
				specialKey = true;

		}
		//this should make sure that checkKeyPressed is not called twice for arrow keys
		if (toReturn == 224)
			toReturn = CheckWhichKeyPressed(specialKey, waitTime);


		FlushConsoleInputBuffer(h);
	}
	return toReturn;
}
void GetMaxWindowSize(int& maxHorizontal, int& maxVertical)
{
	COORD c;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	c = GetLargestConsoleWindowSize(h);
	maxHorizontal = c.X;
	maxVertical = c.Y;
}

//set the title of the window
void SetWindowTitle(char Title[])
{
	//SetConsoleTitle(Title);
}


void GetMaxWindowCoordinates(int& x, int& y)
{
	CONSOLE_SCREEN_BUFFER_INFO info;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(h, &info);
	x = info.srWindow.Right;
	y = info.srWindow.Bottom;
}
//won't set for more than a certain height and certain width, depending
//upon your system
void SetWindowSize(int width, int height)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	bool bAbs = true;
	SMALL_RECT r;

	r.Left = 0;
	r.Top = 0;
	r.Right = width;
	r.Bottom = height;

	SetConsoleWindowInfo(h, bAbs, &r);
}
void maximized()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
}
//changes the color of a certain co-ordinate
//color can be input using a combination of foreground and Back grounfd Color and | operator
bool SetColorAtPoint(int x, int y, int color)
{
	COORD c, size;
	c.X = x;
	c.Y = y;
	size.X = 1;
	size.Y = 1;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD w = color;
	unsigned long written = 0;
	WriteConsoleOutputAttribute(h, &w, 1, c, &written);

	if (written)
		return true;

	return false;
}

void cls()
{
	COORD coordScreen = { 0, 0 };    // home for the cursor
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!GetConsoleScreenBufferInfo(consoleHandle, &csbi))
	{
		return;
	}

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	FillConsoleOutputCharacter(consoleHandle,        // Handle to console screen buffer
		(TCHAR) ' ',          // Character to write to the buffer
		dwConSize,            // Number of cells to write
		coordScreen,          // Coordinates of first cell
		&cCharsWritten);     // Receive number of characters written

}

void delay(int ms)
{
	Sleep(ms);
}

char getKey()
{
	HANDLE consoleHandle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD size = 1;
	INPUT_RECORD input[1];
	DWORD events = 0;
	char key = '\0';

	if (PeekConsoleInput(consoleHandle, input, size, &events)) {
		if (input[0].EventType == KEY_EVENT) {
			key = input[0].Event.KeyEvent.uChar.AsciiChar;
			FlushConsoleInputBuffer(consoleHandle);
			return key;
		}
	}

	return key; // returns NULL if no input event recorded
}

void getWindowDimensions(int& width, int& height)
{
	HWND consoleHandle = GetConsoleWindow();
	RECT rc;
	GetClientRect(consoleHandle, &rc);
	width = rc.right;
	height = rc.bottom;
}

void getConsoleWindowDimensions(int& width, int& height)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (!GetConsoleScreenBufferInfo(consoleHandle, &csbi)) {
		return;
	}

	width = csbi.srWindow.Right;
	height = csbi.srWindow.Bottom;
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void showConsoleCursor(bool flag)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = flag; // show or hide if flag is true or false respectively
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

//#endif /* MYGRAPHICS_H_ */
