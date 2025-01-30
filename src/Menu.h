#include <iostream>
#include <windows.h>



class Menu
{
protected:
    HANDLE* phEvent = nullptr;
    HANDLE* phOutput = nullptr;
    COORD coordOrigin;

    int sizeX, sizeY;

public:
    Menu(HANDLE* phEvent, HANDLE* phOutput);

    void run();

    size_t getSizeX() const;
    size_t getSizeY() const;

};
