#include "gotoxy.h"
#include <windows.h>

gotoxy::gotoxy(int x, int y)
{

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD CursorPosition;

    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);

}
