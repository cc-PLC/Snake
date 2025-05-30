#include <windows.h>
#include <iostream>
#include <vector>

#define EMPTY L"  "
#define BORDER L"X "
#define SNAKE_HEAD L"@ "
#define SNAKE_BODY L"O "
#define FOOD L"$ "


class Snake
{
public:
    class Vec2
    {
    public:
        int x;
        int y;
    };

protected:
    HANDLE* phEvent = nullptr;
    HANDLE* phOutput = nullptr;

    COORD coordOrigin;
    std::vector<std::vector<std::wstring>> board;

    std::vector<Vec2> snake;
    size_t speed;
    Vec2 dir;
    size_t score;

protected:
    void placeFood();
    void move(int deltaX, int deltaY);
    void draw();
public:
    Snake(HANDLE* phEvent, HANDLE* phOutput, size_t sizeX, size_t sizeY);

    void run();

};
