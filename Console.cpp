#include "Console.h"

/* Scrollbar hidden function */
void hideScrollBar() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(console, &screenBufferInfo);
    COORD new_screen_buffer_size;
    new_screen_buffer_size.X = screenBufferInfo.srWindow.Right - screenBufferInfo.srWindow.Left + 1;
    new_screen_buffer_size.Y = screenBufferInfo.srWindow.Bottom - screenBufferInfo.srWindow.Top + 1;
    SetConsoleScreenBufferSize(console, new_screen_buffer_size);
}

/* Hide/show cursor function*/
void showCursor(bool show)
{
    CONSOLE_CURSOR_INFO info = { 1, show };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

/* Console screen resizing function */
void resizeWindow(int x, int y) {
    HWND console = GetConsoleWindow();  
    RECT r; 
    GetWindowRect(console, &r); 
    MoveWindow(console, r.left, r.top, x, y, TRUE); 
}

/* Console screen placement function */
void initWindow(int width, int length) {
    resizeWindow(width, length);
    hideScrollBar();
    showCursor(0);
}

/* Centering function and setting up the console screen */
void setAndCenterWindow()
{
    RECT rectClient, rectWindow;
    GetClientRect(GetConsoleWindow(), &rectClient), GetWindowRect(GetConsoleWindow(), &rectWindow);
    int width = 1100;
    int height = 768;
    int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
        posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
    MoveWindow(GetConsoleWindow(), posX, posY, width, height, TRUE);
}

/* The function moves the cursor to the coordinates (x,y) */
void gotoxy(int x, int y) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition;
    cursorPosition.X = x;
    cursorPosition.Y = y;
    SetConsoleCursorPosition(console, cursorPosition);
}


/*Background and text color settings function */
void Background_Text_Color(int b_color, int t_color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (b_color << 4) | t_color);
}

/*The function only sets the color for text*/
void Text_Color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/* Audio settings function */
void playSound(int i)
{
    const wchar_t* soundFile[] = {
        L"move.wav", L"enter.wav", L"error.wav", L"placed.wav", L"win.wav", L"background2.wav", L"effect.wav", L"lose.wav"
    };
    const int numSounds = sizeof(soundFile) / sizeof(soundFile[0]);

        if (i >= 0 && i < numSounds) {
            PlaySound(soundFile[i], NULL, SND_FILENAME | SND_ASYNC);
        }
}