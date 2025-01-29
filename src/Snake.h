#include <windows.h>
#include <iostream>
#include <vector>

#define EMPTY L"  "
#define BORDER L"≡ "
#define SNAKE_HEAD L"● "
#define SNAKE_BODY L"○ "
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
    HANDLE hEvent;
    HANDLE hOuput;
    COORD coordOrigin;
    std::vector<std::vector<std::wstring>> board;

    std::vector<Vec2> snake;
    int updateInterval;
    Vec2 dir;
    size_t score;

protected:
    void placeFood();
    void move(int deltaX, int deltaY);
    void draw();
public:
    Snake(size_t sizeX, size_t sizeY);
    ~Snake();

    void run();

};
