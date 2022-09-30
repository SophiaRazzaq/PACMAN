#ifndef MYGRAPHICS_H
#define MYGRAPHICS_H
#include <windows.h>



void drawLine(int x1, int y1, int x2, int y2, int colour); // draws a line between two points given their x-y coordinates in gray-scale
void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b); // draws a line between two points given their x-y coordinates using RGB colouring
void drawRectangle(int x1, int y1, int x2, int y2, int R, int G, int B); // draws a rectangle using top-left and bottom-right x-y coordinates with a border using RGB colouring
void drawRectangle(int x1, int y1, int x2, int y2, int R, int G, int B, int FR, int FG, int FB); // draws a rectangle using top-left and bottom-right x-y coordinates with separate border and fill colours
void drawEllipse(int x1, int y1, int x2, int y2, int R, int G, int B); // draws a rectangle-bounded ellipse using top-left and bottom-right x-y coordinates with a border using RGB colouring
void drawEllipse(int x1, int y1, int x2, int y2, int R, int G, int B, int FR, int FG, int FB); // draw a rectangle-bounded ellipse using top-left and bottom-right x-y coordinates with separate border and fill colours







void mySetPixel(int x, int y, COLORREF colorVal);
void myLine(int x1, int y1, int x2, int y2, COLORREF lineColor);
void myRect(int x1, int y1, int x2, int y2, COLORREF lineColor, COLORREF fillColor);
void myEllipse(int x1, int y1, int x2, int y2, COLORREF colorForeground, COLORREF colorBackground);
void myDrawText(int x, int y, int ht, int score, COLORREF lineColor, COLORREF fillColor);
void myDrawTextWithFont(int x, int y, int ht, char str[], COLORREF lineColor, COLORREF fillColor);
void drawboard(char** arr, int row, int col);
void drawline(int x1, int y1, int x2, int y2, int choice);
#endif



