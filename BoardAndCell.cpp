#include "BoardAndCell.h"

/*This line declares a 2-dimensional array called box, representing the visual layout of a single cell on the game board*/
char box[5][12] = {
            {"..........."},
            {":         :"},
            {":         :"},
            {":         :"},
            {"..........."}
};

/*Draws a single cell on the game board*/
void DrawCell(CELL cell, int b_color = BRIGHT_WHITE) {
    if (!cell.isExist) 	 // Checks if the cell exists. If the cell doesn't exist
        return;

    int X = cell.x + 1, Y = cell.y + 1;

    for (int i = 0; i < 5; i++) {   // Draw the border of a cell
        gotoxy(X * 10, Y * 4 + i);
        cout << box[i];
    }

    if (cell.isChosen) {
        // use ( c%6 + 1 ) to ensure that the color can be visible clearly on the black ground of console screen
        Background_Text_Color(b_color, cell.c % 6 + 1);

        for (int i = 1; i < 4; i++) {
            gotoxy(X * 10 + 1, Y * 4 + i);
            cout << "         ";
        }
        gotoxy(X * 10 + 5, Y * 4 + 2); // Go to the center position of a cell
        cout << cell.c;
        Text_Color(WHITE); // Reset the color of the text  
    }
    else {
        Text_Color(cell.c % 6 + 1);
        gotoxy(X * 10 + 5, Y * 4 + 2);
            cout << cell.c;
        Text_Color(WHITE);
    }
}

void DeleteCell(CELL& cell) {
    int X = cell.x + 1, Y = cell.y + 1;
    for (int i = 0; i < 5; i++) {
        gotoxy(X * 10, Y * 4 + i);
        cout << "           ";	//  Color the box inside of a cell
    }
}

void Mix_Board(CELL* cell)
{
    for (int i = 0; i < 20 + 1; i++) {
        int index1 = rand() % 20, index2 = rand() % 20 + 20;    // Select cells to shuffle randomly
        if (cell[index1].isExist && cell[index2].isExist)
            swap(cell[index1].c, cell[index2].c);
    }
}

CELL* CreateBoard() {

    srand(time(NULL));
    int NUMBER = HEIGHT * WIDTH / 2;
    CELL* cell = new CELL[NUM];
    int k = 0;
    for (int i = 0; i < HEIGHT; i++)  // Determine the coordinates of each cell
        for (int j = 0; j < WIDTH; j++) {
            cell[k].y = i;
            cell[k].x = j;
            k++;
        }
    for (int i = 0; i < NUMBER; i++) { // Determine the upper letter that each cell included randomly
        char c = char(rand() % 26 + 65);
        cell[i].c = cell[NUM - i - 1].c = c;
    }
    Mix_Board(cell);  // Mix cells randomly
    return cell;
}

void DrawBoard(CELL* cell) {
    for (int i = 0; i < NUM; i++) {
        DrawCell(cell[i]);
    }
}

void deleteBoard(CELL*& cell) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            int num = y * WIDTH + x;  // cell with the coordinates x, y has the index equal to  (y * WIDTH + x ) on the board
            if (cell[num].isExist) {
                DeleteCell(cell[num]);
                Sleep(200);
            }
        }
    }
    delete[] cell;
}
