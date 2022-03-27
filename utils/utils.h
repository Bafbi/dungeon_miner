#pragma once

typedef struct Pos
{
    short x, y;
} Pos;

typedef struct Vec2
{
    double x, y;
} Vec2;

int modulo(int x, int N)
{
    return (x % N + N) % N;
}