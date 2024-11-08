#pragma once

#ifndef _BOARDANDCELL_H_
#define _BOARDANDCELL_H_

#include "Console.h"
#include <ctime>
#include <cstdlib>
#include <fstream>

#define WIDTH 8
#define HEIGHT 5

const int NUM = WIDTH * HEIGHT;

struct CELL {		// Structure of a cell on the Board.
    int x, y; 		// Coordinates x and y of a cell on the Board
    char c;		// Upper character that a cell included
    bool isExist = 1, isChosen = 0;  // Check the status of a cell
};



void DrawCell(CELL, int);

void DeleteCell(CELL&);

void Mix_Board(CELL*);	// Mix cells in the Board randomly

CELL* CreateBoard();

void DrawBoard(CELL*);

void deleteBoard(CELL*&);

#endif

