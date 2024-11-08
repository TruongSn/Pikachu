#include "Check.h"

bool NextCheck(CELL* cell, CELL cell1, CELL cell2) {
	if (cell1.c == cell2.c) {
		if ((cell1.x == cell2.x) && (cell1.y - 1 == cell2.y || cell1.y + 1 == cell2.y))
			return true;
		if ((cell1.y == cell2.y) && (cell1.x - 1 == cell2.x || cell1.x + 1 == cell2.x))
			return true;
	}
	return false;
}

bool Icheck(CELL* cell, CELL cell1, CELL cell2) {
	if (cell1.x == cell2.x) {
		int start = min(cell1.y, cell2.y);
		int end = max(cell1.y, cell2.y);
		int x = cell1.x;	// cell1.x or cell2.x are the same

		for (int y = start + 1; y < end; y++)  // Y coordinates running from Start to End
			if (cell[y * WIDTH + x].isExist) { // The cell at (x, y) has the order of y*WIDTH + x
				return false;
			}
		return true;
	}

	if (cell1.y == cell2.y) {
		int start = min(cell1.x, cell2.x);
		int end = max(cell1.x, cell2.x);
		int y = cell1.y;

		for (int x = start + 1; x < end; x++)  // x coordinates running from Start to End
			if (cell[y * WIDTH + x].isExist) { // The cell at (x, y) has the order of y*WIDTH + x
				return false;
			}
		return true;
	}
	return false;
}

// used to check Z-lines and U-lines
bool LineCheck(CELL* cell, CELL cell1, CELL cell2) {

	if (cell1.x == cell2.x) {

		int count = 0, x = cell1.x; // cell1.x or cell2.x are the same
		int start = min(cell1.y, cell2.y);
		int end = max(cell1.y, cell2.y);

		for (int y = start; y <= end; y++) {
			if (cell[y * WIDTH + x].isExist) // The cell at (x, y) has the order of y*WIDTH + x
				count++;
			if (count == 2) // There are 2 exit cells from cell1 to cell2
				return false;
		}

		if (count == 1 && ((cell1.isExist && !cell2.isExist) || (!cell1.isExist && cell2.isExist)))
			return true;
		else if (count == 0)
			return true;
		return false;
	}

	if (cell1.y == cell2.y) {

		int count = 0, y = cell1.y; // cell1.y or cell2.y are the same
		int start = min(cell1.x, cell2.x);
		int end = max(cell1.x, cell2.x);


		for (int x = start; x <= end; x++) {
			if (cell[y * WIDTH + x].isExist) // The cell at (x, y) has the order of y*WIDTH + x
				count++;
			if (count == 2) // There are 2 exit cells from cell1 to cell2
				return false;
		}

		if (count == 1 && ((cell1.isExist && !cell2.isExist) || (!cell1.isExist && cell2.isExist)))
			return true;
		else if (count == 0)
			return true;
		return false;
	}
	return false;
}

bool Lcheck(CELL* cell, CELL cell1, CELL cell2) {
	if ((cell1.x == cell2.x) || (cell1.y == cell2.y))
		return false;
	CELL cross_cell; // cell at 2-cell intersection

	cross_cell = cell[cell1.y * WIDTH + cell2.x];// at coordinates (cell2.x , cell1,y )
	if (cross_cell.isExist == 0) {
		if (LineCheck(cell, cell1, cross_cell) && LineCheck(cell, cell2, cross_cell))
			return true;
	}

	cross_cell = cell[cell2.y * WIDTH + cell1.x]; // at coordinates  (cell1.x, cell2.y)
	if (cross_cell.isExist == 0) {
		if (LineCheck(cell, cell1, cross_cell) && LineCheck(cell, cell2, cross_cell))
			return true;
	}
	return false;
}

bool Zcheck(CELL* cell, CELL cell1, CELL cell2) {

	int start_x = min(cell1.x, cell2.x), start_y = min(cell1.y, cell2.y);
	int end_x = max(cell1.x, cell2.x), end_y = max(cell1.y, cell2.y);
	// vertical Z-vertical check
	for (int x = start_x + 1; x < end_x; x++) {
		if (LineCheck(cell, cell[cell1.y * WIDTH + x], cell[cell2.y * WIDTH + x])) {
			bool condition1 = LineCheck(cell, cell1, cell[cell1.y * WIDTH + x]);
			bool condition2 = LineCheck(cell, cell2, cell[cell2.y * WIDTH + x]);
			if (condition1 && condition2)
				return true;
		}
	}
	// horizontal Z-vertical check
	for (int y = start_y + 1; y < end_y; y++) {
		if (LineCheck(cell, cell[y * WIDTH + cell1.x], cell[y * WIDTH + cell2.x])) {
			bool condition1 = LineCheck(cell, cell1, cell[y * WIDTH + cell1.x]);
			bool condition2 = LineCheck(cell, cell2, cell[y * WIDTH + cell2.x]);
			if (condition1 && condition2)
				return true;
		}
	}
	return false;
}

