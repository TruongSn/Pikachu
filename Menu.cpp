#include "Menu.h"
#include <string>
#include <sstream>
using namespace std;


/* Function Animation - color screen with twinkling stars */
void printAnimation() { // OK
    srand(time(NULL));
    Background_Text_Color(BLACK, WHITE); 
    system("cls");
    int x = 0;
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 5; j++) {
            x = rand() % 120;
            gotoxy(x, i);
            Text_Color(rand() % 6 + 1);
            cout << "*";
        }
    }
    gotoxy(0, 0);
    Text_Color(WHITE);
}

void printLogo() {  
    Background_Text_Color(BLACK, BLUE);
    gotoxy(52, 1);
    Background_Text_Color(BLACK, LIGHT_YELLOW);
    gotoxy(35, 2);
    Background_Text_Color(BLACK, GREEN);
    cout << " ____     ___    _  __  _____   __  __    ___    _   _ ";
    gotoxy(35, 3);
    cout << "|  _ \\   / _ \\  | |/ / | ____| |  \\/  |  / _ \\  | \\ | |";
    Background_Text_Color(BLACK, YELLOW);
    gotoxy(35, 4);
    cout << "| |_) | | | | | | ' /  |  _|   | |\\/| | | | | | |  \\| |";
    gotoxy(35, 5);
    cout << "|  __/  | |_| | | . \\  | |___  | |  | | | |_| | | |\\  |";
    Background_Text_Color(BLACK, RED);
    gotoxy(35, 6);
    cout << "|_|      \\___/  |_|\ _\\ |_____| |_|  |_|  \\___/  |_| \\_|";

    Background_Text_Color(BLACK, LIGHT_AQUA);
    gotoxy(45, 10);
    cout << " Nguyen Ngoc Mai Xuan - 23127284";
    gotoxy(48, 11);
    cout << " Le Thi Minh Thu - 23127488";

}

/*rectangular frame drawing function*/
void printRectangle(int left, int top, int width, int height) { 

    gotoxy(left, top);
    cout << char(218);
    for (int i = 0; i < width; i++)
        cout << char(196);
    cout << char(191);

    int i = 0;
    while (i < height) {
        gotoxy(left, top + i + 1);
        cout << char(179);
        gotoxy(left + width + 1, top + i + 1);
        cout << char(179);
        i++;
    }

    gotoxy(left, top + i);
    cout << char(192);
    for (i = 0; i < width; i++)
        cout << char(196);
    cout << char(217);
}

