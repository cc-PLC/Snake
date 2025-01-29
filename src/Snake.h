#include <windows.h>
#include <iostream>
#include <vector>

#define EMPTY L"  "
#define BORDER L"◯ "
#define SNAKE_HEAD L"◙ "
#define SNAKE_BODY L"● "
#define FOOD L"★ "


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
    HANDLE hOuput;
    COORD coordOrigin;
    std::vector<std::vector<std::wstring>> board;

    size_t score;
    std::vector<Vec2> snake;
    Vec2 dir;

protected:
    void placeFood();
    void move(int deltaX, int deltaY);
    void draw();
public:
    Snake(size_t sizeX, size_t sizeY);
    ~Snake();

    void run();

};
