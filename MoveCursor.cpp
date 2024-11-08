#include "MoveCursor.h"
#include "Menu.h"

using namespace std;

char border[5][12] = {
			{" --------- "},
			{"|         |"},
			{"|         |"},
			{"|         |"},
			{" --------- "}
};


/* The function prints out the states when considering 1 pair of cells */
void DisplayResultChosen(bool result, CELL* cell, CELL& cell1, CELL& cell2, Player& player) {
	if (result == false) {		// If the matching result is wrong

		//mark the 1st and 2nd selection boxes in red
		DrawCell(cell1, LIGHT_RED);		
		DrawCell(cell2, LIGHT_RED);

		Sleep(1000);

		//return white to those 2 boxes
		DrawCell(cell1, WHITE);		
		DrawCell(cell2, WHITE);

		// reducing the life by 1 and the player is deducted 15 points
		player.Life--;
		player.Score -= 15;
	}
	else { // If the matching results are correct

		//mark the 1st and 2nd selection boxes in yellow
		DrawCell(cell1, LIGHT_YELLOW);		
		DrawCell(cell2, LIGHT_YELLOW);

		Sleep(500);

		DeleteCell(cell1);
		DeleteCell(cell2);

		/*DisplayBackground(bg, cell1.x, cell1.y);
		DisplayBackground(bg, cell2.x, cell2.y);*/

		//update the status of the first and 2nd cells and add 20 points to the player
		int X1 = cell1.x + 1, Y1 = cell1.y + 1;
		int X2 = cell2.x + 1, Y2 = cell2.y + 1;
		cell1.isExist = 0;
		cell2.isExist = 0;
		player.Score += 20;
	}

	// Reset the state of the 1st cell and the 2nd cell not selected
	cell1.isChosen = cell2.isChosen = 0; 	
	Text_Color(WHITE);

	// Display player information on the gaming screen and introduce support function keys

	Background_Text_Color(BLACK, WHITE);
	printRectangle(93, 1, 25, 9);
	printRectangle(93, 12, 25, 9);

	printRectangle(94, 2, 23, 2);
	Background_Text_Color(BLACK, AQUA);
	gotoxy(96, 3);
	cout << "PLAYER'S INFORMATION";

	Background_Text_Color(BLACK, LIGHT_YELLOW);
	gotoxy(94, 5);
	
	if (!player.name.empty())
		cout << "Player's name: " << player.name;
	else
		cout << "unknown";


	gotoxy(94, 7);
	if (!player.ID.empty())
		cout << "Student's ID: " << player.ID;
	else
		cout << "unknown";


	gotoxy(94, 9);
	if (!player.Class.empty())
		cout << "Class: " << player.Class;
	else
		cout << "unknown";

	Background_Text_Color(BLACK, WHITE);
	printRectangle(94, 13, 23, 2);
	Background_Text_Color(BLACK, WHITE);
	gotoxy(97, 14);
	cout << "GAME INFORMATION";
	Background_Text_Color(BLACK, WHITE);
	gotoxy(94, 16);
	cout << "Life: ";
	cout << player.Life;
	gotoxy(94, 17);
	cout << "Current score: ";
	cout << player.Score;
	Background_Text_Color(BLACK, WHITE);
	gotoxy(94, 18);
	cout << "Suggestion: " << player.Suggestion;
	Text_Color(WHITE);
	


	Background_Text_Color(BLACK, WHITE);
	printRectangle(93, 23, 23, 2);
	printRectangle(93, 26, 10, 2);
	printRectangle(105, 26, 11, 2);

	Background_Text_Color(BLACK, LIGHT_PURPLE);
	gotoxy(95, 24);
	cout << "TAB: Move suggestion";
	Background_Text_Color(BLACK, LIGHT_GREEN);
	gotoxy(94, 27);
	cout << "SPACE: MIX";
	Background_Text_Color(BLACK, LIGHT_RED);
	gotoxy(106, 27);
	cout << "Esc: Exit";
	Text_Color(WHITE);
}


