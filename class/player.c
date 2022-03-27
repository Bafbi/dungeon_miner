#pragma once

#include "entity.c"

#define PLAYER_TEXTURE 2

typedef struct Player
{
    Entity entityData;
    int viewDistance;
    char inventory[9];
} Player;
