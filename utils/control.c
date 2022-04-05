#pragma once

#include "./pos.c"

Pos getMove(int input)
{
    Pos pos = {0, 0};
    switch (input)
    {
    case 'z':
        pos.y = -1;
        break;
    case 'd':
        pos.x = +1;
        break;
    case 's':
        pos.y = +1;
        break;
    case 'q':
        pos.x = -1;
        break;
    default:
        break;
    }

    return pos;
}