void leaderBoard() {
    showCursor(false);
    int current_option = 0;
    system("cls");
    Player p[100];
    gotoxy(25, 1);
    Background_Text_Color(BLACK, WHITE);
    cout << " _     _____    _    ____  _____ ____  ____   ___    _    ____  ____";
    gotoxy(25, 2);
    cout << "| |   | ____|  / \\  |  _ \\| ____|  _ \\| __ ) / _ \\  / \\  |  _ \\|  _ \\";
    Background_Text_Color(BLACK, RED);
    gotoxy(25, 3);
    cout << "| |   |  _|   / _ \\ | | | |  _| | |_) |  _ \\| | | |/ _ \\ | |_) | | | |";
    gotoxy(25, 4);
    cout << "| |___| |___ / ___ \\| |_| | |___|  _ <| |_) | |_| / ___ \\|  _ <| |_| |";
    Background_Text_Color(BLACK, WHITE);
    gotoxy(25, 5);
    cout << "|_____|_____/_/   \\_\\____/|_____|_| \\_\\____/ \\___/_/   \\_\\_| \\_\\____/";


    //Draw a table
    Background_Text_Color(BLACK, WHITE);
    printRectangle(23, 7, 70, 17);

    Background_Text_Color(BLACK, YELLOW);
    gotoxy(26, 8);
    cout << "STT";
    Background_Text_Color(BLACK, WHITE);
    for (int i = 1; i < 17; i++)
    {
        gotoxy(31, 7 + i);
        cout << char(179);
    }
    for (int i = 24; i < 49; i++)
    {
        gotoxy(i, 9);
        cout << char(196);
    }


    Background_Text_Color(BLACK, YELLOW);
    gotoxy(36, 8);
    cout << "Name";
    Background_Text_Color(BLACK, WHITE);
    for (int i = 1; i < 17; i++)
    {
        gotoxy(45, 7 + i);
        cout << char(179);
    }
    for (int i = 49; i < 56; i++)
    {
        gotoxy(i, 9);
        cout << char(196);
    }

    Background_Text_Color(BLACK, YELLOW);
    gotoxy(52, 8);
    cout << "ID";
    Background_Text_Color(BLACK, WHITE);
    for (int i = 1; i < 17; i++)
    {
        gotoxy(60, 7 + i);
        cout << char(179);
    }
    for (int i = 56; i < 67; i++)
    {
        gotoxy(i, 9);
        cout << char(196);
    }

    Background_Text_Color(BLACK, YELLOW);
    gotoxy(67, 8);
    cout << "Class";
    Background_Text_Color(BLACK, WHITE);
    for (int i = 1; i < 17; i++)
    {
        gotoxy(80, 7 + i);
        cout << char(179);
    }
    for (int i = 67; i < 75; i++)
    {
        gotoxy(i, 9);
        cout << char(196);
    }

    Background_Text_Color(BLACK, YELLOW);
    gotoxy(84, 8);
    cout << "Score";
    Background_Text_Color(BLACK, WHITE);
    for (int i = 75; i < 94; i++)
    {
        gotoxy(i, 9);
        cout << char(196);
    }

    int y = 11;
    int lines = 6;




    int n = 0; // Player count

    ifstream fs("leaderboard.txt"); // Input file stream

    string line;
    while (getline(fs, line)) {
        p[n].name = line;
        getline(fs, p[n].ID);
        getline(fs, p[n].Class);

        // Read score using stringstream
        string scoreStr;
        getline(fs, scoreStr);
        stringstream(scoreStr) >> p[n].Score;

        n++;
    }

    fs.close();

    //Print out text in a table read from the file
    for (int i = 0; i < lines && i < n; i++) { // Adjusted loop to start from 0 and added a condition to avoid accessing out-of-bounds elements
        gotoxy(27, y);
        cout << i + 1; // Adjusted to print the correct index starting from 1

        gotoxy(35, y);
        cout << p[i].name; // Changed to use index i directly

        gotoxy(50, y);
        cout << p[i].ID;

        gotoxy(67, y);
        cout << p[i].Class;

        gotoxy(86, y);
        cout << p[i].Score;
        y += 2;
    }


    Background_Text_Color(BLACK, WHITE);
    printRectangle(55, 26, 10, 2);
    Background_Text_Color(BLACK, GREEN);
    gotoxy(57, 27);
    cout << char(175);
    gotoxy(59, 27);
    cout << "BACK";
    gotoxy(64, 27);
    cout << char(174);
    int c = _getch();
    if (c == ENTER)
        playSound(ENTER_SOUND);
    system("cls");


}

/*The function reads the file from the leaderboard.txt file to write player information to the table*/
void writeLeaderBoard(Player player) {
    Player leaderboard[10];
    int no_player = 0;

    ifstream fin("leaderboard.txt");
    if (fin.is_open()) {
        while (no_player < 10 && getline(fin, leaderboard[no_player].name)) {
            getline(fin, leaderboard[no_player].ID);
            getline(fin, leaderboard[no_player].Class);
            fin >> leaderboard[no_player].Score;
            fin.ignore();
            ++no_player;
        }
        fin.close();
    }

    int index = no_player - 1;
    for (index; index >= 0; --index) {
        if (player.Score <= leaderboard[index].Score) {
            break;
        }
    }

    if (no_player < 10) {
        for (int i = no_player; i > index + 1; --i) {
            leaderboard[i] = leaderboard[i - 1];
        }
        leaderboard[index + 1] = player;
        ++no_player;
    }
    else {
        if (index != no_player - 1) {
            for (int i = no_player - 1; i > index + 1; --i) {
                leaderboard[i] = leaderboard[i - 1];
            }
            leaderboard[index + 1] = player;
        }
    }

    ofstream fout("leaderboard.txt");

    for (int i = 0; i < no_player; ++i) {
        fout << leaderboard[i].name << endl;
        fout << leaderboard[i].ID << endl;
        fout << leaderboard[i].Class << endl;
        fout << leaderboard[i].Score << endl;
    }

    fout.close();
}

