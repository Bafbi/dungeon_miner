#pragma once

#include "entity.c"
#include "../utils/pos.c"

#define PLAYER_TEXTURE 2

typedef struct Player
{
    Entity entityData;
    char inventory[9];
    int viewDistance;
} Player;

/// Public function ///

Player *player_init(Entity entityData, int viewDistance);
void player_move(Player *player, Pos move);

///-----------------///

/// Private function ///

///------------------///

Player *player_init_ptr(Entity entityData, int viewDistance)
{
    Player *player;
    player = malloc(sizeof(player));
    player->entityData = entityData;
    player->viewDistance = viewDistance;

    return player;
}

void player_move(Player *player, Pos move)
{
    entity_setPos(&player->entityData, addPos(player->entityData.pos, move));
}
