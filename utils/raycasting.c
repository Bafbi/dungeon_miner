#pragma once

#include <stdbool.h>
#include <math.h>
#include "utils.h"
#include "../ressource/block.h"
#include "../class/map.c"

bool inverseRayCast(Map map, Pos posA, Pos posB);
int posToIndex(Pos pos, int size);
int Vec2Index(Vec2 pos, int size);

bool inverseRayCast(Map map, Pos posA, Pos posB)
{
    float distanceX = posA.x - posB.x;
    float distanceY = posA.y - posB.y;

    Vec2 testPoint = {posA.x, posA.y};

    while ((floor(testPoint.x) == posA.x && floor(testPoint.y) == posA.y) && map.data[((int)floor(testPoint.x) % map.size) + (int)(floor(testPoint.y) / map.size)].type == air_block)
    {
        if ((floor(testPoint.x) != posB.x && floor(testPoint.y) != posB.y))
        {
            return true;
        }

        testPoint.x += distanceX / 10;
        testPoint.y += distanceY / 10;
    }
    FILE *file = fopen("logger.txt", "wt");

    fseek(file, 0, 2);

    fprintf(file, "%f, %f ", testPoint.x, testPoint.y);
    fclose(file);

    return false;
}

int Vec2Index(Vec2 pos, int size)
{
    return ((int)floor(pos.x) % size) + (int)(floor(pos.y) / size);
}

int posToIndex(Pos pos, int size)
{
    return (pos.x % size + pos.y / size);
}

int distance(Pos posA, Pos posB)
{
    float distanceX = posA.x - posB.x;
    float distanceY = posA.y - posB.y;

    return sqrtf(distanceX * distanceX + distanceY * distanceY);
}