/*Get player information*/
void getPlayerInfo(Player& player) { // OK
    printLogo();

    Background_Text_Color(BLACK, LIGHT_RED);
    gotoxy(35, 14);
    cout << "Please enter your name with an underscore at the beginning";

    Background_Text_Color(BLACK, LIGHT_GREEN);
    gotoxy(50, 16);
    cout << "Enter player name: ";
    cin.ignore();
    getline(cin, player.name);

    Background_Text_Color(BLACK, LIGHT_YELLOW);
    gotoxy(50, 18);
    cout << "Enter your ID: ";
    getline(cin, player.ID);

    Background_Text_Color(BLACK, LIGHT_PURPLE);
    gotoxy(50, 20);
    cout << "Enter your classname: ";
    getline(cin, player.Class);
    player.Score = 0;
    Sleep(200);
    system("cls");
}

void helpScreen()
{
    showCursor(false);
    system("cls");

    Background_Text_Color(BLACK, GREEN);
    gotoxy(45, 1);
    Background_Text_Color(BLACK, AQUA);
    cout << "__  __    ____  __      _____";
    Background_Text_Color(BLACK, WHITE);
    gotoxy(45, 2);
    cout << "| |_| |  |__ |  | |     |  _ \\";
    gotoxy(45, 3);
    cout << "| __  |  | _|   | |__   | __/";
    Background_Text_Color(BLACK, AQUA);
    gotoxy(45, 4);
    cout << "|_| |_|  |___|  |____|  |_|";

    Background_Text_Color(BLACK, WHITE);
    int left = 20, top = 6, width = 85, height = 19;
    int line1 = 6, line2 = 10, line3 = 33, line4 = 21;  //chi?u dài hàng 3: line 4; line3: c?t 2; l?ne2: hàng 2
    printRectangle(left, top, width, height);
    gotoxy(left + 1, line1);
    for (int i = 0; i < width; i++)
        cout << char(196);

    gotoxy(left + 1, line2);
    for (int i = 0; i < width; i++)
        cout << char(196);

    gotoxy(left + 1, line4);
    for (int i = 1; i < width; i++)
        cout << char(196);

    for (int i = 1; i < height; i++) {
        gotoxy(line3, top + i);
        cout << char(179);
    }

    gotoxy(line3, line2);
    cout << char(197);

    Background_Text_Color(BLACK, YELLOW);
    gotoxy(left + 3, top + 9);
    cout << "Rules:";
    Background_Text_Color(BLACK, LIGHT_RED);
    gotoxy(left + 14, top + 5);
    cout << char(249); cout << " Win: ";
    Background_Text_Color(BLACK, WHITE);
    gotoxy(left + 14, top + 6);
    int left1 = left + 14;
    cout << " All pairs in the table are connected (the board has 20 pairs with";
    Background_Text_Color(BLACK, WHITE);
    gotoxy(left1, top + 7);
    cout << "the same characters), but it is not always possible to connect them all ";
    Background_Text_Color(BLACK, WHITE);
    gotoxy(left1, top + 8);
    cout << "because the player's first moves select 2 cells and delete 2 cells, ";
    Background_Text_Color(BLACK, WHITE);
    gotoxy(left1, top + 9);
    cout << "gradually creating a path for the remaining cells, if the player deletes";
    gotoxy(left1, top + 10);
    cout << "unwisely, it will block the path of the remaining cells, resulting in";
    gotoxy(left1, top + 11);
    cout << "winning the game but a low score";
    Background_Text_Color(BLACK, LIGHT_RED);
    gotoxy(left + 14, top + 13);
    cout << char(249); cout << " Lose: ";
    Background_Text_Color(BLACK, WHITE);
    gotoxy(left1, top + 14);
    cout << " Deducted all 3 lives";

    Background_Text_Color(BLACK, YELLOW);
    gotoxy(left + 3, top + 17);
    cout << "Scoring:";
    Background_Text_Color(BLACK, GREEN);
    gotoxy(left1 + 10, top + 16);
    cout << char(249); cout << " Matched: +20";
    Background_Text_Color(BLACK, GREEN);
    gotoxy(left1 + 40, top + 16);
    cout << char(249); cout << " Not matched: -10";
    Background_Text_Color(BLACK, GREEN);
    gotoxy(left1 + 10, top + 17);
    cout << char(249); cout << " Mixed cell: -3";
    gotoxy(left1 + 40, top + 17);
    cout << char(249); cout << " Move suggestion: -3";


    Background_Text_Color(BLACK, YELLOW);
    gotoxy(left + 2, top + 2);
    cout << "Developers:";
    Background_Text_Color(BLACK, LIGHT_AQUA);
    gotoxy(left + 20, top + 1);
    cout << "Dev 1: Nguyen Ngoc Mai Xuan (23127284)";
    gotoxy(left + 20, top + 2);
    cout << "Dev 2: Le Thi Minh Thu (23127488)";

    Background_Text_Color(BLACK, WHITE);
    printRectangle(57, 26, 10, 2);
    Background_Text_Color(BLACK, GREEN);
    gotoxy(59, 27);
    cout << char(175);
    gotoxy(61, 27);
    cout << "BACK";
    gotoxy(66, 27);
    cout << char(174);
    int c = _getch();
    if (c == ENTER)
        playSound(ENTER_SOUND);
    system("cls");
}

