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
    hideCursor();
    clearScreen();

    Game game = game_init();
    game_render(game);

    while (!GetAsyncKeyState('P'))
    {

        game_update(game, _getch());
        game_render(game);
    }

    closeConsole();

    return EXIT_SUCCESS;
}
