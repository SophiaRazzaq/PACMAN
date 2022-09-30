#pragma once
#ifndef MYCONSOLE_H
#define MYCONSOLE_H
//this function outputs a string str at position (x,y) of the screen 
void OutputString(int x, int y, char* str);
//this function will clear the screen
void ClearScreen();
//this function is an alternative to ClearScreen(), when ClearScreen() does not work on windows 7
void ClearScreen1();
//this function will place the cursor at a certain position on the screen
void PlaceCursor(int x, int y);
unsigned int CheckWhichKeyPressed(bool& specialKey, int waitTime = 20);
void SetWindowSize(int width, int height);
bool SetColorAtPoint(int x, int y, int color);
//set the title of the window
void SetWindowTitle(char Title[]);
//will get the maximum and minimum x and y coordinates of the current window
void GetMaxWindowCoordinates(int& x, int& y);
void GetMaxWindowSize(int& maxHorizontal, int& maxVertical);
void maximized();
void cls(); // clears the screen
void delay(int ms); // waits for some time (in milli-seconds)
char getKey(); // gets key typed into the console without waiting for the input
void getWindowDimensions(int& width, int& height); // gets width and height of the window
void getConsoleWindowDimensions(int& width, int& height); // gets width and height of console window (in character mode)
void gotoxy(int x, int y); // sets console cursor on given x-y coordinates
void showConsoleCursor(bool showFlag); // shows or hides the cursor



#endif