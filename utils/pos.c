#pragma once

#include <limits.h>
#include "./utils.c"

typedef struct Pos
{
    short x, y;
} Pos;

// #define NULL_POS ({INT_MAX, INT_MIN})

Pos pos_init(int x, int y)
{
    Pos pos = {x, y};
    return pos;
}

Pos *pos_init_ptr(int x, int y)
{
    Pos *pos;
    pos = malloc(sizeof(Pos));
    pos->x = x;
    pos->y = y;
    return pos;
}

Pos addPos(Pos pos1, Pos pos2)
{
    Pos newPos = {pos1.x + pos2.x, pos1.y + pos2.y};
    return newPos;
}

Pos subPos(Pos pos1, Pos pos2)
{
    Pos newPos = {pos1.x - pos2.x, pos1.y - pos2.y};
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

Pos moduloPosByCnt(Pos pos, int cnt)
{
    Pos newPos = {modulo(pos.x, cnt),
                  modulo(pos.y, cnt)};
    return newPos;
}

Pos multiplyPosByCnt(Pos pos, int cnt)
{
    Pos newPos = {pos.x * cnt,
                  pos.y * cnt};
    return newPos;
}
