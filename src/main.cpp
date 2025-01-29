#include "Snake.h"

using namespace std;



int main()
{
    Snake snake(20, 20);
    try { snake.run(); }
    catch (const runtime_error& e) { cout << e.what() << endl; }

    printf("Press Enter to exit...");
    scanf_s("%*c");

    return 0;
}
