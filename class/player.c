#pragma once

#include "entity.c"

#define PLAYER_TEXTURE 2

typedef struct Player
{
    Entity entityData;
    char inventory[9];
} Player;
