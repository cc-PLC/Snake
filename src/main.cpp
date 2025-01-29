#include "Snake.h"

using namespace std;



int main()
{
    size_t sizeX, sizeY;
    printf("Set the size (e.g. 10 10): ");
    std::cin >> sizeX >> sizeY;
    getchar();

    Snake snake(sizeX, sizeY);
    try { snake.run(); }
    catch (const runtime_error& e) { cout << e.what() << endl; }

    printf("Press Enter to exit...");
    getchar();

    return 0;
}
