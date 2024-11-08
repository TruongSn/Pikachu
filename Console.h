#pragma once

#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;


struct Player {
    string name = "", ID = "", Class = "";
    int Score, Life, Suggestion;
};

// COLOR CODE

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GREY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15


#define MOVE_SOUND 0
#define ENTER_SOUND 1
#define ERROR_SOUND 2
#define PLACED_SOUND 3
#define WIN_SOUND 4
#define BACKGROUND_SOUND 5
#define EFFECT_SOUND 6
#define LOSE_SOUND 7

void hideScrollBar(); //  Scrollbar hidden function

void showCursor(bool);	// Hide / show cursor function

void resizeWindow(int, int); // Console screen resizing function

void initWindow(int, int); // Console screen placement function

void setAndCenterWindow();	// Centering function and setting up the console screen

void gotoxy(int, int); // The function moves the cursor to the coordinates (x,y)

void Background_Text_Color(int, int); // Background and text color settings function

void Text_Color(int); // The function only sets the color for text

void playSound(int); // Audio settings function

#endif
