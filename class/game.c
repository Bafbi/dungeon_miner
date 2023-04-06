#pragma once

#include "./map.c"
#include "./player.c"
#include "../utils/ConsoleTools.c"
#include "../utils/render.c"
#include "./config.c"

typedef struct Game
{
    Map *map;
    Player *player;
    Pos *camPos;
    Config *config;
} Game;

/// Public function ///

Game game_init();
void game_update(Game game, char keyPress);
void game_render(Game game);

///----------------///

Game game_init()
{
    Game game;
    COORD consoleSize = getConsoleSize();

    game.map = map_init(2);
    game.player = player_init_ptr(entity_init(pos_init(5, 5), 100), 10);
    game.camPos = pos_init_ptr(consoleSize.X / 2, consoleSize.Y / 2);
    game.config = config_init_ptr(2);

    return game;
}

void game_update(Game game, char keyPress)
{
    Pos move = getMove(keyPress);
    Pos playerPos = game.player->entityData.pos;
    Pos newPos = addPos(playerPos, move);

    if (map_testCollision(*game.map, newPos))
    {
        map_mineBlock(game.map, newPos);
        return;
    }
    player_move(game.player, move);
    // game.camPos->x -= move.x;
    // game.camPos->y -= move.y;
}

void game_render(Game game)
{
    Player player = *game.player;
    Pos playerPos = player.entityData.pos;
    Pos playerChunkPos = dividePosByCnt(playerPos, CHUNK_SIZE);
    Pos playerPosChunk = moduloPosByCnt(playerPos, CHUNK_SIZE);

    Pos pos1 = {0, 0};
    Pos pos2 = {CHUNK_SIZE, CHUNK_SIZE};
    Chunk chunk = *map_getChunk_ptr(game.map, playerChunkPos);

    renderChunk(chunk, addPos(multiplyPosByCnt(chunk.position, CHUNK_SIZE), *game.camPos), pos1, pos2);

    Pos relativePlayerPos = addPos(playerPos, *game.camPos);
    moveCursor(relativePlayerPos.x, relativePlayerPos.y);
    setBackGroundColor(0);
    setWriteColor(15);
    plotChar(PLAYER_TEXTURE);
    moveCursor(0, 16 + 1);
}
