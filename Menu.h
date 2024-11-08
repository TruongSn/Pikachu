#pragma once

#ifndef _MENU_H_
#define _MENU_H_

#include "MoveCursor.h"
#include <string>
#include <cstring>
#include <fstream>

void printAnimation(); //Function Animation - color screen with twinkling stars
void printLogo();
void printRectangle(int, int, int, int);	//rectangular frame drawing function
void leaderBoard();
void writeLeaderBoard(Player); //The function reads the file from the leaderboard.txt file to write player information to the table
void getPlayerInfo(Player&);		//get player information
void helpScreen();
int mainMenu();
void DisplayStatus(bool);	//function prints win or loss status
void Play_Mode(Player&);	//The function sets the state of whether or not the player wants to continue playing, when the player wins

#endif