bool Ucheck(CELL* cell, CELL cell1, CELL cell2) {
	// If there are 2 cells on the same side of the board, it satisfies
	if ((cell1.x == cell2.x) && ((cell1.x == 0) || (cell1.x == WIDTH - 1))) // located on the left vertical edge, the right vertical edge
		return true;
	if ((cell1.y == cell2.y) && ((cell1.y == 0) || (cell1.y == HEIGHT - 1))) // located on the upper horizontal edge, the lower horizontal edge
		return true;

	int start_x = min(cell1.x, cell2.x), start_y = min(cell1.y, cell2.y);
	int end_x = max(cell1.x, cell2.x), end_y = max(cell1.y, cell2.y);

	bool condition1, condition2;

	// in vertical U -> in ascending direction of x
	for (int y = 0; y < HEIGHT; y++) {
		if (y <= start_y || y >= end_y) {
			if (LineCheck(cell, cell[y * WIDTH + cell1.x], cell[y * WIDTH + cell2.x])) {
				condition1 = LineCheck(cell, cell1, cell[y * WIDTH + cell1.x]);
				condition2 = LineCheck(cell, cell2, cell[y * WIDTH + cell2.x]);
				if (condition1 && condition2)
					return true;
			}
		}
		// consider that the line "_" blocks the letter U beyond the out-of-board range (i.e. there is an out-of-board seam)
		else if (y == 0 || y == HEIGHT - 1) {
			condition1 = LineCheck(cell, cell1, cell[y * WIDTH + cell1.x]);
			condition2 = LineCheck(cell, cell2, cell[y * WIDTH + cell2.x]);
			if (condition1 && condition2)
				return true;
			// if 1 of the 2 points is in position 1 of the 4 corners of the board
			else if ((condition1 && (cell2.y == y)) || (condition2 && (cell1.y == y)))
				return true;
		}
	}
	// consider the horizontal U -> in ascending direction of x

	for (int x = 0; x < WIDTH; x++) {
		if (x <= start_x || x >= end_x) {
			if (LineCheck(cell, cell[cell1.y * WIDTH + x], cell[cell2.y * WIDTH + x])) {
				condition1 = LineCheck(cell, cell1, cell[cell1.y * WIDTH + x]);
				condition2 = LineCheck(cell, cell2, cell[cell2.y * WIDTH + x]);
				if (condition1 && condition2)
					return true;
			}
			else if (x == 0 || x == (WIDTH - 1)) {
				condition1 = LineCheck(cell, cell1, cell[cell1.y * WIDTH + x]);
				condition2 = LineCheck(cell, cell2, cell[cell2.y * WIDTH + x]);
				if (condition1 && condition2)
					return true;
				// if 1 of the 2 points is in position 1 of the 4 corners of the board
				else if ((condition1 && (cell2.x == x)) || (condition2 && (cell1.x == x)))
					return true;
			}
		}
	}

	return false;
}

bool AllCheck(CELL* cell, CELL cell1, CELL cell2) {
	if (NextCheck(cell, cell1, cell2))
		return true;
	if (Icheck(cell, cell1, cell2))
		return true;
	if (Lcheck(cell, cell1, cell2))
		return true;
	if (Zcheck(cell, cell1, cell2))
		return true;
	if (Ucheck(cell, cell1, cell2))
		return true;
	return false;
}

bool Check_Exist_EqualPair(CELL* cell) {

	for (char Char = 'A'; Char <= 'Z'; Char++) {
		CELL* cell_temp = new CELL[NUM]; // because there is always a maximum of NUM cells in existence
		int num = 0; // Number of cells that exist and have capital characters
		for (int i = 0; i < NUM; i++) {
			if (cell[i].isExist && cell[i].c == Char) {
				cell_temp[num++] = cell[i];
			}
		}
		// Examine a set of cells in a grid and determine if any pairs of cells in that set meet certain specific conditions.
		for (int i = 0; i < num - 1; i++)
			for (int j = i + 1; j < num; j++) {
				if (AllCheck(cell, cell_temp[i], cell_temp[j]))
					return true;
			}
		delete[] cell_temp;
	}
	return false;
}