/*controlling the movement of the cursor on a table of squares*/
void Movement(CELL*& cell, Player& player, int& status, Pos select[], int pos[], Pos& Cursor, int& count) {
	
	//Read a character from the keyboard.
	char c = _getch();

	//the function assigns a value of 2 to the status variable to exit the game and play an error sound
	if (c == ESC) {
		status = 2; // exit game;
		playSound(ERROR_SOUND);
	}
		
	else if (c == ENTER) { // Select O
		playSound(ENTER_SOUND);

		select[count] = Cursor;
		pos[count] = select[count].y * WIDTH + select[count].x;  // The corresponding position of the selected cell in the board
		cell[pos[count]].isChosen = 1;
		count++;
		if (count == 2) {
			bool identical = (cell[pos[0]].x == cell[pos[1]].x) && (cell[pos[0]].y == cell[pos[1]].y);
			if (identical || (cell[pos[0]].c != cell[pos[1]].c)) {
				playSound(ERROR_SOUND);
				DisplayResultChosen(false, cell, cell[pos[0]], cell[pos[1]], player);
			}
			else {
				if (AllCheck(cell, cell[pos[0]], cell[pos[1]])) {
					playSound(PLACED_SOUND);
					DisplayResultChosen(true, cell, cell[pos[0]], cell[pos[1]], player);
				}
					
				else {
					playSound(ERROR_SOUND);
					DisplayResultChosen(false, cell, cell[pos[0]], cell[pos[1]], player);
				}
					
			}
			count = 0;
			select[0] = { -1, -1 };  select[1] = { -1, -1 };
			// Returns the position of the cursor after considering whether the selected 2 cells are true or false
			for (int i = Cursor.y; i < HEIGHT; i++)
				for (int j = Cursor.x; j < WIDTH; j++) {  // From left to right (starting from cursor position)
					if (cell[i * WIDTH + j].isExist) {
						Cursor.x = j;
						Cursor.y = i;
						return;
					}
				}

			for (int i = Cursor.y; i >= 0; i--)   // From right to left (starting from cursor position)
				for (int j = Cursor.x; j >= 0; j--) {
					if (cell[i * WIDTH + j].isExist) {
						Cursor.x = j;
						Cursor.y = i;
						return;
					}
				}
		}
	}

	else {
		if (((Cursor.x != select[0].x) || (Cursor.y != select[0].y)) && ((Cursor.x != select[1].x) || (Cursor.y != select[1].y)))
			cell[Cursor.y * WIDTH + Cursor.x].isChosen = 0;
		switch (c) {
			// Move left 		
		case LEFT:
			playSound(MOVE_SOUND);
			// If left or right, the scrolling position at cursor.x is not considered with y = cursor.y
			  //Consider the fourth quadrant, where the center is the cursor
			for (int y = Cursor.y; y < HEIGHT; y++) 
				for (int x = Cursor.x - 1; x >= 0; x--)
					if (cell[y * WIDTH + x].isExist) {
						Cursor = { x, y };
						return;
					}
			// Consider the third quadrant, where the center is the cursor							
			for (int y = Cursor.y; y < HEIGHT; y++) // Y runs from top to bottom
				for (int x = WIDTH - 1; x > Cursor.x; x--) // x runs from right to left border
					if (cell[y * WIDTH + x].isExist) {
						Cursor = { x, y };
						return;
					}
			// Consider the first quadrant	
			for (int y = Cursor.y + 1; y >= 0; y--)
				for (int x = Cursor.x - 1; x >= 0; x--)
					if (cell[y * WIDTH + x].isExist) {
						Cursor = { x, y };
						return;
					}
			// consider the second quadrant			
			for (int y = Cursor.y + 1; y >= 0; y--)
				for (int x = WIDTH - 1; x >= Cursor.x; x++)
					if (cell[y * WIDTH + x].isExist) {
						Cursor = { x, y };
						return;
					}
			break;
		case RIGHT:
			playSound(MOVE_SOUND);
			for (int y = Cursor.y; y < HEIGHT; y++) // Consider the third quadrant
				for (int x = Cursor.x + 1; x < WIDTH; x++)
					if (cell[y * WIDTH + x].isExist) {
						Cursor = { x, y };
						return;
					}

			for (int y = Cursor.y; y < HEIGHT; y++) // Consider the fourth quadrant 
				for (int x = 0; x < Cursor.x; x++)
					if (cell[y * WIDTH + x].isExist) {
						Cursor = { x, y };
						return;
					}
			for (int y = Cursor.y + 1; y >= 0; y--) // Consider the first quadrant
				for (int x = 0; x <= Cursor.x; x++)
					if (cell[y * WIDTH + x].isExist) {
						Cursor = { x, y };
						return;
					}
			for (int y = Cursor.y + 1; y >= 0; y--) // Consider the second quadrant
				for (int x = Cursor.x + 1; x < WIDTH; x++) {
					if (cell[y * WIDTH + x].isExist)
						Cursor = { x, y };
					return;
				}
			break;

			// If scrolling up or moving down, cursor.y is changed
			// Do not consider cursor.y where cursor.x is located (initially)
			// To move Y must be considered in the direction of X	
		case UP:
			playSound(MOVE_SOUND);
			for (int x = Cursor.x; x < WIDTH; x++) // Consider the second quadrant, direction away from cursor.y upward
				for (int y = Cursor.y - 1; y >= 0; y--)
					if (cell[y * WIDTH + x].isExist) {
						Cursor = { x, y };
						return;
					}
			for (int x = Cursor.x; x < WIDTH; x++) // Consider the third quadrant , The direction goes from the bottom up in the direction of Y
				for (int y = HEIGHT - 1; y > Cursor.y; y--)
					if (cell[y * WIDTH + x].isExist) {
						Cursor = { x, y };
						return;
					}
			for (int x = Cursor.x - 1; x >= 0; x--) // Consider the first quadrant
				for (int y = Cursor.y - 1; y >= 0; y--)
					if (cell[y * WIDTH + x].isExist) {
						Cursor = { x, y };
						return;
					}
			for (int x = Cursor.x - 1; x >= 0; x--) // Consider the fourth quadrant
				for (int y = HEIGHT - 1; y >= Cursor.y; y--)
					if (cell[y * WIDTH + x].isExist) {
						Cursor = { x, y };
						return;
					}
			break;

		case DOWN:
			playSound(MOVE_SOUND);
			for (int x = Cursor.x; x < WIDTH; x++) // Consider the fourth quadrant
				for (int y = Cursor.y + 1; y < HEIGHT; y++)
					if (cell[y * WIDTH + x].isExist) {
						Cursor = { x, y };
						return;
					}
			for (int x = Cursor.x; x < WIDTH; x++)// Consider the second quadrant
				for (int y = 0; y < Cursor.y; y++)
					if (cell[y * WIDTH + x].isExist) {
						Cursor = { x, y };
						return;
					}
			for (int x = Cursor.x - 1; x >= 0; x--)
				for (int y = Cursor.y + 1; y >= 0; y--)
					if (cell[y * WIDTH + x].isExist) {
						Cursor = { x, y };
						return;
					}
			for (int x = Cursor.x - 1; x >= 0; x--)
				for (int y = 0; y <= Cursor.y; y++)
					if (cell[y * WIDTH + x].isExist) {
						Cursor = { x, y };
						return;
					}
			break;

		case SPACE: // Mix table elements
			playSound(ENTER_SOUND);
			Mix_Board(cell);
			player.Score -= 3;
			break;
		case TAB:
			playSound(ENTER_SOUND);
			if (player.Suggestion > 0) {
				player.Suggestion--;
				player.Score -= 3;

				Background_Text_Color(BLACK, WHITE);
				gotoxy(94, 18);
				cout << "Suggestion: " << player.Suggestion;
				Text_Color(WHITE);

				for (char Char = 'A'; Char <= 'Z'; Char++) {
					CELL* cell_temp = new CELL[NUM]; // because there is always a maximum of NUM cells in existence
					int num = 0; // Number of cells that exist and have capital characters
					for (int i = 0; i < NUM; i++)
						if (cell[i].isExist && cell[i].c == Char) {
							cell_temp[num++] = cell[i];
						}
					// If there are 2 cells left together, the board is valid and the game has not automatically ended (chưa tự động kthuc)
					for (int i = 0; i < num - 1; i++)
						for (int j = i + 1; j < num; j++)
							if (AllCheck(cell, cell_temp[i], cell_temp[j])) {
								Text_Color(GREEN);
								int Xi = cell_temp[i].x + 1, Yi = cell_temp[i].y + 1;
								int Xj = cell_temp[j].x + 1, Yj = cell_temp[j].y + 1;
								for (int k = 0; k < 5; k++) {  // Draw Bolder of Cell
									gotoxy(Xi * 10, Yi * 4 + k);
									cout << border[k];
									gotoxy(Xj * 10, Yj * 4 + k);
									cout << border[k];
								}
								Text_Color(c % 6 + 1);
								gotoxy(Xi * 10 + 5, Yi * 4 + 2);
								cout << cell_temp[i].c;
								gotoxy(Xj * 10 + 5, Yj * 4 + 2);
								cout << cell_temp[j].c;
								Sleep(1500);
								Text_Color(WHITE);
								return;

							}
					}
			}
			break;
		default:
			break;
		}
	}
}
