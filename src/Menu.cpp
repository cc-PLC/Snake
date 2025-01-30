#include "Menu.h"
#include "Snake.h"
#include <conio.h>

using namespace std;



Menu::Menu(HANDLE* hEvent, HANDLE* hOutput):
    phEvent(hEvent),
    phOutput(hOutput),
    coordOrigin({ 0, 0 }),
    sizeX(25),
    sizeY(15) {}


void Menu::run()
{
    static const char* prompt =
        "=============================\n"
        "|         Snake Game        |\n"
        "|                           |\n"
        "| W,S to choose             |\n"
        "| Q to decrease             |\n"
        "| E to increase             |\n"
        "=============================\n";

    char currentSelection = 0;
    bool
        lastIncreaseX = false, lastIncreaseY = false,
        lastDecreaseX = false, lastDecreaseY = false;

    system("cls");

    while (true)
    {
        SetConsoleCursorPosition(*this->phOutput, this->coordOrigin);

        printf("%s\n", prompt);

        printf("  Set the board size:\n");
        printf("  %sX: %d          \n", currentSelection == 0 ? ">" : " ", this->sizeX);
        printf("  %sY: %d          \n", currentSelection == 1 ? ">" : " ", this->sizeY);
        printf("  %sStart!", currentSelection == 2 ? ">" : " ");

        char input = '\0';
        if (_kbhit()) { input = _getch(); } // Test "_kbhit" for non-blocking input
        switch (input)
        {
        case 'w':
            --currentSelection;
            if (currentSelection < 0) { currentSelection = 0; }
            break;
        case 's':
            ++currentSelection;
            if (currentSelection == 2) { return; }
            break;
        case 'q':
            if (currentSelection == 0)
            {
                if (lastDecreaseX) { this->sizeX -= 5; }
                else { --this->sizeX; }

                if (this->sizeX <= 0) { this->sizeX = 1; }
                lastDecreaseX = true;
            }
            else if (currentSelection == 1)
            {
                if (lastDecreaseY) { this->sizeY -= 5; }
                else { --this->sizeY; }

                if (this->sizeY <= 0) { this->sizeY = 1; }
                lastDecreaseY = true;
            }
            break;
        case 'e':
            if (currentSelection == 0)
            {
                if (lastIncreaseX) { this->sizeX += 5; }
                else { ++this->sizeX; }

                if (this->sizeX > 100) { this->sizeX = 100; }
                lastIncreaseX = true;
            }
            else if (currentSelection == 1)
            {
                if (lastIncreaseY) { this->sizeY += 5; }
                else { ++this->sizeY; }

                if (this->sizeY > 100) { this->sizeY = 100; }
                lastIncreaseY = true;
            }
            break;
        default:
            lastIncreaseX = false;
            lastIncreaseY = false;
            lastDecreaseX = false;
            lastDecreaseY = false;
            break;
        }

        size_t updateInterval =
            lastIncreaseX || lastIncreaseY || lastDecreaseX || lastDecreaseY ? 10 : 100;
        WaitForSingleObject(*this->phEvent, updateInterval);
    }
}

size_t Menu::getSizeX() const { return sizeX; }
size_t Menu::getSizeY() const { return sizeY; }