int mainMenu() {

    int choice[4] = { 0,0,0,0 }, temp, key, curChoice = 0;
    playSound(BACKGROUND_SOUND);
    printAnimation();
    printLogo();
    //GetBackground(bg);
    while (1) {

        choice[curChoice] = 1;

        if (choice[0]) {
            Background_Text_Color(BRIGHT_WHITE, LIGHT_PURPLE);
            for (int i = 0; i < 3; i++) {
                gotoxy(53, 14 + i);
                cout << "             "; 
            }
            gotoxy(55, 15);
            Background_Text_Color(BRIGHT_WHITE, RED);
            cout << "PLAY GAME";
        }
        else {
            Background_Text_Color(BLACK, LIGHT_YELLOW);

            for (int i = 0; i < 3; i++) {
                gotoxy(53, 14 + i);
                cout << "             ";
            }

            gotoxy(55, 15);
            Background_Text_Color(BLACK, WHITE);
            cout << "PLAY GAME";
        }


        if (choice[1]) {
            Background_Text_Color(BRIGHT_WHITE, LIGHT_PURPLE);

            for (int i = 0; i < 3; i++) {
                gotoxy(53, 17 + i);
                cout << "             ";
            }

            gotoxy(57, 18);
            Background_Text_Color(BRIGHT_WHITE, RED);
            cout << "HELP";
        }
        else {
            Background_Text_Color(BLACK, LIGHT_YELLOW);

            for (int i = 0; i < 3; i++) {
                gotoxy(53, 17 + i);
                cout << "             ";
            }

            gotoxy(57, 18);
            Background_Text_Color(BLACK, YELLOW);
            cout << "HELP";
        }


        if (choice[2]) {
            Background_Text_Color(BRIGHT_WHITE, LIGHT_PURPLE);

            for (int i = 0; i < 3; i++) {
                gotoxy(53, 20 + i);
                cout << "             ";
            }

            gotoxy(54, 21);
            Background_Text_Color(BRIGHT_WHITE, RED);
            cout << "LEADERBOARD";
        }
        else {
            Background_Text_Color(BLACK, LIGHT_YELLOW);
            for (int i = 0; i < 3; i++) {
                gotoxy(53, 20 + i);
                cout << "             ";
            }

            gotoxy(54, 21);
            Background_Text_Color(BLACK, GREEN);
            cout << "LEADERBOARD";
        }

        if (choice[3]) {
            Background_Text_Color(BRIGHT_WHITE, LIGHT_PURPLE);

            for (int i = 0; i < 3; i++) {
                gotoxy(53, 23 + i);
                cout << "             ";
            }

            gotoxy(57, 24);
            Background_Text_Color(BRIGHT_WHITE, RED);
            cout << "EXIT";
        }
        else {
            Background_Text_Color(BLACK, LIGHT_YELLOW);

            for (int i = 0; i < 3; i++) {
                gotoxy(53, 23 + i);
                cout << "             ";
            }

            gotoxy(57, 24);
            Background_Text_Color(BLACK, AQUA);
            cout << "EXIT";
        }

        Text_Color(WHITE);

        if (temp = _getch()) {
            if (temp != 224 && temp) {
                if (temp == ENTER) {
                    system("cls");
                    return curChoice;
                }
            }

            else {
                key = _getch();
                switch (key) {
                case UP:
                    playSound(MOVE_SOUND);
                    choice[curChoice] = 0;
                    if (curChoice > 0)
                        curChoice--;
                    else
                        curChoice = 3;
                    break;
                case DOWN:
                    playSound(MOVE_SOUND);
                    choice[curChoice] = 0;
                    if (curChoice < 3)
                        curChoice++;
                    else
                        curChoice = 0;
                default:
                    break;
                }
            }
        }
    }
}

