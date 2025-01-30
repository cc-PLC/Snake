#include "Menu.h"
#include "Snake.h"
#include <windows.h>
#include <conio.h>

using namespace std;



int main()
{
    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(hOuput, &cursorInfo);
    cursorInfo.bVisible = false; // Set the cursor visibility
    SetConsoleCursorInfo(hOuput, &cursorInfo);

    Menu menu(&hEvent, &hOuput);
    menu.run();

    while (true)
    {
        Snake snake(&hEvent, &hOuput, menu.getSizeX(), menu.getSizeY());
        try { snake.run(); }
        catch (const runtime_error& e) { printf("\t%s\n", e.what()); }
        printf("\tPress any key to restart...");
        _getch();
    }

    return 0;
}
