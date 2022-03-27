#pragma once

#include "player.c"
#include <conio.h>
#include "../utils/new_perlin.c"
#include "../ressource/block.h"
#include "../control.c"
#include "../utils/utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define CHUNK_SIZE 16

typedef struct Block
{
    BlockType type;
    int durability;
} Block;

typedef struct Chunk
{
    Block *blockData;
    Pos position;
    Entity *entity;
} Chunk;

typedef struct Map
{
    Chunk *chunkData;
    int nbChunkLoad;
    Player player;
} Map;

Chunk generateChunk(Pos pos);
void loadChunk(Map *map, Pos pos);
Map initMap();
void update(Map *map);
Pos addPos(Pos pos1, Pos pos2);
Pos multiplyPos(Pos pos1, Pos pos2);
bool testCollision(Map *map, Pos move);
void mineBlock(Map *map, Pos pos);
Block *getBlock(Map *map, Pos pos);
Chunk *getChunk(Map *map, Pos chunkPos);

static int CAVE_SEED;
static int ORE_SEED;

Chunk generateChunk(Pos pos)
{

    Chunk chunk;
    chunk.blockData = malloc(sizeof(Block) * CHUNK_SIZE * CHUNK_SIZE);
    chunk.position = pos;

    SEED = CAVE_SEED;
    float perlinCave[CHUNK_SIZE * CHUNK_SIZE];
    for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++)
    {
        perlinCave[i] = Perlin_Get2d((i % CHUNK_SIZE) + pos.x * CHUNK_SIZE, (i / CHUNK_SIZE) + pos.y * CHUNK_SIZE, 0.2, 1);
    }

    SEED = ORE_SEED;
    float perlinOre[CHUNK_SIZE * CHUNK_SIZE];
    for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++)
    {
        perlinOre[i] = Perlin_Get2d((i % CHUNK_SIZE) + pos.x * CHUNK_SIZE, (i / CHUNK_SIZE) + pos.y * CHUNK_SIZE, 0.1, 1);
    }

    for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++)
    {
        int type = perlinCave[i] < 0.5 ? air_block : perlinOre[i] < 0.95 ? stone_block
                                                                         : mytrile_block;
        int dura;
        dura = perlinCave[i] < 0.7 ? 1 : perlinCave[i] < 0.8 ? 2
                                     : perlinCave[i] < 0.9   ? 3
                                                             : 4;
        Block block = {type, dura};
        chunk.blockData[i] = block;
    }

    return chunk;
}

void loadChunk(Map *map, Pos chunkPos)
{
    map->chunkData[map->nbChunkLoad] = generateChunk(chunkPos);
    map->nbChunkLoad++;
}

void loadChunks(Map *map, int loadDistance)
{
    Pos loadPos = {0, 0};
    loadChunk(map, loadPos);

    for (int k = 1; k <= loadDistance; k++)
    {
        loadPos.x = -k;
        loadPos.y = -k;
        for (short c = 0; c < 4; c++)
        {
            for (int n = 1; n < 2 * k + 1; n++)
            {
                switch (c)
                {
                case 0:;
                    Pos posTmp1 = {1, 0};
                    loadPos = addPos(loadPos, posTmp1);
                    break;
                case 1:;
                    Pos posTmp2 = {0, 1};
                    loadPos = addPos(loadPos, posTmp2);
                    break;
                case 2:;
                    Pos posTmp3 = {-1, 0};
                    loadPos = addPos(loadPos, posTmp3);
                    break;
                case 3:;
                    Pos posTmp4 = {0, -1};
                    loadPos = addPos(loadPos, posTmp4);
                    break;
                }
                loadChunk(map, loadPos);
            }
        }
    }
}

Map initMap(int loadDistance)
{
    CAVE_SEED = rand();
    ORE_SEED = rand();
    Map map;
    map.nbChunkLoad = 0;
    map.chunkData = malloc(sizeof(Chunk) * (2 * loadDistance + 1) * (2 * loadDistance + 1));
    loadChunks(&map, loadDistance);
    Player tmpPlayer = {{{0, 0}, 100, 5}, {0}};
    map.player = tmpPlayer;

    return map;
}

void update(Map *map)
{

    Pos move = getMove(_getch());
    Pos playerPos = map->player.entityData.pos;
    Pos newPos = addPos(playerPos, move);
    printf("%d %d + %d %d = %d %d ", playerPos.x, playerPos.y, move.x, move.y, newPos.x, newPos.y);

    if (testCollision(map, newPos))
    {
        mineBlock(map, newPos);
        return;
    }
    entity_setPos(&map->player.entityData, newPos);
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

bool testCollision(Map *map, Pos pos)
{
    if (getBlock(map, pos)->type != air_block)
    {
        return true;
    }
    return false;
}

Block *getBlock(Map *map, Pos pos)
{
    Pos chunkPos = {floor((float)pos.x / (float)CHUNK_SIZE),
                    floor((float)pos.y / (float)CHUNK_SIZE)};
    Pos blockPos = {modulo(pos.x, CHUNK_SIZE),
                    modulo(pos.y, CHUNK_SIZE)};

    Chunk *chunk = getChunk(map, chunkPos);
    Block *block = &chunk->blockData[blockPos.x + blockPos.y * CHUNK_SIZE];

    return block;
}

Chunk *getChunk(Map *map, Pos chunkPos)
{
    for (int i = 0; i < map->nbChunkLoad; i++)
    {
        Pos currentChunkPos = map->chunkData[i].position;
        if (currentChunkPos.x == chunkPos.x && currentChunkPos.y == chunkPos.y)
        {
            return &map->chunkData[i];
        }
    }
    return NULL;
}

void mineBlock(Map *map, Pos pos)
{
    Block *block = getBlock(map, pos);
    block->durability -= 1;
    if (block->durability == 0)
    {
        block->type = air_block;
    }
}