/*function prints win or loss status*/
void DisplayStatus(bool win) {
    if (win) {
        Text_Color(LIGHT_YELLOW);

        gotoxy(50, 10);
        Background_Text_Color(BLACK, GREEN);
        cout << "__        _____ _   _";
        gotoxy(50, 11);
        cout << "\\ \\      / /_ _| \\ | |";
        gotoxy(50, 12);
        Background_Text_Color(BLACK, WHITE);
        cout << " \\ \\ /\\ / / | ||  \\| |";
        Background_Text_Color(BLACK, AQUA);
        gotoxy(50, 13);
        cout << "  \\ V  V /  | || |\\  |";
        gotoxy(50, 14);
        cout << "   \\_/\\_/  |___|_| \\_|";

        Text_Color(WHITE);
        playSound(WIN_SOUND);
        Sleep(2000);
    }
    else {

        gotoxy(50, 10);
        Background_Text_Color(BLACK, RED);
        cout << " _     ___  ____  _____ ";
        gotoxy(50, 11);
        cout << "| |   / _ \\/ ___|| ____|";
        gotoxy(50, 12);
        Background_Text_Color(BLACK, WHITE);
        cout << "| |  | | | \\___ \\|  _|";
        Background_Text_Color(BLACK, WHITE);
        gotoxy(50, 13);
        cout << "| |__| |_| |___) | |___";
        Background_Text_Color(BLACK, RED);
        gotoxy(50, 14);
        cout << "|_____\\___/|____/|_____|";
        Text_Color(WHITE);
        playSound(LOSE_SOUND);
        Sleep(2000);
    }
}

/*The function sets the state of whether or not the player wants to continue playing, when the player wins*/
void Play_Mode(Player& player) {

    player.Score = 0;  // Reinitialize after each loop
    player.Suggestion = 3;
    player.Life = 3;

    int status = 0, count = 0, pos[2];
    Pos select[2] = { {-1, -1}, {-1, -1} }, Cursor = { 0,0 };
    showCursor(0);

    CELL* cell = CreateBoard(); // Reinitialize the board 
    DrawBoard(cell);

    while ((!status) && player.Life) {

        cell[Cursor.y * WIDTH + Cursor.x].isChosen = 1;
        DrawBoard(cell);
        Movement(cell, player, status, select, pos, Cursor, count);
        if (!Check_Exist_EqualPair(cell))
            status = 1;
    }

    deleteBoard(cell);
    Sleep(2000);
    system("cls");

    if (player.Life && status == 1) {
        DisplayStatus(1);
        gotoxy(45, 17);
        char c;
        cout << "Do you want to play again? (Y/N): ";
        cin >> c;
        cin.ignore();
        system("cls");
        if (c == 'y' || c == 'Y')
            Play_Mode(player);
        else
            writeLeaderBoard(player);
    }
    else if (player.Life == 0) {
        DisplayStatus(0);
        gotoxy(50, 17);
        char c;
        writeLeaderBoard(player);
        Sleep(2000);
    }
    system("cls");
}
