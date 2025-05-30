#include "Snake.h"
#include <conio.h>
#include <sstream>

using namespace std;



Snake::Snake(HANDLE* phEvent, HANDLE* phOutput, size_t sizeX, size_t sizeY):
    phEvent(phEvent),
    phOutput(phOutput),
    coordOrigin({ 0, 0 }),
    board(sizeY + 2, vector<wstring>(sizeX + 2, EMPTY)),
    speed(5),
    dir({ 0, 0 }),
    score(0)
{
    if (!sizeX || !sizeY) { throw invalid_argument("Invalid size"); }
    setlocale(LC_ALL, "en_US.UTF-8");
    srand(time(nullptr));

    this->snake.emplace_back(Vec2{ static_cast<int>(sizeX) / 2 + 1, static_cast<int>(sizeY) / 2 + 1});
    for (size_t i = 0; i < board.size(); i++)
    {
        for (size_t j = 0; j < board[i].size(); j++)
        {
            if (i == 0 || i == board.size() - 1 || j == 0 || j == board[i].size() - 1)
            {
                this->board[i][j] = BORDER;
            }
        }
    }
    this->board[this->snake.front().y][this->snake.front().x] = SNAKE_HEAD;

    this->placeFood();
}


void Snake::placeFood()
{
    bool foodPlaced = false;
    while (!foodPlaced)
    {
        int x = rand() % (this->board[0].size() - 2) + 1;
        int y = rand() % (this->board.size() - 2) + 1;
        if (this->board[y][x] == EMPTY)
        {
            this->board[y][x] = FOOD;
            foodPlaced = true;
        }
    }
}
void Snake::move(int deltaX, int deltaY)
{
    this->board[this->snake.front().y][this->snake.front().x] = SNAKE_BODY;

    this->snake.insert(this->snake.begin(), { this->snake.front().x + deltaX, this->snake.front().y + deltaY });
    if (this->board[this->snake.front().y][this->snake.front().x] == FOOD)
    {
        this->score += this->speed * this->speed;
        this->placeFood();
    }
    else
    {
        this->board[this->snake.back().y][this->snake.back().x] = EMPTY;
        this->snake.pop_back();
    }

    if (this->board[this->snake.front().y][this->snake.front().x] != EMPTY &&
        this->board[this->snake.front().y][this->snake.front().x] != FOOD
    ) { throw runtime_error("Game Over"); }
    else { this->board[this->snake.front().y][this->snake.front().x] = SNAKE_HEAD; }
}

void Snake::draw()
{
    SetConsoleCursorPosition(*this->phOutput, this->coordOrigin);

    printf(
        "=============================\n"
        "|         Snake Game        |\n"
        "|                           |  Score: %zu\n"
        "| W,A,S,D to move           |\n"
        "| Q to decrease speed       |  Speed: %zu          \n"
        "| E to increase speed       |\n"
        "=============================\n\n",
        this->score, this->speed
    );

    wstringstream ss;
    for (size_t i = 0; i < board.size(); i++)
    {
        for (size_t j = 0; j < board[i].size(); j++)
        {
            ss << this->board[i][j];
        }
        ss << std::endl;
    }
    wprintf(L"%ls", ss.str().c_str());
}

void Snake::run()
{
    system("cls");

    while (true)
    {
        // getinput
        char input = '\0';
        if (_kbhit()) { input = _getch(); } // Test "_kbhit" for non-blocking input
        switch (input)
        {
        case 'w':
            if (this->dir.y != 1) { this->dir = { 0, -1 }; }
            break;
        case 'a':
            if (this->dir.x != 1) { this->dir = { -1, 0 }; }
            break;
        case 's':
            if (this->dir.y != -1) { this->dir = { 0, 1 }; }
            break;
        case 'd':
            if (this->dir.x != -1) { this->dir = { 1, 0 }; }
            break;
        case 'q':
            this->speed -= 1;
            if (this->speed == 0) { this->speed = 1; }
            break;
        case 'e':
            this->speed += 1;
            break;
        default:
            break;
        }

        this->move(this->dir.x, this->dir.y);
        this->draw();
        WaitForSingleObject(*this->phEvent, 1000 / this->speed);
    }
}
