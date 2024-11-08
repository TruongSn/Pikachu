#pragma once

#ifndef _MOVECURSOR_H_
#define _MOVECURSOR_H_

#include "Check.h"
#include "Menu.h"


#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32 // MIX CELL
#define TAB 9  // SUGGESTION

struct Pos {
    int x, y;
};

void DisplayResultChosen(bool , CELL*, CELL& , CELL& , Player& );      //The function prints out the states when considering 1 pair of cells
void Movement(CELL*& , Player&, int&, Pos [], int [], Pos& , int& );    //controlling the movement of the cursor on a table of squares

#endif