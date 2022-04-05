#pragma once

/// Standard lib ///
#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
///-------------///

/// My file ///
// Class
#include "./player.c"
#include "./chunk.c"
// Utils
#include "../utils/new_perlin.c"
#include "../utils/control.c"
#include "../utils/pos.c"
#include "../utils/ConsoleTools.h"
// Ressource
#include "../ressource/block.h"
///--------///

/// Struct ///
typedef struct Map
{
    Chunk *chunkData;
    int nbChunkLoad;
    int *generationSeeds;
} Map;
///--------///

/// Public function ///

/**
 * @brief
 *
 * @param map The map to render
 * @param displayPos The relative position in the console to render the map part
 * @param start Starting position of the part of map (corner up-left)
 * @param end Ending position of the part of map (corner bottom-right)
 */
void map_renderPart(Map *map, Pos displayPos, Pos start, Pos end);

/**
 * @brief Load chunk
 *
 * @param map
 * @param chunkPos
 */
void map_loadChunk(Map *map, Pos chunkPos);

/**
 * @brief Load multiple chunk
 *
 * @param map
 * @param loadDistance
 */
void map_loadChunks(Map *map, int loadDistance);

/**
 * @brief Constructor of map
 *
 * @param loadDistance
 * @return Map*
 */
Map *map_init(int loadDistance);

/**
 * @brief Test for block collision on a pos
 *
 * @param map
 * @param pos
 * @return true When the pos given is in a block which is not air or have durability
 * @return false
 */
bool map_testCollision(Map map, Pos pos);

/**
 * @brief Get the block at a certain pos.
 *
 * @param *map
 * @param pos
 * @return Block*
 */
Block *map_getBlock_ptr(Map *map, Pos pos);

/**
 * @brief Get the chunk at a certain chunk pos
 *
 * @param *map
 * @param chunkPos
 * @return Chunk*
 */
Chunk *map_getChunk_ptr(Map *map, Pos chunkPos);

/**
 * @brief Remove durability / destroy a certain block
 *
 * @param map
 * @param pos
 */
void map_mineBlock(Map *map, Pos pos);

///-----------------///

void map_loadChunk(Map *map, Pos chunkPos)
{
    map->chunkData[map->nbChunkLoad] = chunk_generateNew(chunkPos, map->generationSeeds);
    map->nbChunkLoad++;
}

void map_loadChunks(Map *map, int loadDistance)
{
    Pos loadPos = {0, 0};
    map_loadChunk(map, loadPos);

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
                map_loadChunk(map, loadPos);
            }
        }
    }
}

Map *map_init(int loadDistance)
{
    Map *map;
    map = malloc(sizeof(Map));
    map->generationSeeds = malloc(sizeof(int) * 2);
    map->generationSeeds[CAVE_SEED] = rand();
    map->generationSeeds[MYTRILE_SEED] = rand();
    map->nbChunkLoad = 0;
    map->chunkData = malloc(sizeof(Chunk) * (2 * loadDistance + 1) * (2 * loadDistance + 1));
    map_loadChunks(map, loadDistance);

    return map;
}

bool map_testCollision(Map map, Pos pos)
{
    if (map_getBlock_ptr(&map, pos)->type != AIR_BLOCK)
    {
        return true;
    }
    return false;
}

Block *map_getBlock_ptr(Map *map, Pos pos)
{
    Pos chunkPos = {floor((float)pos.x / (float)CHUNK_SIZE),
                    floor((float)pos.y / (float)CHUNK_SIZE)};
    Pos blockPos = {modulo(pos.x, CHUNK_SIZE),
                    modulo(pos.y, CHUNK_SIZE)};

    Chunk *chunk = map_getChunk_ptr(map, chunkPos);
    Block *block = &chunk->blockData[blockPos.x + blockPos.y * CHUNK_SIZE];

    return block;
}

Chunk *map_getChunk_ptr(Map *map, Pos chunkPos)
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

void map_mineBlock(Map *map, Pos pos)
{
    Block *block = map_getBlock_ptr(map, pos);
    block->durability -= 1;
    if (block->durability == 0)
    {
        block->type = AIR_BLOCK;
    }
}