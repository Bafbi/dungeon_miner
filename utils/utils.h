#pragma once

#include <limits.h>

typedef struct Pos
{
    short x, y;
} Pos;

#define NULL_POS         \
    {                    \
        INT_MAX, INT_MIN \
    }

Pos addPos(Pos pos1, Pos pos2)
{
    Pos newPos = {pos1.x + pos2.x, pos1.y + pos2.y};
    return newPos;
}

Pos multiplyPos(Pos pos1, Pos pos2)
{
    Pos newPos = {pos1.x * pos2.x, pos1.y * pos2.y};
    return newPos;
}

Pos dividePosByCnt(Pos pos, int cnt)
{
    Pos newPos = {floor((float)pos.x / (float)cnt),
                  floor((float)pos.y / (float)cnt)};
    return newPos;
}

typedef struct Vec2
{
    double x, y;
} Vec2;

int modulo(int x, int N)
{
    return (x % N + N) % N;
}