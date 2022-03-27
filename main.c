#include "main.h"

#define MAP_SIZE 25

int main(int argc, char const *argv[])
{

    COORD dwSize = {120, 35};

    SetConsoleTitle("Mon Terminal"); // Réglage du titre
    if (setConsoleScreenBufferInfo(dwSize))
    { // Réglage des coordonnées
        printf("setConsoleScreenBufferInfo (%ld)\n", GetLastError());
        return EXIT_FAILURE;
    }
    openConsole();

    Map map = initMap(2);
    hideCursor();
    clearScreen(30);
    render(&map);
    while (!GetAsyncKeyState('P'))
    {

        update(&map);
        render(&map);
    }

    closeConsole();

    return EXIT_SUCCESS;
}
