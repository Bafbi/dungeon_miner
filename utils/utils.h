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

typedef struct Vec2
{
    double x, y;
} Vec2;

int modulo(int x, int N)
{
    return (x % N + N) % N;
}