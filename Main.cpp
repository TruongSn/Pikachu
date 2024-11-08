#include "Menu.h"

int main() {
    showCursor(0);      //Hide/show cursor function
    initWindow(900, 550);       //Console screen placement function
    int SelectStatus = 0;   
    Player player;

    while ((SelectStatus = mainMenu()) != 3) {
        switch (SelectStatus)
        {
        case 0:
            getPlayerInfo(player);   // Enter player information
            Play_Mode(player);      //Game mode
            break;
        case 1:
            helpScreen();   
            break;
        case 2:
            leaderBoard();  
            break;
        default:
            break;
        }
    }
    return 0;
}
