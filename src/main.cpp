#include "Menu.h"
#include "Snake.h"
#include <windows.h>
#include <conio.h>

using namespace std;



int main()
{
    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

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
